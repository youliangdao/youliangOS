#include "../lib/bootpack.h"

#define EFLAGS_AC_BIT       0x00040000
#define CR0_CACHE_DISABLE   0x60000000

void memman_init(struct MEMMAN *man)
{
  man->frees = 0;         // 空き情報の個数
  man->maxfrees = 0;      // 状況観察用 : freeの最大値
  man->lostsize = 0;      // 解放に失敗した合計サイズ
  man->losts = 0;         // 解放に失敗した回数
  return;
}

unsigned int memman_total(struct MEMMAN *man)
// 空きサイズの合計を報告
{
  unsigned int i, t = 0;
  for ( i = 0; i < man->frees; i++)
  {
    t += man->free[i].size;
  }
  return t;
}

unsigned int memman_alloc(struct MEMMAN *man, unsigned int size)
// 確保
{
  unsigned int i, a;
  for ( i = 0; i < man->frees; i++)
  {
    if (man->free[i].size >= size)
    {
      // 十分な広さの空きを発見
      a = man->free[i].addr;
      man->free[i].addr += size;
      man->free[i].size -= size;
      if (man->free[i].size == 0)
      {
        // free[i]がなくなったので前へつめる
        man->frees--;
        for (; i < man->frees; i++)
        {
          man->free[i] = man->free[i + 1];  // 構造体の代入
        }
        
      }
      return a;
    }
    
  }
  return 0;   // 空きがない
}

// 4KB単位でメモリを確保
unsigned int memman_alloc_4k(struct MEMMAN *man, unsigned int size)
{
    unsigned int a;
    size = (size + 0xfff) & 0xfffff000;
    a = memman_alloc(man, size);
    return a;
}

int memman_free(struct MEMMAN *man, unsigned int addr, unsigned int size)
// 解放
{
  int i, j;
  // まとめやすさを考えると、free[]がaddr順に並んでいる方がいい
  // だからまず、どこに入れるべきかを決める
  for ( i = 0; i < man->frees; i++)
  {
    if (man->free[i].addr > addr)
    {
      break;
    }
  }
  // free[i - 1].addr < addr < free[i].addr
  if (i > 0)
  {
    // 前がある
    if (man->free[i - 1].addr + man->free[i - 1].size == addr)
    {
      // 前の空き領域にまとめられる
      man->free[i - 1].size += size;
      if (i < man->frees)
      {
        // 後ろもある
        if (addr + man->free[i].addr)
        {
          // なんと後ろもまとめられる
          man->free[i - 1].size += man->free[i].size;
          // man->free[i]の削除
          // free[i]がなくなったので前へ詰める
          man->frees--;
          for (; i < man->frees; i++)
          {
            man->free[i] = man->free[i + 1];  // 構造体の代入
          }
          
        }
        
      }
      return 0;   // 成功終了
    }
    
  }
  // 前はまとめられなかった
  if (i < man->frees)
  {
    // 後ろがある
    if (addr + size == man->free[i].addr)
    {
      // 後ろとはまとめられる
      man->free[i].addr = addr;
      man->free[i].size += size;
      return 0; // 成功終了
    }
    
  }
  // 前にも後ろにもまとめられない
  if (man->frees < MEMMAN_FREES)
  {
    // free[i]より後ろを、後ろへずらして、隙間を作る
    for ( j = man->frees; j > i; j--)
    {
      man->free[j] = man->free[j - 1];
    }
    man->frees++;
    if (man->maxfrees < man->frees)
    {
      man->maxfrees = man->frees; // 最大値を更新
    }
    man->free[i].addr = addr;
    man->free[i].size = size;
    return 0; // 成功終了
  }
  // 後ろにずらせなかった
  man->losts++;
  man->lostsize += size;
  return -1;  // 失敗終了
  
}

int memman_free_4k(struct MEMMAN *man, unsigned int addr, unsigned int size)
{
    int i;
    size = (size + 0xfff) & 0xfffff000;
    i = memman_free(man, addr, size);
    return i;
}

unsigned int memtest(unsigned int start, unsigned int end)
{
  char flag486 = 0;
  unsigned int eflag, cr0, i;

  // 386か、486以降なのか確認
  eflag = io_load_eflags();
  eflag |= EFLAGS_AC_BIT;   // AC-bit = 1
  io_store_eflags(eflag);
  eflag = io_load_eflags();
  if ((eflag & EFLAGS_AC_BIT) != 0)   // 386ではAC=1にしても自動で0に戻ってしまう
  {
    flag486 = 1;
  }
  eflag &= ~EFLAGS_AC_BIT;  // AC-bit = 0
  io_store_eflags(eflag);
  
  if (flag486 != 0)
  {
    cr0 = load_cr0();
    cr0 |= CR0_CACHE_DISABLE;  // キャッシュ禁止
    store_cr0(cr0);
  }

  i = memtest_sub(start, end);

  if (flag486 != 0)
  {
    cr0 = load_cr0();
    cr0 &= ~CR0_CACHE_DISABLE;
    store_cr0(cr0);
  }
  
  return i;
}
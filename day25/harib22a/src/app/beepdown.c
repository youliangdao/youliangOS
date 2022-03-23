void api_end(void);
int api_getkey(int data);
int api_alloctimer(void);
void api_inittimer(int timer, int data);
void api_settimer(int timer, int time);
void api_beep(int tone);

void HariMain(void)
{
    int i, timer;
    timer = api_alloctimer();
    api_inittimer(timer, 128);
    for ( i = 20000000; i >= 20000; i -= i / 100)
    {
        // 20KHz~20Hz：人間に聞こえる音の範囲
        // iは1%ずつ減らされていく
        api_beep(i);
        
    }
    
}
#include "strcmp.h"

int strcmp(char *s1, char *s2)
{
  while (*s1) {
    if (*s1 == *s2) {
      /* 次の文字へ */
      s1++;
      s2++;
      continue;
    }
    
    if (*s2 == 0) {
      /* 前の文字まで同じ状態で、s2の方が先に終端に来たら、s1の方が辞書順で後。 */
      return 1;
    }
      
    if (*s1 < *s2) {
      return -1;
    } else if (*s1 > *s2) {
      return 1;
    }
  }

  if (*s2 == 0) {
    return 0;
  } else {
    return -1;
  }
}

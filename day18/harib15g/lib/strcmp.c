#include "strcmp.h"

int strcmp(char *a, char *b)
{
  while (*a) {
    if (*a == *b) {
      /* 次の文字へ */
      a++;
      b++;
      continue;
    }

    if (*b == 0) {
      /* 前の文字まで同じ状態で、bの方が先に終端に来たら、aの方が辞書順で後。 */
      return 1;
    }

    if (*a < *b) {
      return -1;
    } else if (*a > *b) {
      return 1;
    }
  }

  if (*b == 0) {
    return 0;
  } else {
    return -1;
  }
}
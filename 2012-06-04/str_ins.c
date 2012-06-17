/*
 * srt_ins.c: 単純挿入法の実装
 */
#include "sort_util.h"

void str_ins(int a[], unsigned n)
{
  int i, j, w;

  /* 番人は用いていない */

  for (i = 1; i < n; i++) {
    w = a[i];
    j = i - 1;
    while (j >= 0 && compare(a[j], w) > 0) {
      assign(a, j + 1, a[j]);
      j--;
    }
    assign(a, j + 1, w);
  }
}

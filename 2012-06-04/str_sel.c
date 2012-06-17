/*
 * str_sel.c: 単純選択法の実装
 */
#include "sort_util.h"

void str_sel(int a[], unsigned n)
{
  int i,j,p,w;

  for (i = 0; i < n - 1; i++) {
    p = i; w = a[p];
    for (j = i + 1; j < n; j++)
      if (compare(a[j], w) < 0) {
	p = j;
	w = a[j];
      }
    swap(a, i, p);
  }
}

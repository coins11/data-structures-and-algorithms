/*
 * bubble.c: バブル整列法の実装
 */
#include "sort_util.h"

void bubble(int a[], unsigned n)
{
  int last, sw, i;

  sw = 0;			/* sw を n 以外の値で初期化 */
  last = 1;
  while (sw != n-1) {
    sw = n-1;
    for (i = n-1; i >= last; i--)
      if (compare(a[i], a[i - 1]) < 0) {
	swap(a, i, i - 1);
	sw = i;
      }
    last = sw + 1;
  }
}

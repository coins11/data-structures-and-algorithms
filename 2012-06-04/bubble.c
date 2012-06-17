/*
 * bubble.c: $B%P%V%k@0NsK!$N<BAu(B
 */
#include "sort_util.h"

void bubble(int a[], unsigned n)
{
  int last, sw, i;

  sw = 0;			/* sw $B$r(B n $B0J30$NCM$G=i4|2=(B */
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

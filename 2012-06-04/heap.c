/*
 * heap.c: ヒープ法の実装
 */
#include <stdio.h>
#include <limits.h>
#include "sort.h"
#include "sort_util.h"

static void sift(int a[], unsigned r, unsigned s)
{
  int i, j, w;

  if (ncalls == ULONG_MAX)
    /* オーバーフローが生じた */
    fprintf(stderr, "## warning: overflow of ncalls ##\n");
  ncalls++;

  i = r;
  j = 2 * r;
  w = a[r];

  while (j <= s) {
    if (j < s && compare(a[j], a[j + 1]) < 0)
      ++j;
    if (compare(w, a[j]) >= 0)
      break;
    assign(a, i, a[j]);
    i = j;
    j = 2 * i;
  }
  assign(a, i, w);
}

void heap(int a[], unsigned n)
{
  int r, m;

  r = n / 2;
  while (r > 0)
    sift(a, --r, n);
  m = n - 1;
  while (m > 0) {
    swap(a, 0, m);
    sift(a, 0, --m);
  }
}

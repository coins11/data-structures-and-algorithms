/*
 * quick.c: クイックソート法の実装
 */
#include <stdio.h>
#include <limits.h>
#include "sort.h"
#include "sort_util.h"

static int partition (int a[], int p, int r) 
{
  int x = a[r];
  int i = p - 1;
  int j;
  for (j = p; j < r; ++j)
    if (compare(a[j], x) <= 0)
      if (++i != j)
        swap(a, i, j);
  swap(a, ++i, r);
  return i;
}


static void quicksort(int a[], int p, int r)
{
  int q;

  if (ncalls == ULONG_MAX)
    /* オーバーフローが生じた */
    fprintf(stderr, "## warning: overflow of ncalls ##\n");
  ncalls++;

  if (p < r) {
    q = partition(a, p, r);
    quicksort(a, p, q - 1);
    quicksort(a, q + 1, r);
  }
}

void quick(int a[], unsigned n)
{
  quicksort(a,0,n-1);
}

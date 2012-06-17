/*
 * quick.c: $B%/%$%C%/%=!<%HK!$N<BAu(B
 */
#include <stdio.h>
#include <limits.h>
#include "sort.h"
#include "sort_util.h"

#define THRESHOLD 10  /* $B%-!<$,$3$N?t0J2<$J$iC1=cA^F~K!$r;H$&(B */

static void str_ins(int a[], unsigned int p, unsigned int r)
{
  int i, j, w;

  for (i = p; i <= r; ++i) {
    w = a[i];
    j = i - 1;
    while (j >= 0 && compare(a[j], w) > 0) {
      assign(a, j + 1, a[j]);
      j--;
    }
    assign(a, j + 1, w);
  }
}

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
    /* $B%*!<%P!<%U%m!<$,@8$8$?(B */
    fprintf(stderr, "## warning: overflow of ncalls ##\n");
  ncalls++;

  if (p < r) {
    if (r - p < THRESHOLD) {
      str_ins(a, p, r);
    } else {
      q = partition(a, p, r);
      quicksort(a, p, q - 1);
      quicksort(a, q + 1, r);
    }
  }
}

void quick_strins(int a[], unsigned int n)
{
  quicksort(a,0,n-1);
}

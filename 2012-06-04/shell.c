/*
 * shell.c: シェル法の実装
 */
#include <stdio.h>
#include <limits.h>
#include "sort.h"
#include "sort_util.h"

void shell(int a[], unsigned n)
{
  int i,j;
  int h = 1;

  while (h < n/3) h = 3*h + 1;
  while (h >= 1) {
    for (i = h; i < n; i++) {
      for (j = i; j >= h && compare(a[j], a[j-h]) < 0 ; j -= h) 
        swap(a, j, j-h);
    }
    h = h/3;
  }
}

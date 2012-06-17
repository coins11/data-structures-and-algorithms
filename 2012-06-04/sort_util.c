/*
 * sort_util.c: sort コマンドで用いるユーティリティ関数群の定義
 */
#include <stdio.h>
#include <limits.h>
#include "sort.h"

/* compare: 整数 i, j を比較し, i > j なら正の値, i == j なら 0,
            i < j なら負の値を返す */
int compare(int i, int j)
{
  if (ncompare == ULONG_MAX)
    /* オーバーフローが生じた */
    fprintf(stderr, "## warning: overflow occurred in compare() ##\n");

  if (vflag)
    printf("compare(%d, %d)\n", i, j);

  ncompare++;
  if (i > j)
    return 1;
  else if (i == j)
    return 0;
  else
    return -1;
}

/* swap: 配列 a の i 番目と j 番目の要素を入れ換える */
void swap(int a[], unsigned i, unsigned j)
{
  int tmp;

  if (nswap == ULONG_MAX)
    /* オーバーフローが生じた */
    fprintf(stderr, "## warning: overflow occurred in swap() ##\n");

  if (vflag)
    printf("swap: a[%d](= %d) <-> a[%d](= %d)\n", i, a[i], j, a[j]);

  nswap++;
  tmp = a[i];
  a[i] = a[j];
  a[j] = tmp;
}

/* assign: 配列 a の i 番目の要素に値 v を代入する */
void assign(int a[], unsigned i, int v)
{
  if (nassign == ULONG_MAX)
    /* オーバーフローが生じた */
    fprintf(stderr, "## warning: overflow occurred in assign() ##\n");

  if (vflag)
    printf("assign: a[%d] <- %d\n", i, v);

  nassign++;
  a[i] = v;
}

/* print_data: 配列 a[1], ..., a[n] の内容を出力する */
void print_data(int a[], unsigned n)
{
  int i;

  for (i = 0; i < n; i++)
    printf("%d ", a[i]);
  printf("\n");
}

/* print_stat: 統計情報を出力する */
void print_stat(void)
{
  printf("statistics:\n");
  printf("(a) no. of comparisons = %ld\n", ncompare);
  printf("(b) no. of swaps = %ld\n", nswap);
  printf("(c) no. of assignments = %ld\n", nassign);
  printf("(d) no. of moves ((b) * 2 + (c)) = %ld\n", 2 * nswap + nassign);
  printf("(e) no. of function calls = %ld\n", ncalls);
  printf("(f) max no. of call depths = %ld\n", max_call_depth);
}

/* 配列がソート済みであるか確かめる */
int verify(int a[], unsigned int n)
{
  int i, j;
  for (i = 0; i < n; ++i)
    for (j = i + 1; j < n; ++j)
      if (a[i] > a[j])
        return 0;
  return 1;
}

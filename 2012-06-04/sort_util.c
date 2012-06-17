/*
 * sort_util.c: sort $B%3%^%s%I$GMQ$$$k%f!<%F%#%j%F%#4X?t72$NDj5A(B
 */
#include <stdio.h>
#include <limits.h>
#include "sort.h"

/* compare: $B@0?t(B i, j $B$rHf3S$7(B, i > j $B$J$i@5$NCM(B, i == j $B$J$i(B 0,
            i < j $B$J$iIi$NCM$rJV$9(B */
int compare(int i, int j)
{
  if (ncompare == ULONG_MAX)
    /* $B%*!<%P!<%U%m!<$,@8$8$?(B */
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

/* swap: $BG[Ns(B a $B$N(B i $BHVL\$H(B j $BHVL\$NMWAG$rF~$l49$($k(B */
void swap(int a[], unsigned i, unsigned j)
{
  int tmp;

  if (nswap == ULONG_MAX)
    /* $B%*!<%P!<%U%m!<$,@8$8$?(B */
    fprintf(stderr, "## warning: overflow occurred in swap() ##\n");

  if (vflag)
    printf("swap: a[%d](= %d) <-> a[%d](= %d)\n", i, a[i], j, a[j]);

  nswap++;
  tmp = a[i];
  a[i] = a[j];
  a[j] = tmp;
}

/* assign: $BG[Ns(B a $B$N(B i $BHVL\$NMWAG$KCM(B v $B$rBeF~$9$k(B */
void assign(int a[], unsigned i, int v)
{
  if (nassign == ULONG_MAX)
    /* $B%*!<%P!<%U%m!<$,@8$8$?(B */
    fprintf(stderr, "## warning: overflow occurred in assign() ##\n");

  if (vflag)
    printf("assign: a[%d] <- %d\n", i, v);

  nassign++;
  a[i] = v;
}

/* print_data: $BG[Ns(B a[1], ..., a[n] $B$NFbMF$r=PNO$9$k(B */
void print_data(int a[], unsigned n)
{
  int i;

  for (i = 0; i < n; i++)
    printf("%d ", a[i]);
  printf("\n");
}

/* print_stat: $BE}7W>pJs$r=PNO$9$k(B */
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

/* $BG[Ns$,%=!<%H:Q$_$G$"$k$+3N$+$a$k(B */
int verify(int a[], unsigned int n)
{
  int i, j;
  for (i = 0; i < n; ++i)
    for (j = i + 1; j < n; ++j)
      if (a[i] > a[j])
        return 0;
  return 1;
}

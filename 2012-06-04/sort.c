/*
 * sort: $B@0Ns%W%m%0%i%`$NK\BN(B. $BF~NO%G!<%?$rFI$_9~$_(B, $BE,@Z$J@0Ns%"%k%4(B
 * $B%j%:%`$r5/F0$9$k(B.
 */

#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include "sort_util.h"

/* $B30ItDj5A$N@0Ns4X?t(B */
void str_sel(int a[], unsigned int n); /* $BC1=cA*BrK!(B */
void heap(int a[], unsigned int n);	/* $B%R!<%W@0NsK!(B */
void str_ins(int a[], unsigned int n); /* $BC1=cA^F~K!(B */
void shell(int a[], unsigned int n);	/* $B%7%'%kK!(B */
void bubble(int a[], unsigned int n);	/* $B%P%V%k@0NsK!(B */
void quick(int a[], unsigned int n);	/* $B%/%$%C%/%=!<%HK!(B */
void quick_strins(int a[], unsigned int n); /* $B%/%$%C%/%=!<%HK!!J:G=*CJ3,$KC1=cA^F~K!$rMxMQ!K(B */

/* $BBg0hJQ?t(B */
unsigned long ncompare;		/* $BHf3S2s?t$r%+%&%s%H(B */
unsigned long nswap;		/* $B%9%o%C%W2s?t$r%+%&%s%H(B */
unsigned long nassign;		/* $BBeF~2s?t$r%+%&%s%H(B */
unsigned long ncalls;		/* $B4X?t8F=P$72s?t$r%+%&%s%H(B */
unsigned long max_call_depth;	/* $B:F5"8F=P$7$N?<$5$N:GBgCM(B */
short vflag;			/* $B>\:Y%b!<%I$+$I$&$+$N%U%i%0(B */

int main(int argc, char *argv[])
{
  unsigned n;			/* $B%-!<$NAm?t(B */
  int *a;			/* $BF~NO%G!<%?$rF~$l$k@0?tG[Ns(B */
  FILE *fp;
  short cflag;			/* $B7k2L$,@5$7$$$+$I$&$+$N%U%i%0(B */
  int i;

  /* $BBg0hJQ?t$N=i4|2=(B */
  ncompare = 0; 
  nswap = 0;
  nassign = 0;
  ncalls = 0;
  max_call_depth = 0;

  if (argc == 1) {
    /* $B0z?t$,M?$($i$l$J$+$C$?>l9g(B: $B%X%k%W$r=PNO$7=*N;(B */
    fprintf(stderr, "usage: sort [-v] method [filename]\n");
    exit(1);
  }

  if (strcmp(argv[1], "-v") == 0) {
    /* $B>\:Y%b!<%I$,;XDj$5$l$?>l9g(B */
    vflag = 1;
    argc--;			/* $B0z?t$N?t$r(B1$B8:$i$9(B */
    argv++;			/* $B0z?t$X$N%]%$%s%?$r(B1$B$D?J$a$k(B */
  } else
    vflag = 0;

  if (argc >= 4) {
    /* $B0z?t$,B?2a$.$k>l9g$O%(%i!<(B: $B%X%k%W$r=PNO$7=*N;(B */
    fprintf(stderr, "usage: sort method [filename]\n");
    exit(1);
  } else if (argc == 2) {
    /* $B%U%!%$%kL>$,M?$($i$l$J$+$C$?>l9g(B: $BI8=`F~NO$+$i%G!<%?$rFI$_9~$`(B */
    printf("no. of keys:\n");
    scanf("%d", &n);		/* $B%-!<$NAm?t$rFI$_9~$`(B */
    a = (int *)malloc(sizeof(int) * n); /* $BG[NsNN0h$N3NJ](B */
    printf("input data (a[0] to a[%d]):\n", n-1);
    for (i = 0; i < n; i++)
      scanf("%d", &a[i]);	/* $BF~NO%G!<%?$rFI$_9~$`(B */
  } else {
    /* $B%U%!%$%kL>$,M?$($i$l$?$H$-(B */
    if ((fp = fopen(argv[2], "r")) == NULL) {
      fprintf(stderr, "cannot open file %s\n", argv[2]);
      exit(1);
    }
    fscanf(fp, "%d\n", &n);	/* $B%-!<$NAm?t$rFI$_9~$`(B */
    a = (int *)malloc(sizeof(int) * n); /* $BG[NsNN0h$N3NJ](B */
    for (i = 0; i < n; i++)
      fscanf(fp, "%d\n", &a[i]); /* $BF~NO%G!<%?$rFI$_9~$`(B */
    fclose(fp);
  }

  printf("###################\n");

  if (vflag) {
    /* $BF~NO%G!<%?$N=PNO(B */
    printf("initial data:\n");
    print_data(a, n);
  }

  /* $B4X?tL>$r%A%'%C%/$7(B, $BBP1~$9$k4X?t$r8F$S=P$9(B */
  if (strcmp(argv[1], "str_sel") == 0)
    str_sel(a, n);
  else if (strcmp(argv[1], "heap") == 0)
    heap(a, n);
  else if (strcmp(argv[1], "str_ins") == 0)
    str_ins(a, n);
  else if (strcmp(argv[1], "bubble") == 0)
    bubble(a, n);
  else if (strcmp(argv[1], "quick") == 0)
    quick(a, n);
  else if (strcmp(argv[1], "shell") == 0)
    shell(a, n);
  else if (strcmp(argv[1], "quick_strins") == 0)
    quick_strins(a, n);
  else {
    fprintf(stderr, "wrong function name: %s\n", argv[1]);
    exit(1);
  }

  /* $B@0Ns7k2L$N%G!<%?$N=PNO(B */
  printf("sorted data:\n");
  print_data(a, n);
  
  if (!verify(a, n))
    printf("!! verification failure !!\n");

  /* $BE}7W>pJs$N=PNO(B */
  print_stat();

  free(a);			/* $BG[Ns(B a $B$K3d$jEv$F$?NN0h$r2rJ|(B */
  
  return 0;
}

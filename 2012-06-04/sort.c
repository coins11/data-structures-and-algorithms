/*
 * sort: 整列プログラムの本体. 入力データを読み込み, 適切な整列アルゴ
 * リズムを起動する.
 */

#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include "sort_util.h"

/* 外部定義の整列関数 */
void str_sel(int a[], unsigned int n); /* 単純選択法 */
void heap(int a[], unsigned int n);	/* ヒープ整列法 */
void str_ins(int a[], unsigned int n); /* 単純挿入法 */
void shell(int a[], unsigned int n);	/* シェル法 */
void bubble(int a[], unsigned int n);	/* バブル整列法 */
void quick(int a[], unsigned int n);	/* クイックソート法 */
void quick_strins(int a[], unsigned int n); /* クイックソート法（最終段階に単純挿入法を利用） */

/* 大域変数 */
unsigned long ncompare;		/* 比較回数をカウント */
unsigned long nswap;		/* スワップ回数をカウント */
unsigned long nassign;		/* 代入回数をカウント */
unsigned long ncalls;		/* 関数呼出し回数をカウント */
unsigned long max_call_depth;	/* 再帰呼出しの深さの最大値 */
short vflag;			/* 詳細モードかどうかのフラグ */

int main(int argc, char *argv[])
{
  unsigned n;			/* キーの総数 */
  int *a;			/* 入力データを入れる整数配列 */
  FILE *fp;
  short cflag;			/* 結果が正しいかどうかのフラグ */
  int i;

  /* 大域変数の初期化 */
  ncompare = 0; 
  nswap = 0;
  nassign = 0;
  ncalls = 0;
  max_call_depth = 0;

  if (argc == 1) {
    /* 引数が与えられなかった場合: ヘルプを出力し終了 */
    fprintf(stderr, "usage: sort [-v] method [filename]\n");
    exit(1);
  }

  if (strcmp(argv[1], "-v") == 0) {
    /* 詳細モードが指定された場合 */
    vflag = 1;
    argc--;			/* 引数の数を1減らす */
    argv++;			/* 引数へのポインタを1つ進める */
  } else
    vflag = 0;

  if (argc >= 4) {
    /* 引数が多過ぎる場合はエラー: ヘルプを出力し終了 */
    fprintf(stderr, "usage: sort method [filename]\n");
    exit(1);
  } else if (argc == 2) {
    /* ファイル名が与えられなかった場合: 標準入力からデータを読み込む */
    printf("no. of keys:\n");
    scanf("%d", &n);		/* キーの総数を読み込む */
    a = (int *)malloc(sizeof(int) * n); /* 配列領域の確保 */
    printf("input data (a[0] to a[%d]):\n", n-1);
    for (i = 0; i < n; i++)
      scanf("%d", &a[i]);	/* 入力データを読み込む */
  } else {
    /* ファイル名が与えられたとき */
    if ((fp = fopen(argv[2], "r")) == NULL) {
      fprintf(stderr, "cannot open file %s\n", argv[2]);
      exit(1);
    }
    fscanf(fp, "%d\n", &n);	/* キーの総数を読み込む */
    a = (int *)malloc(sizeof(int) * n); /* 配列領域の確保 */
    for (i = 0; i < n; i++)
      fscanf(fp, "%d\n", &a[i]); /* 入力データを読み込む */
    fclose(fp);
  }

  printf("###################\n");

  if (vflag) {
    /* 入力データの出力 */
    printf("initial data:\n");
    print_data(a, n);
  }

  /* 関数名をチェックし, 対応する関数を呼び出す */
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

  /* 整列結果のデータの出力 */
  printf("sorted data:\n");
  print_data(a, n);
  
  if (!verify(a, n))
    printf("!! verification failure !!\n");

  /* 統計情報の出力 */
  print_stat();

  free(a);			/* 配列 a に割り当てた領域を解放 */
  
  return 0;
}

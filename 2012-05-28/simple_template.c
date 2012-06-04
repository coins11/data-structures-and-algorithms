/* 単純照合のプログラム simple.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int Ncomp = 0; /* 比較回数をカウントする大域変数 */
#define TRACE

int getFileSize(char *fname)
{
  int fd, sz;

  if ((fd = open(fname, O_RDONLY)) == -1) {
    fprintf(stderr, "open");
    exit(1);
  }
  if ((sz = lseek(fd, 0, SEEK_END)) == -1) {
    fprintf(stderr, "lseek");
    exit(1);
  }
  close(fd);

  return sz;
}

char *patget(char *s)
{
  char *pat;

  if ((pat = calloc(strlen(s) + 1, sizeof(char))) == NULL) {
    fprintf(stderr, "calloc");
    exit(1);
  }
  strcpy(pat, s);

  return pat;
}

char *txtget(char *fname)
{
  int cnt = 0, n;
  char buf[BUFSIZ];
  char *str;
  FILE *fp;

  if ((str = calloc(getFileSize(fname) + 1, sizeof(char))) == NULL) {
    fprintf(stderr, "calloc");
    exit(1);
  }

  if ((fp = fopen(fname, "r")) == NULL) {
    fprintf(stderr, "fopen");
    exit(1);
  }

  for (cnt = 0; (n = fread(buf, sizeof(char), sizeof(buf), fp)) != 0; cnt += n)
    memcpy(&str[cnt], buf, n);

  fclose(fp);

  return str;
}

/* 文字の比較と比較回数の収集を行う*/
int compare(char a, char b)
{
#ifdef TRACE
  printf("compare(%c, %c)\n", a, b);
#endif
  Ncomp++; /* 比較回数を1増やす */
  if (a == b)
    return 1;
  else
    return 0;
}

/* 単純照合 */
int simple_search(char *text, int tlen, char *pat, int plen)
{
}

int main(int argc, char *argv[])
{
  char *text; /* テキストの文字配列 */
  char *pat; /* パターンの文字配列 */
  int tlen; /* テキスト長（文字数） */
  int plen; /* パターン長（文字数） */
  int pos; /* 照合した位置 */

  /* 引数をチェック */
  if (argc != 3) {
    fprintf(stderr, "wrong no. of arguments\n");
    fprintf(stderr, "usage: %s pat fname\n", argv[0]);
    exit(1);
  }

  pat = patget(argv[1]);
  plen = strlen(pat); /* パターンの文字数を求める */

  /* 第2引数で指定されたファイル名のファイルを読み込む */
  text = txtget(argv[2]);
  tlen = strlen(text); /* テキストの文字数を求める */

  /* 単純照合の関数を呼び出す */
  pos = simple_search(text, tlen, pat, plen);

  if (pos >= 0)
    printf("Found at %d\n", pos);
  else
    printf("Not found\n");
  printf("no. of comparisons = %d\n", Ncomp);

  free(pat); /* patのメモリ領域を解放 */
  free(text); /* textのメモリ領域を解放 */

  return 0;
}

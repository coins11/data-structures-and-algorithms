#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int Ncomp = 0; /* ��Ӳ���򥫥���Ȥ�������ѿ� */
// #define TRACE

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

/* ʸ������Ӥ���Ӳ���μ�����Ԥ�*/
int compare(char a, char b)
{
#ifdef TRACE
  printf("compare(%c, %c)\n", a, b);
#endif
  Ncomp++; /* ��Ӳ����1���䤹 */
  if (a == b)
    return 1;
  else
    return 0;
}

void kmp_table(char *pat, int plen, int* table)
{
  int i = 2, j = 0;
  table[0] = 0;
  table[1] = 0;
  while (i < plen) {
    if (pat[i - 1] == pat[j]) {
      table[i] = ++j;
      ++i;
    } else if (j > 0) {
      j = table[j];
    } else {
      table[i++] = 0;
    }
  }
  printf("table: ");
  for (i = 0; i < plen; ++i)
    printf("%d ", table[i]);
  printf("\n");
}

int kmp_search(char *text, int tlen, char *pat, int plen)
{
  int i;
  int text_pos = 0, pat_pos = 0;
  int *next = (int*)(malloc(sizeof(int) * plen));
  if (next == NULL) {
    printf("memory for next[] cannot be allocated.\n");
    exit(EXIT_FAILURE);
  }
  kmp_table(pat, plen, next);
  
  while (text_pos < tlen) {
    if (compare(text[text_pos], pat[pat_pos])) {
      ++text_pos;
      ++pat_pos;
      if (pat_pos == plen)
        return text_pos - plen;
    } else if (pat_pos == 0) {
      ++text_pos;
    } else {
      pat_pos = next[pat_pos];
    }
  }
  return -1;
}

int main(int argc, char *argv[])
{
  char *text; /* �ƥ����Ȥ�ʸ������ */
  char *pat; /* �ѥ������ʸ������ */
  int tlen; /* �ƥ�����Ĺ��ʸ������ */
  int plen; /* �ѥ�����Ĺ��ʸ������ */
  int pos; /* �ȹ礷������ */

  /* ����������å� */
  if (argc != 3) {
    fprintf(stderr, "wrong no. of arguments\n");
    fprintf(stderr, "usage: %s pat fname\n", argv[0]);
    exit(1);
  }

  pat = patget(argv[1]);
  plen = strlen(pat); /* �ѥ������ʸ��������� */

  /* ��2�����ǻ��ꤵ�줿�ե�����̾�Υե�������ɤ߹��� */
  text = txtget(argv[2]);
  tlen = strlen(text); /* �ƥ����Ȥ�ʸ��������� */

  /* ñ��ȹ�δؿ���ƤӽФ� */
  pos = kmp_search(text, tlen, pat, plen);

  if (pos >= 0)
    printf("Found at %d\n", pos);
  else
    printf("Not found\n");
  printf("no. of comparisons = %d\n", Ncomp);

  free(pat); /* pat�Υ����ΰ����� */
  free(text); /* text�Υ����ΰ����� */

  return 0;
}

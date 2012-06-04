/*********************************************************
 *                      dijkstra.c                       *
 *********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "debug.h"
#include "weight.h"

typedef enum {FALSE, TRUE} Bool;

/* 対象のグラフの定義 */
#define N 6
int w[N][N] = {{ 0, M,  M, 8, 15, M}, \
							 {10, 0, 24, M,  8, M}, \
							 { M, M,  0, M,  M, 6}, \
							 { M, M,  M, 0,  5, M}, \
							 { M, M, 12, M,  0, 7}, \
							 { M, M,  3, M,  M, 0}};

Bool S[N];		/* 処理済みの頂点の集合 S */
int Scount;	  /* 集合 S の要素数 */
Weight d[N][N];  /* 重みの累積値を格納する行列 */
int p[N][N];

void Floyd()
{
  int i, j, k, can;
  
  for (i = 0; i < N; ++i) {
    for (j =0; j < N; ++j) {
      d[i][j] = w[i][j];
      p[i][j] = i;
    }
  }

  for (k = 0; k < N; ++k) {
    for (i = 0; i < N; ++i) {
      for (j = 0; j < N; ++j) {
        can = d[i][k] + d[k][j];
        if (can < d[i][j]) {
          d[i][j] = can;
          p[i][j] = p[k][j];
        }
      }
    }
  }
}

int main(int argc, char *argv[])
{
  int i, j;
  Floyd();

 /*  開始点から各頂点への最短距離，および最短経路を出力するようにする */
  for (i = 0; i < N; ++i)
  printf("from %d\n", i);
  for (j = 0; j < N; ++j) {
    printf(" -> %d : <%d>\t", i, d[i][j]);
  }
	return 0;
}

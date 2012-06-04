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
Weight d[N];  /* 重みの累積値を格納する行列 */
int parent[N];

void add(int p, Bool S[])
{
  if (!S[p]) {
    S[p] = TRUE;
    ++Scount;
  }
}

Bool remain(void)
{
  int i;
  for (i = 0; i < N; ++i)
    if (!S[i])
      return TRUE;
  return FALSE;
}

int select_min(void)
{
  int i;
  int min = M;
  int minIdx = -1;
  for (i = 0; i < N; ++i) {
    if (S[i])
      continue;
    if (weight_compare(d[i], min) == -1) {
      min = d[i];
      minIdx = i;
    }
  }
  return minIdx;
}

Bool member(int u, int x)
{
  return w[u][x] != M;
}

void Dijkstra(int start)
{
  int i, u, x, k;

  // initialize
  for (i = 0; i < N; ++i) {
    S[i] = FALSE;
    parent[i] = -1;
  }
  Scount = 0;

	add(start, S);
  for (i = 0; i < N; i++) 
    d[i] = w[start][i];
  while (remain()) {
    u = select_min();
    if (u == -1) break;
    add(u, S);
    if (parent[u] < 0)
      parent[u] = start;
    for (x = 0; x < N; x++) {
      if (member(u, x)) {
        k = d[u] + w[u][x];
        if (weight_compare(k, d[x]) == -1) {
         d[x] = k;
         parent[x] = u;
        }
			}
    }
	}
}

void print_route(int from, int to)
{
  if (parent[to] < 0) {
    printf("%d ", from);
    return;
  }
  print_route(from, parent[to]);
  printf("-> %d ", to);
}

int main(int argc, char *argv[])
{
  int i, start;
	if (argc != 2) {
		fprintf(stderr, "Usage: program nodeid\n");
		exit(1);
	}
  start = atoi(argv[1]);

	Dijkstra(start);

 /*  開始点から各頂点への最短距離，および最短経路を出力するようにする */
  printf("from %d\n", start);
  for (i = 0; i < N; ++i) {
    printf(" -> %d : <%d>\t", i, d[i]);
    if (d[i] == -1) {
      printf("no route\n");
    } else if (d[i] == 0) {
      printf("start point\n");
    } else {
      print_route(start, i);
      printf("\n");
    }
  }
	return 0;
}

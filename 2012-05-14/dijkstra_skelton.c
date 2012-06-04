/*********************************************************
 *                      dijkstra.c                       *
 *********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "debug.h"

typedef enum {FALSE, TRUE} Bool;
typedef int Weight;

#define M (-1)		/* ̵����νŤߤ�ɽ�� */

/* �оݤΥ���դ���� */
#define N 6
int w[N][N] = {{ 0, M,  M, 8, 15, M}, \
							 {10, 0, 24, M,  8, M}, \
							 { M, M,  0, M,  M, 6}, \
							 { M, M,  M, 0,  5, M}, \
							 { M, M, 12, M,  0, 7}, \
							 { M, M,  3, M,  M, 0}};

Bool S[N];		/* �����Ѥߤ�ĺ���ν��� S */
int Scount;	  /* ���� S �����ǿ� */
Weight d[N];  /* �Ťߤ������ͤ��Ǽ������� */

void add(int p, Bool S[])
{
}

Bool remain(void)
{
}

int select_min(void)
{
}

Bool member(int u, int x)
{
}

void Dijkstra(int p)
{
  int i, u, x, k;

	add(p, S);
  for (i = 0; i < N; i++) 
		d[i] = w[p][i];
	while (remain()) {
		u = select_min();
		add(u, S);
		for (x = 0; x < N; x++) {
			if (member(u, x)) {
				k = d[u] + w[u][x];
				if (k < d[x])
					d[x] = k;
			}
		}		
	}
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "Usage: program nodeid\n");
		exit(1);
	}

	Dijkstra(atoi(argv[1]));

 /*  �����������ĺ���ؤκ�û��Υ������Ӻ�û��ϩ����Ϥ���褦�ˤ��� */ /*  �����������ĺ���ؤκ�û��Υ������Ӻ�û��ϩ����Ϥ���褦�ˤ��� */
    /*  �����������ĺ���ؤκ�û��Υ������Ӻ�û��ϩ����Ϥ���褦�ˤ��� */	/*  �����������ĺ���ؤκ�û��Υ������Ӻ�û��ϩ����Ϥ���褦�ˤ��� */
	return 0;
}

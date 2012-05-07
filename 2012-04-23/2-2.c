#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct queue {
    int *circbuf;
    size_t bsize;
    size_t qhead;
    size_t qsize;
} queue_t;

queue_t *initqueue()
{
    queue_t *q = malloc(sizeof(queue_t));
    if(!q) return NULL;
    q->circbuf = NULL;
    q->bsize = 0;
    q->qhead = 0;
    q->qsize = 0;
    return q;
}

void releasequeue(queue_t *q)
{
    assert(q);
    free(q->circbuf);
    free(q);
}

int enqueue(queue_t *q, int v)
{
    assert(q);
    if(q->bsize == q->qsize){
        size_t nbsize = q->bsize ? q->bsize*2 : 16;
        int* tmp = realloc(q->circbuf, sizeof(int)*nbsize);
        if(!tmp) return -1;
        memcpy(tmp+q->bsize, tmp,sizeof(int)*q->qhead);
        q->circbuf = tmp;
        q->bsize = nbsize;
    }
    q->circbuf[(q->qhead+q->qsize)%q->bsize] = v;
    q->qsize++;
    return 0;
}

int dequeue(queue_t *q, int *dest)
{
    assert(q && dest);
    if(q->qsize){
        *dest = q->circbuf[q->qhead];
        q->qhead = (q->qhead+1)%q->bsize;
        q->qsize--;
    }
    else return -1;
}

int main(void)
{
    int i = 1, j, dest;
    int arr[] = {3, 5, 7, 0};
    queue_t *q = initqueue();
    while(i != 201){
        enqueue(q, i);
        for(j = 0; arr[j]; j++)
            if(i && i%arr[j] == 0){
                dequeue(q, &dest);
                printf("%d\n", dest);
            }
        i++;
    }
    return 0;
}

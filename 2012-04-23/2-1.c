#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct elem {
    int v;
    struct elem *next;
} elem_t;

typedef struct queue {
    struct elem *head, *tail;
} queue_t;

queue_t *initqueue()
{
    queue_t *q = malloc(sizeof(queue_t));
    if(!q) return NULL;
    q->head = NULL;
    q->tail = NULL;
    return q;
}

void releasequeue(queue_t *q)
{
    elem_t *e1, *e2;
    assert(q);
    e2 = q->head;
    while(e1){
        e1 = (e2 = e1)->next;
        free(e2);
    }
    free(q);
}

int enqueue(queue_t *q, int v)
{
    assert(q);
    if(q->tail){
        q->tail->next = malloc(sizeof(elem_t));
        if(!q->tail->next) return -1;
        q->tail = q->tail->next;
    }
    else{
        q->head = q->tail = malloc(sizeof(elem_t));
        if(!q->tail) return -1;
    }
    q->tail->v = v;
    q->tail->next = NULL;
    return 0;
}

int dequeue(queue_t *q, int *dest)
{
    assert(q && dest);
    if(q->head){
        elem_t *nh = q->head->next;
        *dest = q->head->v;
        free(q->head);
        if(!(q->head = nh)) q->tail = NULL;
        return 0;
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

#include <stdio.h>
#include <stdlib.h>

typedef struct cell {
    int v;
    struct cell *next;
} cell_t;

cell_t *head = NULL;

int append(int n)
{
    cell_t **i = &head;
    while(*i) i = &((*i)->next);
    if(*i = malloc(sizeof(cell_t))){
        (*i)->v = n;
        (*i)->next = NULL;
        return 0;
    }
    else return -1;
}

cell_t *search(int n)
{
    cell_t *i = head;
    for(; i && i->v != n; i = i->next);
    return i;
}

int insert(cell_t *c, int n)
{
    cell_t *nc = malloc(sizeof(cell_t));
    if(nc){
        nc->v = n;
        nc->next = c->next;
        c->next = nc;
        return 0;
    }
    else return -1;
}

int delete(cell_t *c)
{
    cell_t *i = head, *prev = NULL;
    for(; i && i != c; i = i->next) prev = i;
    if(!i) return -1;
    *(prev ? &prev->next : &head) = i->next;
    free(i);
}

void printlist(void)
{
    cell_t *i = head;
    for(; i; i = i->next) printf("%d ", i->v);
    printf("\n");
}

int main(void){
    int i;
    for(i = 0; i != 10; i++) append(i);
    printlist();
    printf("%d\n", search(0)->next->v);
    printf("%d\n", search(6)->next->v);
    insert(search(8)->next, 10);
    delete(search(5));
    printlist();
    return 0;
}

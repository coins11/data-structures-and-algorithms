#ifndef INTLIST_H__
#define INTLIST_H__

typedef struct cell_ {
   int elem;
   struct cell_ *next;
   struct cell_ *prev;
} cell;

void initlist(void);
void append(int elem);
cell* search(int elem);
void insert(cell *precell, int elem);
void delete(cell *target);
void printlist(void);


#endif


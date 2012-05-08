#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define MAX_ELEMS 32
#define NEXT(IDX) ( ((IDX)+1) % (MAX_ELEMS+1) )

static int queue_array[MAX_ELEMS+1];
static int idx_head = 0;
static int idx_tail = 0;

void initqueue(void) {
}

void enqueue(int elem) {
   idx_tail = NEXT(idx_tail);
   assert(idx_tail != idx_head);
   queue_array[idx_tail] = elem;
}

int dequeue(void) {
   idx_head = NEXT(idx_head);
   int elem = queue_array[idx_head];
   assert(NEXT(idx_tail) != idx_head);
   return elem;
}

void printqueue(void) {
   int idx = NEXT(idx_head);
   while(idx_head != idx_tail) {
      printf("%d  ", queue_array[idx]);
      if(idx == idx_tail) break;
      idx = NEXT(idx);
   }
   putchar('\n');
}


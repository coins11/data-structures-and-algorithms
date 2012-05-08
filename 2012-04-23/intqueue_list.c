#include <assert.h>
#include "intlist.h"
#include "intqueue.h"

extern cell *head;

void printqueue(void) {
   printlist();
}

void initqueue(void) {
   initlist();
}

void enqueue(int elem) {
   append(elem);
}

int dequeue(void) {
   assert(head->prev != head);
   int elem = head->next->elem;
   delete(head->next);
   return elem;
}



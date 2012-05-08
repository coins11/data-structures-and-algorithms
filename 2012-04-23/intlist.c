#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "intlist.h"

cell *head = NULL;

static cell* new_cell(int elem) {
   cell *ret = (cell*)malloc(sizeof(cell));
   if(ret == NULL) {
      perror("malloc");
      exit(EXIT_FAILURE);
   }
   ret->elem = elem;
   return ret;
}

void initlist(void) {
   assert(head == NULL);
   head = new_cell(0);
   head->next = head;
   head->prev = head;
}

void append(int elem) {
   insert(head->prev, elem);
}

cell* search(int elem) {
   assert(head);
   for(cell *p = head->next; p != head; p = p->next) {
      if(p->elem == elem) return p;
   }
   return NULL;
}

void insert(cell *precell, int elem) {
   assert(precell);
   cell *c = new_cell(elem);
   if(c == NULL) return;
   c->prev = precell;
   c->next = precell->next;
   c->prev->next = c;
   c->next->prev = c;
}

void delete(cell *target) {
   assert(target);
   if(target->next) target->next->prev = target->prev;
   if(target->prev) target->prev->next = target->next;
   free(target);
}

void printlist(void) {
   assert(head);
   cell *p = head->next;
   while(p != head) {
      printf("%2d ", p->elem);
      p = p->next;
   }
   putchar('\n');
}


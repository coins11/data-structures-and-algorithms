#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "intlist.h"

extern cell *head;

int main(void) {
   initlist();
   append(0);
   append(1);
   append(2);
   insert(search(1), 3);
   insert(head, 4);
   printlist();
   for(int i = 0; i < 5; ++i) {
      delete(search(i));
      printlist();
   }
   return 0;
}


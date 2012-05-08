#include <stdio.h>
#include <stdlib.h>
#include "intqueue.h"

int main(int argc, char *argv[]) {
   initqueue();
   for(int i = 0; i < 5; ++i) {
      enqueue(i);
      printqueue();
   }
   for(int i = 0; i < 5; ++i) {
      dequeue();
      printqueue();
   }
   for(int i = 0; i < 5; ++i) {
      enqueue(i);
      printqueue();
      dequeue();
      printqueue();
   }
   dequeue();
   return 0;
}


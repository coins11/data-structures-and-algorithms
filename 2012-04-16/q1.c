#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define SWAP(TYPE, A, B) do { TYPE t = A; A = B; B = t; } while(0)

unsigned euclid1(unsigned a, unsigned b) {
   assert(a > 0 && b > 0);
   if(a < b) SWAP(unsigned, a, b);
   while(b != 0) {
      unsigned r = a % b;
      a = b;
      b = r;
   }
   return a;
}

unsigned euclid2(unsigned a, unsigned b) {
   assert(a > 0 && a >= b);
   return b == 0 ? a : euclid2(b, a % b);
}

int main(int argc, char *argv[]) {
   if(argc != 3) return 1;
   unsigned a = (unsigned)atol(argv[1]);
   unsigned b = (unsigned)atol(argv[2]);
   unsigned result1 = euclid1(a, b);
   unsigned result2 = euclid2(a, b);
   printf("euclid1(%s,%s) = %u\n", argv[1], argv[2], result1);
   printf("euclid2(%s,%s) = %u\n", argv[1], argv[2], result2);
   return 0;
}


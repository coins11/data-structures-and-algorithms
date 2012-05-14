#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b);

int main(int argc, char **argv)
{
  int g;

  int a, b;
  a = atoi(argv[1]);
  b = atoi(argv[2]);
  if (a > 0 && b > 0) {
    g = gcd(a, b);
    printf("gcd = %d\n", g);
  } else {
    printf("out of range.\n");
  }

  return 0;
}

int gcd(int a, int b)
{
  int x, y, r;
  if (a >= b) {
    x = a;
    y = b;
  } else {
    x = b;
    y = a;
  }

  while (y != 0) {
    r = x % y;
    x = y;
    y = r;
  }

  return x;
}

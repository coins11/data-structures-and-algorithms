#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b);

int main(int argc, char **argv)
{
  int g;

  int a, b;
  a = atoi(argv[1]);
  b = atoi(argv[2]);
  if (a > 0 && b >= 0) {
    if (a >= b)
      g = gcd(a, b);
    else
      g = gcd(b, a);
    
    printf("gcd = %d\n", g);
  } else {
    printf("out of range.\n");
  }

  return 0;
}

int gcd(int a, int b)
{
  if (b == 0)
    return a;
  else
    return gcd(b, a % b);
}

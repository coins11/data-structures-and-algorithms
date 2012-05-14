#include <stdio.h>
#include <stdlib.h>

int gcd(int, int);

int main(int argc, char **argv)
{
  int g;

  g = gcd(atoi(argv[1]), atoi(argv[2]));

  printf("gcd = %d\n", g);

  return 0;
}

int gcd (int a, int b)
{
  int i;

  /* Calculate min(a, b) and substitute it for i */
  if (a < b)
    i = a;
  else
    i = b;

  for (; i > 1; i--)
    if ((a % i + b % i) == 0)
      break;
  
  return i;
}


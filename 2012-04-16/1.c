#include <stdio.h>

int gcd(int a, int b)
{
    int i = a < b ? a : b;
    for(; i > 1; i--) if(!(a%i + b%i)) break;
    return i;
}

int main(void)
{
    int i, j;
    for(i = 1; i != 21; i++)
        for(j = 1; j != 21; j++)
            printf("gcd(%d, %d) = %d\n", i, j, gcd(i, j));
    return 0;
}

#include <stdio.h>

int gcd(int a, int b)
{
    return b ? gcd(b, a % b) : a;
}

int main(void)
{
    int i, j;
    for(i = 1; i != 21; i++)
        for(j = 1; j != 21; j++)
            printf("gcd(%d, %d) = %d\n", i, j, gcd(i, j));
    return 0;
}

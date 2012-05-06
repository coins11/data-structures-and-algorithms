#include <stdio.h>

#define SWAP(_type, a, b) do{ \
        _type _tmp = a; \
        a = b; \
        b = _tmp; \
    } while(0)

int gcd(int a, int b)
{
    if(a < b) SWAP(int, a, b);
    while(b){
        a = a % b;
        SWAP(int, a, b);
    }
    return a;
}

int main(void)
{
    int i, j;
    for(i = 1; i != 21; i++)
        for(j = 1; j != 21; j++)
            printf("gcd(%d, %d) = %d\n", i, j, gcd(i, j));
    return 0;
}

#include<alloca.h>
#include<stdio.h>
#include<string.h>

#define SWAP(_type, a, b) do{ \
        _type _tmp = a; \
        a = b; \
        b = _tmp; \
    } while(0)

void quicksort(int *arr, size_t size)
{
    size_t *stack = alloca(sizeof(size_t)*(size*2)), stacktop = 1;
    stack[0] = 0, stack[1] = size;
    while(stacktop--){
        size_t base = stack[stacktop*2], i = 1, j = stack[stacktop*2+1];
        if(j-- < 1) continue;
        while(i <= j){
            while(i != stack[stacktop*2+1] && arr[base+i] < arr[base]) i++;
            while(j && arr[base] <= arr[base+j]) j--;
            if(i < j) SWAP(int, arr[base+i], arr[base+j]);
        }
        SWAP(int, arr[base], arr[base+j]);
        stack[stacktop*2] = base+i;
        stack[stacktop*2+1] -= i;
        stack[stacktop*2+2] = base;
        stack[stacktop*2+3] = j;
        stacktop += 2;
    }
}

int main(void)
{
    int arr[8192];
    size_t arrsize, i;
    scanf("%d", &arrsize);
    for(i = 0; i != arrsize; i++) scanf("%d", arr+i);
    quicksort(arr, arrsize);
    for(i = 0; i != arrsize; i++) printf("%d\n", arr[i]);
    return 0;
}

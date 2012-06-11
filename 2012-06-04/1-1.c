#include<stdio.h>

#define SWAP(_type, _a, _b) do{ \
        _type _tmp = _a; \
        _a = _b; \
        _b = _tmp; \
    } while(0)

void sift(int *arr, size_t size, size_t pos)
{
    int val = arr[pos];
    for(; pos < size/2;){
        size_t next = pos*2+1;
        if(next+1 < size && arr[next] < arr[next+1]) next++;
        if(arr[next] < val) break;
        arr[pos] = arr[next];
        pos = next;
    }
    arr[pos] = val;
}

void heapsort(int *arr, size_t size)
{
    size_t i, j;
    for(i = size/2; i;) sift(arr, size, --i);
    for(i = size; i;){
        i--;
        SWAP(int, arr[0], arr[i]);
        sift(arr, i, 0);
    }
}

int main(void)
{
    int arr[8192];
    size_t arrsize, i;
    scanf("%d", &arrsize);
    for(i = 0; i != arrsize; i++) scanf("%d", arr+i);
    heapsort(arr, arrsize);
    for(i = 0; i != arrsize; i++) printf("%d\n", arr[i]);
    return 0;
}

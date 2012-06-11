#include<stdio.h>

#define SWAP(_type, _a, _b) do{ \
        _type _tmp = _a; \
        _a = _b; \
        _b = _tmp; \
    } while(0)

void sift(int *arr, size_t size, size_t pos, int *c1, int *c2)
{
    int val = arr[pos];
    for(; pos < size/2;){
        size_t next = pos*2+1;
        if(next+1 < size && ((*c1)++, arr[next] < arr[next+1])) next++;
        if((*c1)++, arr[next] < val) break;
        (*c2)++;
        arr[pos] = arr[next];
        pos = next;
    }
    arr[pos] = val;
}

void heapsort(int *arr, size_t size, int *c1, int *c2)
{
    size_t i, j;
    for(i = size/2; i;) sift(arr, size, --i, c1, c2);
    for(i = size; i;){
        i--;
        (*c2) += 3;
        SWAP(int, arr[0], arr[i]);
        sift(arr, i, 0, c1, c2);
    }
}

int main(void)
{
    int arr[8192], c1 = 0, c2 = 0;
    size_t arrsize, i;
    scanf("%d", &arrsize);
    for(i = 0; i != arrsize; i++) scanf("%d", arr+i);
    heapsort(arr, arrsize, &c1, &c2);
    printf("%d %d\n", c1, c2);
    return 0;
}

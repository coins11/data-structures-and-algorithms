#include<alloca.h>
#include<stdio.h>
#include<string.h>

size_t find_substring(const char *s1, const char *s2)
{
    size_t *next, i, j, c = 0;
    next = alloca(sizeof(size_t)*strlen(s2));
    if(s2[0]){
        for(i = 0; c++, s2[i]; i++) next[i] = 0;
        for(i = 1; c++, s2[i]; i++){
            for(j = 0; c++, s2[j] == s2[i+j]; j++);
            if(next[i+j] < j+1) next[i+j] = j+1;
        }
    }
    for(i = 0, j = 0;;){
        if((c++, !s2[j]) || (c++, !s1[i+j])) return c;
        if(c++, s1[i+j] != s2[j]){
            i = i+j+1-next[j];
            j = next[j] ? next[j]-1 : next[j];
        }
        else j++;
    }
}

int main(void)
{
    char s1[131072], s2[131072];
    scanf("%s %s", &s1, &s2);
    printf("%d\n", find_substring(s1, s2));
    return 0;
}

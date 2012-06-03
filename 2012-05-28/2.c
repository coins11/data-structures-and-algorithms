#include<alloca.h>
#include<stdio.h>
#include<string.h>

const char *find_substring(const char *s1, const char *s2)
{
    size_t *next, i, j;
    next = alloca(sizeof(size_t)*strlen(s2));
    if(s2[0]){
        for(i = 0; s2[i]; i++) next[i] = 0;
        for(i = 1; s2[i]; i++){
            for(j = 0; s2[j] == s2[i+j]; j++);
            if(next[i+j] < j+1) next[i+j] = j+1;
        }
    }
    for(i = 0, j = 0;;){
        if(!s2[j]) return s1+i;
        if(!s1[i+j]) return NULL;
        if(s1[i+j] != s2[j]){
            i = i+j+1-next[j];
            j = next[j] ? next[j]-1 : next[j];
        }
        else j++;
    }
}

int fss_test(const char *s1, const char *s2)
{
    const char *s3 = find_substring(s1, s2);
    printf("s1:\n%s\ns2:\n%s\n", s1, s2);
    if(s3) printf("s3:\n%s\n", s3);
    else printf("substring not found\n");
    return 0;
}

int main(void)
{
    char s1[131072], s2[131072];
    scanf("%s %s", &s1, &s2);
#ifdef TESTMODE
    puts(find_substring(s1, s2) == strstr(s1, s2) ? "true" : "false");
#else
    fss_test(s1, s2);
#endif
    return 0;
}

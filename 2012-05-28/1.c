#include<stdio.h>
#include<string.h>

const char *find_substring(const char *s1, const char *s2)
{
    size_t head, i;
    for(head = 0;; head++){
        for(i = 0;; i++){
            if(!s2[i]) return s1+head;
            if(!s1[head+i]) return NULL;
            if(s1[head+i] != s2[i]) break;
        }
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

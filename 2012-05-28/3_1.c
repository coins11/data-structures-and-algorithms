#include<stdio.h>
#include<string.h>

size_t find_substring(const char *s1, const char *s2)
{
    size_t head, i, c = 0;
    for(head = 0;; head++){
        for(i = 0;; i++){
            if((c++, !s2[i]) || (c++, !s1[head+i])) return c;
            if(c++, s1[head+i] != s2[i]) break;
        }
    }
}

int main(void)
{
    char s1[131072], s2[131072];
    size_t c;
    scanf("%s %s", &s1, &s2);
    c = find_substring(s1, s2);
    printf("%d\n", c);
    return 0;
}

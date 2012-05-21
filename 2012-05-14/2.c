#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define CMPDISTANCE(x, y) ((y) < 0 || ((x) >= 0 && (x) < (y)))
#define ADDDISTANCE(x, y) ((x) < 0 || (y) < 0 ? -1 : (x) + (y))

typedef struct {
    size_t x, y;
    int *m;
} matrix_t;

int expect(char ch, FILE *input)
{
    int ch_ = getc(input);
    if(ferror(input)) return -1;
    if(ch == ch_) return 1;
    ungetc(ch_, input);
    return 0;
}

int expect_pred(int (*f)(int), FILE *input)
{
    int ch = getc(input);
    if(ferror(input)) return EOF;
    if(f(ch)) return ch;
    ungetc(ch, input);
    return EOF;
}

int drop_spaces(FILE *input)
{
    while(1){
        int r = expect_pred(isspace, input);
        if(ferror(input)) return -1;
        if(r == EOF) return 0;
    }
}

int read_uinteger(int *dest, FILE *input)
{
    int result = 0;
    if(drop_spaces(input) < 0) return -1;
    while(1){
        int ch = expect_pred(isdigit, input);
        if(ferror(input)) return -1;
        if(ch != EOF) result = result*10+ch-'0';
        else{
            *dest = result;
            return 0;
        }
    }  
}

int read_integer(int *dest, FILE *input)
{
    int sign, result = 0;
    if(drop_spaces(input) < 0) return -1;
    if((sign = expect('-', input)) < 0) return -1;
    while(1){
        int ch = expect_pred(isdigit, input);
        if(ferror(input)) return -1;
        if(ch != EOF) result = result*10+ch-'0';
        else{
            *dest = sign ? -result : result;
            return 0;
        }
    }
}

int read_matrix(matrix_t *dest, FILE *input)
{
    int size, *m;
    size_t i = 0;
    if(read_uinteger(&size, input) < 0) return -1;
    dest->x = size, dest->y = size;
    dest->m = (m = malloc(sizeof(int)*size*size));
    if(!m) return -1;
    for(; i != size*size; i++)
        if(read_integer(m+i, input) < 0){
            free(m);
            return -1;
        }
    return 0;
}

int floyd(matrix_t *graph, size_t start, int **dtable_, size_t **route_)
{
    int *dtable, distance;
    char *used;
    size_t size = MIN(graph->x, graph->y), *route, i, j, cur;
    if(size < start) return -1;
    dtable = malloc(sizeof(int)*size);
    route = malloc(sizeof(size_t)*size);
    used = malloc(sizeof(char)*size);
    if(!(dtable && route && used)){
        free(dtable);
        free(route);
        free(used);
        return -1;
    }
    for(i = 0; i != size; i++) dtable[i] = -1, route[i] = i, used[i] = 0;
    dtable[start] = 0;
    for(i = 0;; i++){
        distance = -1;
        for(j = 0; j != size; j++)
            if(!used[j] && CMPDISTANCE(dtable[j], distance))
                cur = j, distance = dtable[j];
        if(distance < 0){
            free(used);
            *dtable_ = dtable;
            *route_ = route;
            return 0;
        }
        used[cur] = 1;
        for(j = 0; j != size; j++){
            int nd = ADDDISTANCE(distance, graph->m[cur*(graph->x)+j]);
            if(!used[j] && CMPDISTANCE(nd, dtable[j]))
                route[j] = cur, dtable[j] = nd;
        }
    }
}

int trace_route(size_t *route, size_t goal)
{
    if(route[goal] != goal) trace_route(route, route[goal]);
    printf("%s%d", route[goal] != goal ? " " : "", goal);
    return 0;
}

int main(void)
{
    matrix_t graph;
    int *dtable;
    size_t *route, i;
    if(read_matrix(&graph, stdin) < 0) return -1;
    if(floyd(&graph, 0, &dtable, &route) < 0){
        free(graph.m);
        return -1;
    }
    for(i = 0; i != graph.x; i++){
        printf("node %d", i);
        if(dtable[i] < 0) printf(" is unreachable.\n");
        else{
            printf("\n\tdistance: %d\n\troute   : ", dtable[i]);
            trace_route(route, i);
            printf("\n");
        }
    }
    free(graph.m);
    free(dtable);
    free(route);
    return 0;
}

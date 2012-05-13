#include<assert.h>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>

#include"stack.h"

typedef enum fixity {
    LEFTASSOC,
    RIGHTASSOC,
    NONASSOC
} fixity_t;

typedef struct operator {
    char opsymbol;
    unsigned int level;
    fixity_t fixity;
} operator_t;

typedef struct expr {
    enum { VAREXPR, OPEXPR } exprtype;
    union {
        char variable;
        struct {
            const operator_t *op;
            struct expr *left, *right;
        };
    };
} expr_t;

expr_t *new_varexpr(char variable)
{
    expr_t *expr = malloc(sizeof(expr_t));
    if(expr){
        expr->exprtype = VAREXPR;
        expr->variable = variable;
    }
    return expr;
}

expr_t *new_opexpr
    (const operator_t *syntax, char op, expr_t *left, expr_t *right)
{
    size_t i = 0;
    assert(op != '\0');
    assert(left);
    assert(right);
    for(; syntax[i].opsymbol && syntax[i].opsymbol != op; i++);
    if(syntax[i].opsymbol != '\0'){
        expr_t *expr = malloc(sizeof(expr_t));
        if(!expr) return NULL;
        expr->exprtype = OPEXPR;
        expr->op = &syntax[i];
        expr->left = left;
        expr->right = right;
        return expr;
    }
    return NULL;
}

void release_expr(expr_t *expr)
{
    if(expr && expr->exprtype == OPEXPR){
        release_expr(expr->left);
        release_expr(expr->right);
    }
    free(expr);
}

void release_expr_p(expr_t **expr)
{
    release_expr(*expr);
}

int compare_level(unsigned int ctxlevel, fixity_t ctxfixity,
    unsigned int level, fixity_t fixity)
{
    if(ctxlevel < level) return 1;
    if(ctxlevel == level && ctxfixity == fixity &&
        (ctxfixity == LEFTASSOC || ctxfixity == RIGHTASSOC))
            return 1;
    return 0;
}

int ppr_infix_expr
    (unsigned int ctxlevel, fixity_t ctxfixity, expr_t *expr, FILE *output)
{
    assert(expr);
    switch(expr->exprtype){
    case VAREXPR:
        fputc(expr->variable, output);
        return 0;
    case OPEXPR:
        assert(expr->op);
        assert(expr->left);
        assert(expr->right);
        if(compare_level(ctxlevel, ctxfixity,
            expr->op->level, expr->op->fixity)){
            ppr_infix_expr(expr->op->level,
                expr->op->fixity == LEFTASSOC ? LEFTASSOC : NONASSOC,
                expr->left, output);
            fputc(' ', output);
            fputc(expr->op->opsymbol, output);
            fputc(' ', output);
            ppr_infix_expr(expr->op->level,
                expr->op->fixity == RIGHTASSOC ? RIGHTASSOC : NONASSOC,
                expr->right, output);
        }
        else{
            fputc('(', output);
            ppr_infix_expr(0, NONASSOC, expr, output);
            fputc(')', output);
        }
        return 0;
    default:
        return -1;
    }
}

int ppr_prefix_expr(expr_t *expr, FILE *output)
{
    assert(expr);
    switch(expr->exprtype){
    case VAREXPR:
        fputc(expr->variable, output);
        fputc(' ', output);
        return 0;
    case OPEXPR:
        assert(expr->op);
        assert(expr->left);
        assert(expr->right);
        fputc(expr->op->opsymbol, output);
        fputc(' ', output);
        ppr_prefix_expr(expr->left, output);
        ppr_prefix_expr(expr->right, output);
        return 0;
    default:
        return -1;
    }
}

stack_t *parse_postfix(const operator_t *syntax, FILE *input)
{
    stack_t *stack;
    stack = stack_initialize(sizeof(expr_t *),
        (void (*)(void *))release_expr_p);
    while(1){
        char ch;
        expr_t *expr;
        ch = getc(input);
        if(ferror(input)) goto ERR;
        if(ch == EOF) return stack;
        if(isspace(ch)) continue;
        if(isalpha(ch)){
            if(!(expr = new_varexpr(ch))) goto ERR;
        }
        else{
            expr_t *children[2];
            if(stack_refer_many_elements_from_top(stack, 0, 1, children) !=
                STACK_SUCCESS) goto ERR;
            if(!(expr = new_opexpr(syntax, ch, children[1], children[0])))
                goto ERR;
            if(stack_pop_many_elements(stack, 2, NULL) != STACK_SUCCESS)
                goto ERR;
        }
        if(stack_push(stack, &expr) != STACK_SUCCESS) goto ERR;
    }
ERR:
    stack_release(stack);
    return NULL;
}

const operator_t syntax[] = {
    {'*', 2, LEFTASSOC},
    {'/', 2, LEFTASSOC},
    {'+', 1, LEFTASSOC},
    {'-', 1, LEFTASSOC},
    {'\0', 0, NONASSOC}
};

int main(void)
{
    stack_t *result = parse_postfix(syntax, stdin);
    if(!result) return -1;
    while(!stack_empty(result)){
        expr_t *expr;
        if(stack_pop(result, &expr) != STACK_SUCCESS) goto ERR;
        ppr_infix_expr(0, NONASSOC, expr, stdout);
        fputc('\n', stdout);
        ppr_prefix_expr(expr, stdout);
        fputc('\n', stdout);
        release_expr(expr);
    }
    stack_release(result);
    return 0;
ERR:
    stack_release(result);
    return -1;
}

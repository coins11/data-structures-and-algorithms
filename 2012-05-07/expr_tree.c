#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#define MAX_NODES 32

typedef struct node_ {
   struct node_ *l, *r;
   char ch;
} node;

node* new_node(const char ch, node *l, node *r) {
   node *n = malloc(sizeof(node));
   if(n == NULL) return NULL;
   n->ch = ch;
   n->l  = l;
   n->r  = r;
   return n;
}

bool is_operator(const char ch) {
   return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

bool compare_operator(const char a, const char b) {
   if(!is_operator(a) || !is_operator(b)) return false;
   if((a == '*' || a == '/') && (b == '*' || b == '/')) return false;
   if((a == '+' || a == '-') && (b == '+' || b == '-')) return false;
   if((a == '*' || a == '/') && (b == '+' || b == '-')) return true;
   return false;
}

node* parse2node(const char *str) {
   node *stack[MAX_NODES] = {NULL};
   unsigned short idx_top = 0;
   for(const char *p = str; *p != '\0'; ++p) {
      if(is_operator(*p)) {
         // case1: character is operator
         if(idx_top - 2 < 0) {
            fprintf(stderr, "SYNTAX ERROR: expected alphabet");
            return NULL;
         }
         node *op_node = new_node(*p, stack[idx_top-2], stack[idx_top-1]);
         idx_top -= 2;
         stack[idx_top++] = op_node;
         continue;
      }
      if(isalpha(*p)) {
         // case2: character is alphabet
         node *alpha_node = new_node(*p, NULL, NULL);
         stack[idx_top++] = alpha_node;
         continue;
      }
      // ignore other characters
   }
   // check syntax error
   if(idx_top != 1) {
      fprintf(stderr, "SYNTAX ERROR: invalid format");
      return NULL;
   }
   return stack[0];
}

void trace_tree_(const node *n) {
   if(n == NULL) return;
   if(is_operator(n->ch)) {
      // case1: operator node
      if(compare_operator(n->ch, n->l->ch)) {
         putchar('(');
         trace_tree_(n->l);
         putchar(')');
      } else trace_tree_(n->l);
      printf(" %c ", n->ch);
      if(compare_operator(n->ch, n->r->ch)) {
         putchar('(');
         trace_tree_(n->r);
         putchar(')');
      } else trace_tree_(n->r);
   } else {
      // case2: alphabet node
      putchar(n->ch);
   }
}

void trace_tree(const node *n) {
   trace_tree_(n);
   putchar('\n');
}

void delete_tree(node *n) {
   if(n == NULL) return;
   delete_tree(n->l);
   delete_tree(n->r);
   free(n);
}

int main(int argc, char *argv[]) {
   while(1) {
      printf("expr: ");
      char buffer[128];
      gets(buffer);
      node *top = parse2node(buffer);
      trace_tree(top);
      delete_tree(top);
   }
   return 0;
}


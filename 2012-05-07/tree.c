#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_STACK_SIZE 100
#define MAX_EXPR_LENGTH 256

typedef struct node_t {
  struct node_t *left, *right;
  char record;
} node;

/* stack functions */
void push(node *n);
node* pop();
void print_stack();
/* node functions */
node* create_node();
void remove_node();
/* tree functions */
node* create_tree(char *expr);
void traverse_preorder(node *n);
void traverse_inorder(node *n);
void traverse_postorder(node *n);

node *stack[MAX_STACK_SIZE];
int stack_pos = 0;

int main(int argc, char **argv)
{
  node *root;
  char input[MAX_EXPR_LENGTH];
  printf("input expression> ");
  scanf("%s", input);
  root = create_tree(input);
  printf("preorder: ");
  traverse_preorder(root);
  printf("\n");
  printf("inorder: ");
  traverse_inorder(root);
  printf("\n");
  printf("postorder: ");
  traverse_postorder(root);
  printf("\n");
}

void push(node *n)
{
  if (stack_pos > MAX_STACK_SIZE)
  {
    printf("error: stack overflow\n");
    exit(EXIT_FAILURE);
  }
  stack[stack_pos++] = n;
}

node* pop()
{
  if (stack_pos < 0)
  {
    printf("error: stack underflow\n");
    exit(EXIT_FAILURE);
  }
  return stack[--stack_pos];
}

void print_stack()
{
  int i;
  for(i = 0; i < MAX_STACK_SIZE && stack[i] != NULL; ++i)
    printf("%c ", stack[i]->record);
  printf("\n");
}

node* create_node()
{
  node* n = malloc(sizeof(node));
  if (n == NULL)
  {
    printf("can't allocate memory.\n");
    exit(EXIT_FAILURE);
  }
  return n;
}

void remove_node(node *n)
{
  free(n);
}

node* create_tree(char *expr)
{
  int i;
  node *n;
  for (i = 0; expr[i] != '\0'; i++)
  {
    if (isalpha(expr[i]))
    {
      n = create_node();
      n->record = expr[i];
      push(n);
    }
    else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') 
    {
      n = create_node();
      n->record = expr[i];
      n->right = pop();
      n->left = pop();
      push(n);
    }
    else
    {
      printf("invalid character.\n");
      exit(EXIT_FAILURE);
    }
  }
  return pop();
}

void traverse_preorder(node *n)
{
  if (n == NULL)
    return;
  printf("%c ", n->record);
  traverse_preorder(n->left);
  traverse_preorder(n->right);
}

void traverse_inorder(node *n)
{
  if (n == NULL)
    return;
  if (n->left != NULL)
  {
    printf("( ");
    traverse_inorder(n->left);
  }
  printf("%c ", n->record);
  if (n->right != NULL)
  {
    traverse_inorder(n->right);
    printf(") ");
  }
}

void traverse_postorder(node *n)
{
  if (n == NULL)
    return;
  traverse_postorder(n->left);
  traverse_postorder(n->right);
  printf("%c ", n->record);
}

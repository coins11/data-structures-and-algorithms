#include <stdio.h>
#include <stdlib.h>

typedef struct _cell {
  int num;
  struct _cell *next;
} cell;

cell *head = NULL, *tail = NULL;

/* list functions */
void append(int value);
cell* search(int value);
void insert(cell* item, int value);
void delete(cell* item);
void printlist();
cell* alloc_cell(int value);
/* queue functions */
void enqueue(int item);
int dequeue();

int main(int argc, char **argv)
{
  cell *p = NULL;

  enqueue(2);
  enqueue(5);
  enqueue(1);

  printlist();
  printf("\n");

  printf("dequeue: %d\n", dequeue());
  printlist();
  printf("\n");

  enqueue(3);
  printlist();

  printf("dequeue: %d\n", dequeue());
  printf("dequeue: %d\n", dequeue());
  printf("dequeue: %d\n", dequeue());
  /* underflow will be occured here
  printf("dequeue: %d\n", dequeue());
  */  
}

void append(int value)
{
  cell *p = alloc_cell(value);
  /* if there are no items in the list.  */
  if (head == NULL && tail == NULL)
  {
    head = p;
    tail = p;
  }
  else
  {
    cell *q = tail;
    q->next = p;
    tail = p;
  }
}

cell* search(int value)
{
  cell *p;
  for(p = head; p != NULL; p = p->next)
  {
    if (p->num == value)
      return p;
  }
  return NULL;
}

void insert(cell* item, int value)
{
  cell *p;
  if (item == NULL)
  {
    printf("insert: item must not be NULL.\n");
    exit(EXIT_FAILURE);
  }

  p = alloc_cell(value);
  if (tail == item)
  {
    item->next = p;
    tail = p;
  }
  else
  {
    p->next = item->next;
    item->next = p;
  }
}

void delete(cell* item)
{
  cell *p;
  if (item == head)
  {
    if (item == tail)
    {
      head = NULL;
      tail = NULL;
    }
    else
    {
      head = item->next;
    }
  }
  else
  {
    /* find a cell before the deleting item */
    for (p = head; p != NULL; p = p->next)
    {
      if (p->next == item)
      {
        if (item == tail)
        {
          p->next = NULL;
          tail = p;
        }
        else
        {
          p->next = item->next;
        }
      }
    }
  }
  free(item);
}

void printlist()
{
  cell *p;
  for (p = head; p != NULL; p = p->next)
    printf("%d ", p->num);
  printf("\n");
}

cell* alloc_cell(int value)
{
  cell *p = (cell *)malloc(sizeof(cell));
  if (p == NULL)
  {
    printf("can't allocate memory.\n");
    exit(EXIT_FAILURE);
  }
  p->num = value;
  p->next = NULL;
  return p;
}

void enqueue(int value)
{
  append(value);
}

int dequeue()
{
  if (head == NULL && tail == NULL)
  {
    printf("queue underflow\n");
    exit(EXIT_FAILURE);
  }
  int r = head->num;
  delete(head);
  return r;
}

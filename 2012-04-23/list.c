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

int main(int argc, char **argv)
{
  cell *p = NULL;

  append(2);
  append(5);
  append(1);

  printlist();
  printf("\n");

  if ((p = search(5)) == NULL)
  {
    printf("item not found: 5\n");
    exit(EXIT_FAILURE);
  }
  insert(p, 3);
  printlist();
  printf("\n");

  if ((p = search(2)) == NULL)
  {
    printf("item not found: 2\n");
    exit(EXIT_FAILURE);
  }
  delete(p);
  printlist();
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

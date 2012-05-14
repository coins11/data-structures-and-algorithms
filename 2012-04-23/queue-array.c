#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE 5

void printqueue();
/* queue functions */
void enqueue(int item);
int dequeue();

int queue[MAX_QUEUE];
int front = 0, rear = 0;

int main(int argc, char **argv)
{
  enqueue(2);
  enqueue(5);
  enqueue(1);

  printqueue();
  printf("\n");

  printf("dequeue: %d\n", dequeue());
  printqueue();
  printf("\n");

  enqueue(3);
  printqueue();

  printf("dequeue: %d\n", dequeue());
  printf("dequeue: %d\n", dequeue());
  printf("dequeue: %d\n", dequeue());
  /* remove the comment below to occur underflow */
  /*
  printf("dequeue: %d\n", dequeue());
  */

  /* remove the comment below to occur overflow */
  /*
  enqueue(1);
  enqueue(2);
  enqueue(3);
  enqueue(4);
  enqueue(5);
  */
  /* overflow will be occured here */
  /*
  enqueue(6);
  */
}

void printqueue()
{
  int i;
  for (i = front; i != rear ; ++i)
    printf("%d ", queue[i % MAX_QUEUE]);
  printf("\n");
}

void enqueue(int value)
{
  if (front - rear == 1 || front - rear + MAX_QUEUE == 1)
  {
    printf("queue overflow\n");
    exit(EXIT_FAILURE);
  }
  queue[rear++] = value;
  if (rear == MAX_QUEUE)
    rear = 0;
}

int dequeue()
{
  if (front == rear)
  {
    printf("queue underflow\n");
    exit(EXIT_FAILURE);
  }
  int tmp = queue[front++];
  if (front == MAX_QUEUE)
    front = 0;
  return tmp;
}

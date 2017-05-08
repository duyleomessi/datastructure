#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main(int argc, char *argv[])  {
  queue *q = createQueue();
  elementtype e;
  e.val = 2;
  enqueue(&q, e);
  e.val = 3;
  enqueue(&q, e);

  node *tmp = dequeue(&q);
  printf("%d ", tmp->element.val);
  node * tmp2 = dequeue(&q);
  printf("%d ", tmp2->element.val);
 
  return 0;
}

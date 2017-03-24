#include <stdio.h>
#include <stdlib.h>
#include "linklist.h"

int main(int argc, char *argv[]) {
  node *arr = NULL;
  elementtype e;
  e.val = 0;
  insertAtTheBegin(&arr, e);
  e.val = 1;
  insertAfterCurrent(&arr, e);
  e.val = 2;
  insertAfterCurrent(&arr, e);
  e.val = 3;
  insertAtPosition(&arr, e, 2);
  printList(&arr);
  deleteAtPosition(&arr, 3);
  printList(&arr);
  e.val = 4;
  insertAtPosition(&arr, e, 2);
  printList(&arr);
  deleteAtTheMiddle(&arr);
  printList(&arr);
}

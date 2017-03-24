#include <stdio.h>
#include <stdlib.h>
#include "linklist.h"

int main(int argc, char *argv[]) {
  node *arr = NULL;
  node *arr1 = NULL;
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

  insertAtTheEnd(&arr1, e);
  e.val = 5;
  insertAfterCurrent(&arr1, e);
  e.val = 6;
  insertBeforeCurrent(&arr1, e);
  e.val = 7;
  insertAtTheBegin(&arr1, e);
  printList(&arr1);
  deleteAtTheMiddle(&arr1);
  printList(&arr1);

  node *reverseList = list_reverse(&arr1);
  printList(&reverseList);
}

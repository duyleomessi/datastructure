#include <stdio.h>
#include <stdlib.h>
#include "linklist.h"

int main (int argc, char *argv[]) {
  node *arr = NULL;
  node *arr1 = NULL;
  elementtype e;
  printf("main root is %p\n", arr);
  e.val = 2;
  
  insertAtTheBegin(&arr, e); 
  printf("root is %p\n", arr);
  e.val = 3;
  insertAtTheBegin(&arr, e);
  e.val = 4;
  insertAtTheEnd(&arr, e);
  insertAtTheBegin(&arr, e);
  e.val = 7;
  insertBeforeCurrent(&arr, e);
  e.val = 8;
  insertAfterCurrent(&arr, e);
  removeFirstItem(&arr);
  removeFirstItem(&arr);
  removeLastItem(&arr);
  removeLastItem(&arr);
  printList(arr);
}

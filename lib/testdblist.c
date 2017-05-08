#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dblinklist.h"


int main(int argc, char *argv[]) {
  node *phone = NULL;
  elementtype e;

  char name[20] = "Samsung 1";
  strcpy(e.name, name);
  e.memory = 16;
  e.screen = 5.5;
  e.price = 10000000;
  insertAtTheBegin(&phone, e);
  
  char name1[20] = "Samsung 2";
  strcpy(e.name, name1);
  e.memory = 16;
  e.screen = 5.5;
  e.price = 10000000;
  insertAtTheBegin(&phone, e);
  printList(&phone);

  char name2[20] = "Samsung 3";
  strcpy(e.name, name2);
  e.memory = 16;
  e.screen = 5.5;
  e.price = 10000000;
  insertAtTheEnd(&phone, e);
  printList(&phone);

  char name3[20] = "Samsung 4";
  strcpy(e.name, name3);
  e.memory = 16;
  e.screen = 5.5;
  e.price = 10000000;
  insertBeforeCurrent(&phone, e);
  printList(&phone);

  char name4[20] = "Samsung 5";
  strcpy(e.name, name4);
  e.memory = 16;
  e.screen = 5.5;
  e.price = 10000000;
  insertBeforeCurrent(&phone, e);
  printList(&phone);

  char name5[20] = "Samsung 6";
  strcpy(e.name, name5);
  e.memory = 16;
  e.screen = 5.5;
  e.price = 10000000;
  insertAfterCurrent(&phone, e);
  printList(&phone);

  char name6[20] = "Samsung 7";
  strcpy(e.name, name6);
  e.memory = 16;
  e.screen = 5.5;
  e.price = 10000000;
  insertAfterCurrent(&phone, e);
  printList(&phone);

  char name7[20] = "Samsung 8";
  strcpy(e.name, name7);
  e.memory = 16;
  e.screen = 5.5;
  e.price = 10000000;
  insertBeforeCurrent(&phone, e);
  printList(&phone);

  /* removeFirstItem(&phone); */
  /* printList(&phone); */

  /* removeFirstItem(&phone); */
  /* printList(&phone); */

  /* removeLastItem(&phone); */
  /* printList(&phone); */
  deleteList(&phone);
  printf("Free\n");
  printList(&phone);
  return 0;
}

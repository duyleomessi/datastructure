#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "duy.h"
#include "linklist.h"

char getMenu();
void readDataFromText(node **phone, FILE *fin, FILE *fout, int totalMember);
void readDataFromDat(node **phone, FILE *fin);
void searchByModel(node **phone);
void searchByPrice(node **phone);
void exportToDat(node **phone, FILE *fout);
int sizefile(FILE *f);
void addNewPhone(node **phone, elementtype e);
void addPhonePosition(node **phone, elementtype e, int position);


int main(int argc, char* argv[]) {
  FILE *fp1, *fp2;
  char filename1[] = "phonedb.txt";
  char filename2[] = "phonedb.dat";
  
  fp1 = myfopen(filename1, "r");
  fp2 = myfopen(filename2, "r+b");

  node *phone = NULL;
  char choice;
  node *revert;

  elementtype newPhone;
  int pos;

  //int lengOfFile = countLine(fp1);
  //rewind(fp1);
  //rewind(fp2);
  
  do {
    choice = getMenu();
    switch(choice) {
    case '1':
      //readDataFromText(&phone, fp1, fp2, lengOfFile);
      //deleteList(&phone);
      //node *phone = NULL;
      readDataFromDat(&phone, fp2);
      printf("Import complete\n\n");
      break;
    case '2':
      printList(&phone);
      break;
    case '3':
      printf("Enter the name of model: ");
      scanf("%[^\n]", newPhone.name);
      printf("Enter the amount of memory: ");
      scanf("%d", &newPhone.memory);
      printf("Enter the wide of screen: ");
      scanf("%f", &newPhone.screen);
      printf("Enter the price: ");
      scanf("%d", &newPhone.price);
      myfflush();
      
      addNewPhone(&phone, newPhone);
      break;
    case '4':
      printf("Enter the position you want to add: ");
      scanf("%d", &pos);
      myfflush();
      printf("Enter the name of model: ");
      scanf("%[^\n]", newPhone.name);
      printf("Enter the amount of memory: ");
      scanf("%d", &newPhone.memory);
      myfflush();
      printf("Enter the wide of screen: ");
      scanf("%f", &newPhone.screen);
      printf("Enter the price: ");
      scanf("%d", &newPhone.price);
      myfflush();

      addPhonePosition(&phone, newPhone, pos);
      break;
    case '5':
      deleteAtTheMiddle(&phone);
      break;
    case '6':
      /* fclose(fp2); */
      /* fp2 = myfopen(filename2, "w+b"); */
      /* exportToDat(&phone, fp2); */

      printf("Enter the position you wanna delete: ");
      scanf("%d", &pos);
      myfflush();
      deleteAtPosition(&phone, pos);
      break;

    case '7':
      removeFirstItem(&phone);
      break;
    case '8':
      searchByModel(&phone);
      break;
    case '9':
      revert = list_reverse(&phone);
      printList(&revert);
      break;
    case '0':
      return 1;
    default:
      printf("Invalid input. Enter again!!!\n");
      break;
    }
  }while(choice != '0');
  
  
  
  fclose(fp1);
  fclose(fp2);
  return 0;
}

char getMenu() {
  char choice;
  printf("*****************\n");
  printf("1. Import from dat\n");
  printf("2. Display list\n");
  printf("3. Add new phone\n");
  printf("4. Insert at position \n");
  printf("5. Delete at position\n");
  printf("6. Delete current\n");
  printf("7. Delete first\n");
  printf("8. Search and Update\n");
  printf("9. Revert list\n");
  printf("10. Devide and extract\n");
  printf("11.Save to file\n");
  printf("0. Quit\n");
  printf("*****************\n");
  
  printf("Your choice: ");
  scanf("%c", &choice);
  myfflush();
  return choice;
}


void readDataFromDat(node **phone, FILE *fin) {
  printf("start import from dat\n");
  int totalMember = sizefile(fin)/sizeof(elementtype);
  printf("totalMember: %d\n", totalMember);
  
  elementtype *e = (elementtype *) malloc(totalMember * sizeof(elementtype));
  //elementtype e[totalMember];
 
  int numRead = fread(e, sizeof(elementtype), totalMember, fin);
  printf("numRead is %d\n", numRead);
  int i;
  for(i = 0; i < numRead; i++) {
    // printf("%s %d %f %d\n", e[i].name, e[i].memory, e[i].screen, e[i].price);
    insertAfterCurrent(phone, e[i]);
  }
  
};

void searchByModel(node **phone) {
  char searching[50];
  node *p = *phone;
  elementtype newPhone;
  printf("Enter the model you wanna search: ");
  scanf("%[^\n]", searching);
  myfflush();
  int found = 0;
  int count = 1;

  while(p != NULL) {
    printf("%s \n", p->element.name);

    if (strcmp(p->element.name, searching) == 0) {
      found = 1;
      printf("Founded: %s %d %f %d\n", p->element.name, p->element.memory, p->element.screen, p->element.price);
      printf("Update\n");
      printf("Enter the model name: ");
      scanf("%[^\n]", newPhone.name);
      myfflush();
      printf("Enter the memory: ");
      scanf("%d", &newPhone.memory);
      myfflush();
      printf("Enter the screen: ");
      scanf("%f", &newPhone.screen);
      myfflush();
      printf("Enter the price: ");
      scanf("%d", &newPhone.price);
      myfflush();
      p->element = newPhone;
      break;
    }
    count++;
    p = p->next;
  }
  
  if (found == 0) {
    printf("Not Found\n");
  }
  
}

void searchByPrice(node **phone) {
  int searchPrice;
  printf("Enter the price: ");
  scanf("%d", &searchPrice);
  myfflush();
  node *p = *phone;
  int count = 0;
  
  while(p != NULL) {
    if (p->element.price < searchPrice) {
      printf("%-50s%-4d%-.2f%20d\n", p->element.name, p->element.memory, p->element.screen, p->element.price);
      count++;
    }
    p = p->next;
  };
  
  if (count == 0) {
    printf("Not found\n");
  }
};

void exportToDat(node **phone, FILE *fout) {
  node *p = *phone;
  while (p != NULL) {
    fwrite(phone, sizeof(phone), 1, fout);
    p = p->next;
  }
};
  
int sizefile(FILE *f){
  int prev = ftell(f);
  fseek(f,(long)0,SEEK_END);
  int size = ftell(f);
  fseek(f,prev,SEEK_SET);
  return size;
}

void addNewPhone(node **phone, elementtype e) {
  insertAtTheEnd(phone, e);
}

void addPhonePosition(node **phone, elementtype e, int position) {
  insertAtPosition(phone, e, position);
};

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "duy.h"
#include "linklist.h"

char getMenu();
void readDataFromText(node **phone, FILE *fin, FILE *fout, int totalMember);
void readDataFromDat(node **phone, FILE *fin, int totalMember);
void searchByModel(node **phone);
void searchByPrice(node **phone);
void exportToDat(node **phone, FILE *fout);

int main(int argc, char* argv[]) {
  FILE *fp1, *fp2;
  char filename1[] = "phonedb.txt";
  char filename2[] = "phonedb.dat";
  
  fp1 = myfopen(filename1, "r");
  fp2 = myfopen(filename2, "w+b");

  node *phone = NULL;
  // node *phone1 = NULL;
  char choice;

  int lengOfFile = countLine(fp1);
  rewind(fp1);
  do {
    choice = getMenu();
    switch(choice) {
    case '1':
      readDataFromText(&phone, fp1, fp2, lengOfFile);
      printf("Import complete\n\n");
      break;
    case '2':
      rewind(fp2);
      phone = NULL;
      readDataFromDat(&phone, fp2, lengOfFile);
      printf("Import complete\n\n");
      break;
    case '3':
      printList(&phone);
      break;
    case '4':
      searchByModel(&phone);
      break;
    case '5':
      searchByPrice(&phone);
      break;
    case '6':
      fclose(fp2);
      fp2 = myfopen(filename2, "w+b");
      exportToDat(&phone, fp2);
      break;
    case '7':
      return 1;
    default:
      printf("Invalid input. Enter again!!!\n");
      break;
    }
  }while(choice != '7');
  
  
  
  fclose(fp1);
  fclose(fp2);
  return 0;
}

char getMenu() {
  char choice;
  printf("*****************\n");
  printf("1. Import from text\n");
  printf("2. Import from dat\n");
  printf("3. Display list\n");
  printf("4. Search by Model\n");
  printf("5. Search price\n");
  printf("6. Export to Dat\n");
  printf("7. Quit\n");
  printf("*****************\n");

  printf("Your choice: ");
  scanf("%c", &choice);
  myfflush();
  return choice;
}


void readDataFromText(node **phone, FILE *fin, FILE *fout,  int totalMember) {
  elementtype e[totalMember];
  
  int i = 0;
  for(i = 0; i < totalMember; i++) {
    fscanf(fin, "%[^|]|%d|%f|%d", e[i].name, &e[i].memory, &e[i].screen, &e[i].price);
 
    insertAfterCurrent(phone, e[i]);
  };

  fwrite(e, sizeof(e), totalMember, fout);
};


void readDataFromDat(node **phone, FILE *fin, int totalMember) {
  elementtype e[totalMember];
  
  fread(e, sizeof(e), totalMember, fin);
  int i;
  for(i = 0; i < totalMember; i++) {
    //printf("value %s %d %f %d\n", e[i].name, e[i].memory, e[i].screen, e[i].price);
    insertAfterCurrent(phone, e[i]);
  }
  
};

void searchByModel(node **phone) {
  char searching[50];
   node *p = *phone;
  printf("Enter the model you wanna search: ");
  scanf("%[^\n]", searching);
  myfflush();
  int found = 0;

  while(p != NULL) {
    printf("%s \n", p->element.name);

    if (strcmp(p->element.name, searching) == 0) {
      found = 1;
      printf("%s %d %f %d\n", p->element.name, p->element.memory, p->element.screen, p->element.price);
      break;
    }
    
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
  

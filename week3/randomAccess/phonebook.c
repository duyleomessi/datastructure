#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "duy.h"

typedef struct {
  char name[20];
  char tel[11];
  char email[25];
} PhoneAddress;

int main(int argc, char *argv[]) {
  FILE *fptr;
  char filename[] = "phone.dat";
  int start, end;
  
  printf("Enter the position to start: ");
  scanf("%d", &start);
  printf("Enter the position to end: ");
  scanf("%d", &end);
   myfflush();
  if ((fptr = fopen(filename, "r+b")) == NULL) {
    printf("Cannot open %s\n", filename);
    return 1;
  }

  rewind(fptr);

  printf("Read file from %dth to %dth \n", start, end);
  
  PhoneAddress *phoneAddress = (PhoneAddress*) malloc( (end- start + 1) * sizeof(PhoneAddress));

  if (phoneAddress == NULL) {
    printf("Memory allocated faild!\n");
    return 1;
  }

  if (fseek(fptr, (start - 1) * sizeof(PhoneAddress), SEEK_SET) != 0) {
    printf("fseek fail\n");
    return 1;
  };
 
  fread(phoneAddress, sizeof(PhoneAddress), (end- start + 1), fptr);

  int i;
  for (i = 0; i  < end - start + 1; i++) {
    printf("%s %s %s\n", phoneAddress[i].name, phoneAddress[i].tel, phoneAddress[i].email);
  }
  char tmp[30];
  
  for (i = 0; i < end - start +1; i++) {
    printf("Enter the name you wanna replace: ");
    scanf("%[^\n]", tmp);
    myfflush();
    strcpy(phoneAddress[i].name, tmp);
    printf("Enter the telephone you wanna replace: ");
    scanf("%[^\n]", tmp);
    myfflush();
    strcpy(phoneAddress[i].tel, tmp);
    printf("Enter the telephone you wanna replace: ");
    scanf("%[^\n]", tmp);
    myfflush();
    strcpy(phoneAddress[i].email, tmp);
  }

  fseek(fptr, (start - 1) * sizeof(PhoneAddress), SEEK_SET);
  fwrite(phoneAddress, sizeof(PhoneAddress), (end - start + 1), fptr);
  fclose(fptr);
  return 0;
}

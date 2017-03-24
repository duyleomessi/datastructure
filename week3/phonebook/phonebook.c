#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT 100

typedef struct {
  char name[20];
  char tel[11];
  char email[25];
} PhoneAddress;

void fflushed();
PhoneAddress *inputPhoneArray(int num);
void writeToBinary(FILE *fout, PhoneAddress *phoneAddress, int num );
void readFromBinary(FILE *fin, int num);

int main(int argc, char *argv[]) {
  PhoneAddress *phoneAddress;
  FILE *fptr;
  int num;
  char filename[] = "phone.dat";
  if ((fptr = fopen(filename, "w+b")) == NULL) {
    printf("Cannot open %s\n", filename);
    return 1;
  }
  do {
    printf("Enter the number of phone: ");
    scanf("%d", &num);
    fflushed();
    if (num >= MAX_ELEMENT || num <= 0) {
      printf("the number of phone must is less than %d and greater than 0\n", MAX_ELEMENT);
    }
  } while(num >= MAX_ELEMENT || num <= 0);
  
  phoneAddress = inputPhoneArray(num);
  if (phoneAddress == NULL) {
    printf("Memory allocated faild\n");
    return 1;
  }

  writeToBinary(fptr, phoneAddress, num);
  rewind(fptr);
  readFromBinary(fptr, num);
  free(phoneAddress);
  fclose(fptr);
  return 0;
}

PhoneAddress *inputPhoneArray(int num) {
  PhoneAddress *phoneAddress  = (PhoneAddress*)malloc(MAX_ELEMENT * sizeof(PhoneAddress));
  int i;
  for (i = 0; i < num; i++) {
    printf("Contact %d\n", i + 1);
    printf("Enter the name: ");
    scanf("%[^\n]", phoneAddress[i].name);
    fflushed();
    printf("Enter the telephone: ");
    scanf("%[^\n]", phoneAddress[i].tel);
    fflushed();
    printf("Enter the email: ");
    scanf("%[^\n]", phoneAddress[i].email);
    fflushed();
  }
  
  return phoneAddress;
}

void fflushed() {
  while(getc(stdin) == '\n') break;
}

void writeToBinary(FILE *fout, PhoneAddress *phoneAddress, int num ) {
  int n;
  n = fwrite(phoneAddress, sizeof(PhoneAddress), num, fout);
  if (n == num) {
    printf("write success\n");
  }
}

void readFromBinary(FILE *fin, int num) {
  int i;
  PhoneAddress *phoneAddressTmp = (PhoneAddress *)malloc(num * sizeof(PhoneAddress));
  if (phoneAddressTmp == NULL) {
    printf("Memory allocated faild\n");
    exit(1);
  }
  fread(phoneAddressTmp, sizeof(PhoneAddress), num, fin);

  for (i = 0; i < num; i++ ) {
    printf("%-30s%-30s%-30s\n", phoneAddressTmp[i].name, phoneAddressTmp[i].tel, phoneAddressTmp[i].email);
  }
  
  free(phoneAddressTmp);
}

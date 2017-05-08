#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 30
#define MAX_LEN 81

void countLength(FILE *fin, int *length);

int main(int argc, char *argv[]) {
  if (argc != 4) {
    printf("The number of argument is incorrect!!");
    return 0;
  }

  FILE *fptr1, *fptr2, *fptr3;
  char filename1[MAX_NAME], filename2[MAX_NAME], filename3[MAX_NAME];
   int length1,length2, length3;
  
  strcpy(filename1, argv[1]);
  strcpy(filename2, argv[2]);
  strcpy(filename3, argv[3]);

  if((fptr1 = fopen(filename1, "r")) == NULL) {
    printf("Cannot open file %s\n", filename1);
    return 0;
  }
  countLength(fptr1, &length1);
  
  if((fptr2 = fopen(filename2, "r")) == NULL) {
    printf("Cannot open file %s\n", filename2);
    return 0;
  }
  countLength(fptr2, &length2);

  if((fptr3 = fopen(filename1, "w")) == NULL) {
    printf("Cannot open file %s\n", filename3);
    return 0;
  }
  countLength(fptr3, &length3);

  fclose(fptr1);
  fclose(fptr2);
  fclose(fptr3);
  return 0;
}

void countLength(FILE *fin, int *length) {
  char c;
  while((c = fgetc(fin)) != EOF) {
    //printf("c is %c\n", c);
    if(c == '\n') (*length)++;
  }
  //printf("length: %d\n", *length);
}

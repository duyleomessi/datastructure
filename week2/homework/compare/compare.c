#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LEN 81
#define MAX_DIFF 100

void compare(FILE *fin1, FILE *fin2) ;

int main(int argc, char* argv[]) {

  if (argc != 3) {
    printf("The number of params is not correct!!");
    return 0;
  }

  FILE *fptr1, *fptr2;

  if ( (fptr1 = fopen(argv[1], "r")) == NULL) {
    printf("Cannot open %s\n", argv[1]);
    return 0;
  }

  if ((fptr2 = fopen(argv[2], "r")) == NULL) {
    printf("Cannot open %s\n", argv[2]);
    return 0;
  }

  compare(fptr1, fptr2);
  fclose(fptr1);
  fclose(fptr2);
  
  return 0;
}

void compare(FILE *fin1, FILE *fin2)  {
  char buff1[MAX_LEN];
  char buff2[MAX_LEN];

  int line = 0;
  int differLine[MAX_DIFF];
  int i;
  for (i = 0; i < MAX_DIFF; i++) {
    differLine[i] = -1;
  }
  int index = 0;
  
  while(fgets(buff1, MAX_LEN, fin1) != NULL && fgets(buff2, MAX_LEN, fin2) != NULL) {
    if (strcmp(buff1, buff2) != 0) {
      differLine[index] = line+1;
      index++;
    }
    line++;
  }
  
  while( (fgets(buff1, MAX_LEN, fin1) != NULL && fgets(buff2, MAX_LEN, fin2) == NULL)
	 || (fgets(buff1, MAX_LEN, fin1) == NULL && fgets(buff2, MAX_LEN, fin2) != NULL) ) {
    differLine[index] = line+1;
    index++;
    line++;
  }
  
  printf("The first different line is %d\n", differLine[0]);
  printf("Differrent line is");
  for (i = 0; i < MAX_DIFF; i++) {
    if (differLine[i] != -1) {
      printf(" %d ", differLine[i]);
    }
  }
  printf("\n");
}

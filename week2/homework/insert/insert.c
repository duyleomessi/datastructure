#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LEN 81

void insert(FILE *fin);

int main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("The number of argument is 2!!");
    return 0;
  }

  FILE *fptr;
  char filename[30];
  strcpy(filename, argv[1]);

  if ((fptr = fopen(filename, "r+")) == NULL) {
    printf("Cannot open %s\n", filename);
    return 0;
  }

  insert(fptr);
  
  return 0;
}

void insert(FILE *fin) {
  char buff[MAX_LEN];
  int i = 0;
  char tmp[MAX_LEN];
  
  while(fgets(buff, MAX_LEN, fin) != NULL) {
    tmp[i] = buff[0];
    i++;
  }
  tmp[i] = '\0';
  // printf("%s\n", tmp);
  fputs(tmp, fin);
}

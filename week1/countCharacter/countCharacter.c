#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 81

void countCharacter(FILE *fin);

int main(int argc, char *argv[]) {
  FILE *fptr;
  char filename[] = "data.txt";

  if ((fptr = fopen(filename, "r+")) == NULL) {
    printf("Cannot open %s\n", filename);
    return 0;
  }

  countCharacter(fptr);
  fclose(fptr);
   
  return 0;
}

void countCharacter(FILE *fin) {
  char buff[MAX_LEN];
  fscanf(fin, "%[^\n]", buff);
  int i;
  int count = 0;
  for (i = 0; i < strlen(buff); i++) {
    count++;
  }
  printf("%d %s", count, buff);
  

  /* while(!feof(fin)) { */
  /*   fscanf(fin, "%[^\n]", buff); */
  /*   int i; */
  /*   int count = 0; */
  /*   for (i = 0; i < strlen(buff); i++) { */
  /*     count++; */
  /*   } */
  /*   printf("%d %s", count, buff); */
  /* }; */
}

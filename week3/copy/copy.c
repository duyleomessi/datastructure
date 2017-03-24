#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 80

void copy(FILE *fin, FILE *fout);

int main(int argc, char *argv[]) {
  FILE *fptr1, *fptr2;
  char filename1[30] = "lab1.txt";
  char filename2[30] = "lab2.txt";

  if ((fptr1 = fopen(filename1, "r")) == NULL) {
    printf("Cannot open %s\n", filename1);
    return 1;
  }
  if ((fptr2 = fopen(filename2, "w")) == NULL) {
    printf("Cannot open %s\n", filename2);
    return 1;
  }

  copy(fptr1, fptr2);
  fclose(fptr1);
  fclose(fptr2);
  
  return 0;
}

void copy(FILE *fin, FILE *fout) {
  int num;
  char buff[MAX_LEN + 1];
  while(!feof(fin)) {
    num = fread(buff, sizeof(char), MAX_LEN, fin);
    buff[num * sizeof(char)] = '\0';
    printf("%s", buff);
    fwrite(buff, sizeof(char), MAX_LEN, fout);
  }
}

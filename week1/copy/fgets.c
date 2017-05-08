#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 81

void copyContent(FILE *fin, FILE *fout);

int main(int argc, char* argv[]) {
  FILE *fptr1, *fptr2;
  char filename1[] = "original.txt";
  char filename2[] = "copy.txt";

  if( (fptr1 = fopen(filename1, "r")) == NULL) {
    printf("Cannot open %s\n", filename1);
    return 0;
  }

  if ((fptr2 = fopen(filename2, "w")) == NULL) {
    printf("Cannot open %s\n", filename2);
    return 0;
  }

  copyContent(fptr1, fptr2);
  fclose(fptr1);
  fclose(fptr2);
  return 0;
}

void copyContent(FILE *fin, FILE *fout) {
  char str[MAX_LEN];

  while(fgets(str, MAX_LEN, fin) != NULL) {
    printf("string is %s\n", str);
    fputs(str, fout);
  }
}

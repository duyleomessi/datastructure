#include <stdio.h>
#include <stdlib.h>

void display(FILE *fin);

int main(int argc, char *argv[]) {
  if (argc < 1) {
    printf("the command line is incorrect!!!!");
    return 0;
  }

  FILE *fptr;

  if ((fptr = fopen(argv[1], "r")) == NULL) {
    printf("Cannot open %s\n", argv[1]);
    return 0;
  }

  display(fptr);
  fclose(fptr);
  return 0;
}

void display(FILE *fin) {
  char c;
  while((c = fgetc(fin)) != EOF) {
    printf("%c", c);
  }
}

#include <stdio.h>
#include <stdlib.h>

#define MAX 30

void stats(FILE *fin, FILE *fout, int *result);

int main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("The number of argument is not correct!!");
    return 0;
  }

  int result[MAX];
  int i;
  for (i = 0; i < 'z' - 'a'; i++) {
    result[i] = 0;
  }

  FILE *fptr1, *fptr2;
  
  if ((fptr1 = fopen(argv[1], "r")) == NULL) {
    printf("Cannot open %s\n", argv[1]);
    return 0;
  }
  
  char filename[] = "sourcestats.txt";
  if ((fptr2 = fopen(filename, "w")) == NULL) {
    printf("cannot open %s\n", filename);
    return 0;
  }
  
  stats(fptr1, fptr2, result);
 
  fclose(fptr1);
  fclose(fptr2);
  return 0;
};

void stats(FILE *fin, FILE *fout, int *result) {
  char c;
  int i;
  
  while((c = fgetc(fin)) != EOF) {
    if('a' <= c && c <= 'z') result[c - 'a']++;
    else if ('A' <= c && c <= 'Z') result[c - 'A']++;
  };

  for (i = 0; i < 'z' - 'a'; i++) {
    fprintf(fout, "Character %c is appear %d\n", 'a' + i, result[i]);
  }
 
};

#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 80

typedef struct {
  char world[MAX_LEN];
  char meaning[MAX_LEN];
} Dict;

void tranferToDat(FILE *fin, FILE *fout);

int main(int argc, char *argv[]) {
  FILE *fptr1, *fptr2;
  char filename1[] = "dict.txt";
  char filename2[] = "vnedict.dat";
  int i;
  
  if ((fptr1 = fopen(filename1, "r")) == NULL) {
    printf("Cannot open %s\n", filename1);
    return 1;
  }

   if ((fptr1 = fopen(filename2, "w+b")) == NULL) {
     printf("Cannot open %s\n", filename2);
     return 1;
  }

   //tranferToDat(fptr1, fptr2);
   rewind(fptr1);

   /* int start, end; */
   /* printf("Enter the line you want to start: "); */
   /* scanf("%d", &start); */
   /* printf("Enter the line you want to end: "); */
   /* scanf("%d", &end); */
   
   //Dict *dict = (Dict*) malloc((end - start + 1) * sizeof(Dict));

   Dict dict;
   fscanf(fptr1, "%[^\n] : %[^\n]", dict.world, dict.meaning);
   printf("%s %s", dict.world, dict.meaning);
   
    /* if (fseek(fptr1, (start - 1) * sizeof(Dict), SEEK_SET) != 0) { */
    /*   printf("Fseek faild!\n"); */
    /*   return 1; */
    /* } */
    
    // fread(dict, sizeof(Dict), (end - start + 1), fptr2);
    
   /* for (i = 0; i < end - start + 1; i++) { */
   /*   ///fscanf(fptr1, "%[^\n] : %[^\n]", dict[i].world, dict[i].meaning); */
   /*   fscanf(fptr1, "%[^:] : %[^:]", dict[i].world, dict[i].meaning); */
   /*   printf("%s %s", dict[i].world, dict[i].meaning); */
   /* } */
   
   
   /* for (i = 0; i < end - start + 1; i++) { */
   /*   printf(""); */
   /* } */
   
   return 0;
}


void tranferToDat(FILE *fin, FILE *fout) {
  char buff[MAX_LEN + 1];

  while (!feof(fin)) {
    int num = fread(buff, sizeof(char), MAX_LEN, fin);
    buff[num * sizeof(char)] = '\0';
    printf("%s\n", buff);
    fwrite(buff, sizeof(char), MAX_LEN, fout);
  }
};

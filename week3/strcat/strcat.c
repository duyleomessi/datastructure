#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 81

char *my_strcat(char *str1, char *str2);

int main(int argc, char *argv[]) {
  int *p, i;
  char str1[MAX_LEN], str2[MAX_LEN];
  int strlen1, strlen2;
  char *str_cat;
  
  printf("Enter the string 1: ");
  scanf("%[^\n]", str1);

  while (getc(stdin) == '\n') {
    break;
  }
  
  printf("Enter the string 2: ");
  scanf("%[^\n]", str2);

  
   while (getc(stdin) == '\n') {
    break;
  }

   str_cat = my_strcat(str1, str2);
   if (str_cat == NULL) {
     printf("The memory error\n");
     return 1;
   }

   printf("concat string is: %s \n", str_cat);
   free(str_cat);
   return 0;
}

char *my_strcat(char *str1, char *str2) {
  int strlen1, strlen2;
  strlen1 = strlen(str1);
  strlen2 = strlen(str2);

  char *p = (char *) malloc( (strlen1 + strlen2) * sizeof(char) + 1);
  strcpy(p, str1);
  strcpy(p + strlen1, str2);
  return p;
}

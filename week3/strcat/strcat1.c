#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *my_strcat(char *str1, char *str2);

int main(int argc, char *argv[]) {
  int *p, i;
  char str1[50], str2[50];
  int strlen1, strlen2;
  char *str_cat;
  
  printf("Enter the string 1: ");
  scanf("%100s", str1);

  
  printf("Enter the string 2: ");
  scanf("%100s", str2);


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

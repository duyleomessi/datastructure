#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "duy.h"

int main(int argc, char* argv[]) {
  FILE *fptr;
  char filename[] = "out.txt";
  if ((fptr = fopen(filename, "w")) == NULL){
    printf("Cannot open %s\n", filename);
    return 1;
  }

  char choice;
  do {
    int totalNumber;
    printf("Enter the number you wanna input: ");
    scanf("%d", &totalNumber);
    
    int *arr = (int *)malloc(totalNumber * sizeof(int) + 1);
    if (arr == NULL) {
      printf("Memory allocated fail!!!\n");
      return 1;
   } 
    
    
    
    int i;
    int sum = 0;
    for (i = 0; i < totalNumber; i++) {
      int tmp;
      printf("Enter the number %d: ", i + 1);
      scanf("%d", &tmp);
      arr[i] = tmp;
      sum += arr[i];
    }
    arr[i] = sum;
    
    for (i = totalNumber - 1; i >= 0; i--) {
      printf("%d\n", arr[i]);
      fprintf(fptr, "%d ", arr[i]);
    }
    fprintf(fptr, "%d", arr[totalNumber]);
    fprintf(fptr, "%c", '\n');

    free(arr);
    
    myfflush();
    printf("Do you wanna continue?? Press 0 to exit, any key to continue!!! ");
    scanf("%c", &choice);
    
    
  } while(choice != '0');
      
  fclose(fptr);
  return 0;
}


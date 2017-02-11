#include <stdio.h>
#include <stdlib.h>

void swap(int *num1, int *num2) {
  int temp;
  temp = *num1;
  *num1 = *num2;
  *num2 = temp;
}

int main(int argc, char* argv[]) {
  int aValue = 9;
  int bValue = 10;
  
  int *a = &aValue;
  int *b = &bValue;

  printf("a = %d\n b = %d\n", *a, *b);
  
  swap(a, b);
  printf("a = %d\n b = %d\n", *a, *b);
    
  return 0;
}



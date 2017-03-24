#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int i, n, m, *p, *p1;
  printf("How many number do you wanna enter? \n");
  scanf("%d", &n);

  p = (int *)malloc(n * sizeof(int));
  if (p == NULL) {
    printf("Memory allocation failed");
    return 1;
  }

  for (i = 0; i < n; i++) {
    printf("Enter the number %d: ", i + 1);
    scanf("%d", p + i);
  }

  printf("Number in the reverse order: ");
  for (i = n - 1; i >= 0; i--) {
    printf("%d ", *(p + i));
  }
  printf("\n");

  printf("How many number you wanna add more? \n");
  scanf("%d", &m);

  p1 = realloc(p, m);
  if (p1 == NULL) {
    printf("Memory allocated failed!!");
    return 1;
  }
  
  
  for (i = n; i < m+n; i++) {
    printf("Enter number: ");
    scanf("%d", p1 + i);
  }
  
  printf("Number in the reverse order: ");
  for (i = n + m - 1; i >= 0; i--) {
    printf("%d ", *(p1 + i));
  }
  printf("\n");
  
  free(p1);
  return 0;
}


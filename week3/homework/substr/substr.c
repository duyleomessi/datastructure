#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 81

char *my_substr(char *str, int offset, int num);

int main(int argc, char *argv[]) {
  char str[MAX_LEN];
  printf("Enter the string: ");
  scanf("%[^\n]", str);

  while(getc(stdin) == '\n') break;

  char *substring;
  int offset;
  int num;
  printf("Enter the offset and number of character you wanna get: ");
  scanf("%d%d",&offset, &num);
  
  substring = my_substr(str, offset, num);
  if (substring == NULL) {
    printf("Memory failed\n");
    return 1;
  }
  printf("substring is %s\n", substring);
  free(substring);
  return 0;
}

char *my_substr(char *str, int offset, int num) {
  char *sub = (char *)malloc(num * sizeof(char) + 1);
  int i;

  int strleng = strlen(str);
  if (offset < 0 || num <= 0) {
    printf("Offset must be greater or equal to 0 and num must be greater than 0 ");
    exit(1);
  }
  if (offset + num > strleng - 1) {
    printf("The total of offset and num is greater than the leng of string");
    exit(2);
  }
  
  for (i = offset; i < offset + num; i++) {
    sub[i-offset] = str[i];
  }

  return sub;
}



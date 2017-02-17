#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void getAllContent(FILE *fin, char *content);
void encode(FILE *fin, int deviation, char* content);
void decode(FILE *fin, int deviation, char* content);

int main(int argc, char* argv[]) {
  if (argc != 4) {
    printf("the number of params is not correct!!!\n");
    return 0;
  }

  FILE *fptr;
  char content[MAX];
  
  int deviation = atoi(argv[2]);
  
  if ((fptr = fopen(argv[1], "r")) == NULL) {
    printf("Cannot open file %s\n", argv[1]);
    return 0;
  }
  getAllContent(fptr, content);

  if ((fptr = fopen(argv[1], "w")) == NULL) {
    printf("Cannot open file %s\n", argv[1]);
    return 0;
  }

  if (*argv[3] == 'e') {
    encode(fptr, deviation, content);
    fprintf(fptr, "%s", content);
  }
  else if (*argv[3] == 'd') {
    decode(fptr, deviation, content);
    fprintf(fptr, "%s", content);
  }
  fclose(fptr);
  return 0;
}

void getAllContent(FILE *fin, char *content) {
  char c;
  
  while((c = fgetc(fin)) != EOF) {
    *content = c;
    content++;
  }
  *content = '\0';
}

void encode(FILE *fin, int deviation, char* content) {
  printf("Encode\n");
  while( *content != '\0') {
    if ('A' <= *content && *content <= 'Z') {
      if (*content + deviation > 'Z') {
	*content = 'A' + deviation - ('Z' - *content + 1);
      } else {
	*content = *content + deviation;
      }
    } else if ('a' <= *content && *content <= 'z') {
      if (*content + deviation > 'z') {
	*content = 'a' + deviation - ('z' - *content + 1);
      } else {
	*content = *content + deviation;
      }
    }
    content++;
  }
  *content = '\0';
}

void decode(FILE *fin, int deviation, char* content) {
  printf("Decode\n");
  while( *content != '\0') {
    if ('A' <= *content && *content <= 'Z') {
      if (*content - deviation < 'A') {
	*content = 'Z' - (deviation - (*content - 'A' + 1));
      } else {
	*content = *content - deviation;
      }
    } else if ('a' <= *content && *content <= 'z') {
      if (*content - deviation > 'z') {
	*content = 'z' - (deviation - (*content - 'a' + 1));
      } else {
	*content = *content - deviation;
      }
    }
    content++;
  }
  *content = '\0';
};

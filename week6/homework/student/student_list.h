#define ID_LENGTH 12
#define NAME_LENGTH 30

typedef struct {
  char id[ID_LENGTH];
  char name[NAME_LENGTH];
  int grade;
} elementtype;

typedef struct node node;

struct node {
  elementtype element;
  node * next;
};

node* cur = NULL;

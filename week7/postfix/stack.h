#define MAX 100

typedef struct {
  int val;
} elementtype;

typedef struct node node;

struct node {
  elementtype element;
  node *next;
};

node *makeNewNode(elementtype e) {
  node *newNode = (node *)malloc(sizeof(node));
  newNode->element = e;
  newNode->next = NULL;
  return newNode;
}

void initialize(node **top) {
  *top = NULL;
}

int isEmpty(node **top) {
  return *top == NULL;
}

void push(node **top, elementtype e) {
  node *p = makeNewNode(e);
  if (isEmpty) {
    (*top) = p;
  } else {
    p->next = (*top);
    (*top) = p;
  }
  
}

elementtype pop(node **top) {
  if ((*top) == NULL) {
    printf("Underflow\n");
    elementtype e;
    e.val = -1;
    return e;
  }

  node *del = *top;
  elementtype e = del->element;
  *top = (*top)->next;
  free(del);
  return e;
}

void printList(node *top) {
  node *p = top;
  if (p == NULL) {
    printf("Stack is empty\n");
  } else {
    while (p != NULL) {
      printf("%d ", p->element.val);
      p = p->next;
    }
  }
};

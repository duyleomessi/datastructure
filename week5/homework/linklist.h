typedef struct {
  char name[50];
  int memory;
  float screen;
  int price;
} elementtype;

/* typedef struct { */
/*   int val; */
/* } elementtype; */

typedef struct node node;

struct node {
  elementtype element;
  node * next;
};

node* cur = NULL;

void printList(node **root);
node* makeNewNode(elementtype e);
void insertAtTheEnd(node **root, elementtype e);
void insertAtTheBegin(node **root, elementtype e);
node* findPreviousNode(node **root, node *current);
void insertBeforeCurrent(node **root, elementtype e);
void insertAfterCurrent(node **root, elementtype e);
void removeFirstItem(node **root);
void removeLastItem(node **root);
void deleteList(node **root);

void printList(node **root) {
  node *p = *root;
  printf("******Print list******\n\n");
  while(p != NULL) {
    printf("%s %d %f %d\n",  p->element.name, p->element.memory, p->element.screen, p->element.price);
    p = p->next;
  }
  printf("\n");
};

node* makeNewNode(elementtype e) {
  node *p = (node *)malloc(sizeof(node));
  p->element = e;
  p->next = NULL;
  return p;
};

void insertAtTheBegin(node **root, elementtype e) {
  node *newNode = makeNewNode(e);
  if(root == NULL) {
    *root = newNode;
    cur = newNode;
  } else {
    newNode->next = *root;
    *root = newNode;
    cur = newNode;
  }
}

void insertAtTheEnd(node **root, elementtype e) {
  node *newNode = makeNewNode(e);
  node *p = *root;
  if (*root == NULL) {
    *root = newNode;
    cur = newNode;
  } else {
    while(p->next != NULL) {
      p = p->next;
    }
    p->next = newNode;
  }
};


node *findPreviousNode(node**root, node *current) {
  node *p = *root;
  while(p != NULL) {
    if(p->next == current) 
      return p;
    p = p->next;
  }
  
  return NULL;
}

void insertBeforeCurrent(node **root, elementtype e) {
  node *newNode = makeNewNode(e);

  node *pre = findPreviousNode(root, cur);
  if(pre == NULL) {
    insertAtTheBegin(root, e);
  } else {
    newNode->next = cur;
    pre->next = newNode;
    cur = newNode;
  }
}

void insertAfterCurrent(node **root, elementtype e) {
  node *newNode = makeNewNode(e);
  if(*root == NULL) {
    *root = newNode;
    cur = newNode;
  } else {
    newNode->next = cur->next;
    cur->next = newNode;
    cur = newNode;
  }
}

void removeFirstItem(node **root) {
  if (*root == NULL) {
    exit(1);
  } else {
    node *p = *root;
    *root = (*root)->next;
    free(p);
  }
}

void removeLastItem(node **root) {
  node *p = *root;
  if(*root == NULL) {
    exit(1);
  } else if((*root)->next == NULL) {
    free(*root);
  } else {
    while(p->next->next != NULL) {
      p = p->next;
    }
    
    p->next = NULL;
    free(p->next);
  }
  
}

void deleteList(node **root) {
  node *p = *root;
  
  while(*root != NULL) {
    *root = (*root)->next;
    free(p);
    p = *root;
  }
}

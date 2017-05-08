typedef struct {
  char name[50];
  int memory;
  float screen;
  int price;
} elementtype;

typedef struct node node;

struct node {
  elementtype element;
  node *next;
  node *pre;
};

node *cur;

node *makeNewNode(elementtype e);
void printList(node **root);
void insertAtTheBegin(node **root, elementtype e);
void insertAtTheEnd(node **root, elementtype e);

node *makeNewNode(elementtype e) {
  node *p = (node *) malloc(sizeof(node));
  p->element = e;
  p->next = NULL;
  p->pre = NULL;

  return p;
}

void printList(node **root) {
  node *p = *root;

  while(p != NULL) {
    printf("%s %d %f %d\n",  p->element.name, p->element.memory, p->element.screen, p->element.price);
    p = p->next;
  }
  printf("\n");
}

void insertAtTheBegin(node **root, elementtype e) {
  node *newNode = makeNewNode(e);
  if(*root == NULL) {
    *root = newNode;
    cur = newNode;
  } else {
    node *p = *root;
    p->pre = newNode;
    newNode->next = p;
    *root = newNode;
    cur = newNode;
  }
};

node *findLastNode(node **root) {
  if (*root == NULL) {
    return NULL;
  } else {
    node *p = *root;
    while(p->next != NULL) {
      p = p->next;
    }
    return p;
  }
}

void insertAtTheEnd(node **root, elementtype e) {
  node *newNode = makeNewNode(e);
  if (*root == NULL) {
    *root = newNode;
    cur = newNode;
  } else {
    node *last = findLastNode(root);
    last->next = newNode;
    newNode->pre = last;
    cur = newNode;
  }
}


void insertBeforeCurrent(node **root, elementtype e) {
  if (*root == NULL) {
    insertAtTheBegin(root, e);
  } else {
    node *newNode = makeNewNode(e);
    newNode->next = cur;
    cur->pre->next = newNode;
    newNode->pre = cur->pre;
    cur->pre = newNode;
    cur = newNode;
  }
};

void insertAfterCurrent(node **root, elementtype e) {
  if (*root == NULL) {
    insertAtTheEnd(root, e);
  } else {
    node *newNode = makeNewNode(e);
    newNode->next = cur->next;
    cur->next->pre = newNode;
    cur->next = newNode;
    newNode->pre = cur;
    cur = newNode;
  }
}

void removeFirstItem(node **root) {
  if (*root == NULL) {
    exit(1);
  }  else {
    node *p = *root;
    *root = (*root)->next;
    //if ((*root)->pre != NULL) 
    //(*root)->pre = NULL;
    free(p);
  }
}

/* void removeLastItem(node **root) { */
/*   if (*root == NULL) { */
/*     return; */
/*   } else if ((*root)->next == NULL) { */
/*     free(*root); */
/*   }else { */
/*     node *p = *root; */
/*     while(p->next->next != NULL) { */
/*       p = p->next; */
/*     } */

/*     p->next->pre = NULL; */
/*     p->next = NULL; */
    
/*     free(p->next); */
/*   } */
/* } */

void deleteList(node **root) {
  if (*root == NULL) {
    return;
  } else {
    node *p = *root;
    while(*root != NULL) {
      *root = (*root)->next;
      free(p);
      p = *root;
    }
  }
}




typedef struct {
  int val;
} elementtype;

typedef struct node node;

struct node {
  elementtype element;
  node *next;
};

typedef struct {
  node *front, *rear;
} queue;


node *makeNewNode(elementtype e) {
  node *newNode = (node*)malloc(sizeof(node));

  newNode->element = e;
  newNode->next = NULL;

  return newNode;
}

queue *createQueue() {
  queue *q = (queue *)malloc(sizeof(queue));
  q->front = NULL;
  q->rear = NULL;
  return q;
}

int isEmpty(queue **q) {
  if ((*q)->front == NULL && (*q)->rear == NULL) {
    return 1;
  }
  return 0;
}

void enqueue(queue **q, elementtype e) {
  node *p = makeNewNode(e);

  if ((*q)->rear == NULL) {
    (*q)->front = (*q)->rear = p;
  }

  (*q)->rear->next = p;
  (*q)->rear = p;
}

node *dequeue(queue **q) {
  if (isEmpty(q)) {
    printf("list empty\n");
    return NULL;
  }

  node *temp = (*q)->front;
  (*q)->front = (*q)->front->next;

  if ((*q)->front == NULL) {
    (*q)->rear = NULL;
  }

  return temp;
}

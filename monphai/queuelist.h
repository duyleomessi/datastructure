typedef struct{
	char name[20];
	int tancong;
	int phongthu;
	int mau;
	int nhanhnhen;
	int diem; //score
}vosi;

typedef vosi elementType;

typedef struct queue_t{
	elementType e;
	struct queue_t* next;
	struct queue_t* prev;
}queue;

int isEmptyQueue(queue* head){
	return (head == NULL);
}

void enQueue(queue** head, queue** tail, elementType e){
	queue* new = (queue*)malloc(sizeof(queue));
	new->e = e;
	new->next = NULL;
	new->prev = NULL;
	if(isEmptyQueue(*head)){
		*head = new;
		*tail = new;
		return;
	}
	(*tail)->next = new;
	new->prev = (*tail);
	*tail = new;		
}

elementType deQueue(queue** head, queue** tail){
	if(!isEmptyQueue(*head)){
		elementType e;
		queue* tmp = *head;
	    e = (*head)->e;
		
		*head = (*head)->next;
	    free(tmp);
		if(*head == NULL) *tail = NULL;
		else (*head)->prev = NULL;		
		return e;
	}
	else printf("Error: Queue is empty!\n");
}

elementType headElementQueue(queue* head, queue* tail){
	if(!isEmptyQueue(head)){
		return head->e;
	}
	else printf("Error: Queue is empty!\n");
}

elementType tailElementQueue(queue* head, queue* tail){
	if(!isEmptyQueue(head)){
		return tail->e;
	}
	else printf("Error: Queue is empty!\n");
}

void freeQueue(queue** head, queue** tail){
	queue* p = *head;
	while(p != NULL){
		*head = (*head)->next;
		free(p);
		p = *head;
	}
	
	*head = NULL;
	*tail = NULL;
}

void displayNodeQueue(queue* a){
	if(a == NULL){
		printf("This is a NULL element!\n");
		return;
	}
	printf("%-20s%-15d%-15d%-15d%-15d\n", a->e.name, a->e.mau, a->e.tancong, a->e.nhanhnhen, a->e.phongthu); 	
}

void displayQueue(queue* head){
	int i = 1;
	
	if(head != NULL)
		for(queue* p = head; p != NULL; p = p->next){
			printf("%-5d", i++);
			displayNodeQueue(p);
		}
}

queue* makeNewNodeQueue(elementType a){
  queue* new = (queue*)malloc(sizeof(queue));
  new->e = a;
  new->next = NULL;
  new->prev = NULL;

  return new; 
}


void insertAtHeadQueue(queue** head, queue** tail, queue** cur, elementType a){
  queue* new = makeNewNodeQueue(a);

  if(*head == NULL){
    *head = new;
    *tail = new;
    *cur = new;

    return;
  }

  new->next = *head;
  (*head)->prev = new;
  *head = new;
  *cur = new; 
}

//insert an element at the end of the list
void insertAtEndQueue(queue** head, queue** tail, queue** cur, elementType a){
  queue* new = makeNewNodeQueue(a);
  
  if(*head == NULL){
    *head = new;
    *tail = new;
    *cur = new;
    
    return;
  }

  (*tail)->next = new;
  new->prev = *tail;

  *tail = new;
  *cur = *tail;  
}

void insertBeforeCurQueue(queue** head, queue** tail, queue** cur, elementType a){
  if(*head == NULL){
    printf("Error: Empty list!\n");
    return;
  }

  if(*cur == NULL){
    printf("Error: Current element is NULL!\n");
    return;
  }

  //check if cur = head
  if((*cur)->prev == NULL){
    insertAtHeadQueue(head, tail, cur, a);
    return;
  }

  //insert in the middle
  queue* new = makeNewNodeQueue(a);
  
  (*cur)->prev->next = new;
  new->prev = (*cur)->prev;
  (*cur)->prev = new;
  new->next = *cur;
  *cur = new;  
}


void insertAfterCurQueue(queue** head, queue** tail, queue** cur, elementType a){
  if(*head == NULL){
    printf("Error: Empty list!\n");
    return;
  }

  if(*cur == NULL){
    printf("Error: Current element is NULL!\n");
    return;
  }

  //check if cur = tail
  if((*cur)->next == NULL){
    insertAtEndQueue(head, tail, cur, a);
    return;
  }

  //insert in the middle
  queue* new = makeNewNodeQueue(a);
  
  (*cur)->next->prev = new;
  new->next = (*cur)->next;
  (*cur)->next = new;
  new->prev = *cur;
  *cur = new;  
}


void deleteNodeQueue(queue** head, queue** tail, queue** cur){
	if(*cur == NULL){
		printf("Error: NULL element!\n");
		return;
	}

//if cur = head
  if(*cur == *head){
    *head = (*head)->next;
    (*head)->prev = NULL;
    free(*cur);
    *cur = *head;

    return;
  }

  //if cur = tail
  if(*cur == *tail){
    *tail = (*tail)->prev;
    (*tail)->next = NULL;
    free(*cur);
    *cur = *tail;

    return;
  }

  //if cur is at the middle
  
  (*cur)->prev->next = (*cur)->next;
  (*cur)->next->prev = (*cur)->prev;
  queue* p = (*cur)->next;
  free(*cur);
  *cur = p;
}
 
//insert an element at a position
void insertAtPositionQueue(queue** head, queue** tail, queue** cur, elementType a, int n){
  if(n < 0){
    printf("Error: Invalid value of position!\n");
    return;
  }

  if(*head == NULL){
    printf("Error: Empty list!\n");
    return;
  }

  int num = 0;
  queue* p = *head;
  
  while(p != NULL){
    if(num == n)
      break;
    p = p->next;
    num++;
  }
  *cur = p;
  
  if(p != NULL)
    insertBeforeCurQueue(head, tail, cur, a);
  else
    insertAtEndQueue(head, tail, cur, a); 
}

//delete an element at a position
void deleteAtPositionQueue(queue** head, queue** tail, queue** cur, int n){
  if(n < 0){
    printf("Error: Invalid value of position!\n");
    return;
  }

  if(*head == NULL){
    printf("Error: Empty list!\n");
    return;
  }

  int num = 0;
  queue* p = *head;
  
  while(p != NULL){
    if(num == n)
      break;
    p = p->next;
    num++;
  }
  *cur = p;
  
  if(p != NULL)
    deleteNodeQueue(head, tail, cur); 
}

void reverseQueue(queue** head, queue** tail, queue** cur){
	if(*head == NULL || (*head)->next == NULL){
		return;
	}
	
	queue* p;
	queue* p_next;
	/*prev point to the next element in the original list
	  after this step, prev and next will have same direction
	 */
	for(p = *head; p != NULL; p = p->next){
		p->prev = p->next;
	}

	//next point to the pre element in the original list
	for(p = *head; p->prev != NULL; p = p->prev){
	    
		p_next = p->prev;
		p_next->next = p;
	}
	
	(*head)->next = NULL; //head becomes tail

	p = *head;
	*head = *tail;
	*tail = p;	
	*cur = *head;
}

/*split the original list into 2 halve
  n1 is the index of the begining element of list 1
  n2 is the number of element in list 1
 */

//free the list
void freeNodeQueue(queue** head, queue** tail, queue** cur){
  queue* p = *head;
  while(p != NULL){
    *head = (*head)->next;
    free(p);
    p = *head;
  }

  *head = NULL;
  *tail = NULL;
  *cur = NULL; 
}


void splitQueue(queue* head, queue** head1, queue** tail1, queue** cur1, queue** head2, queue** tail2, queue** cur2, int n1, int n2){
	if(*head1 != NULL)
		freeNodeQueue(head1, tail1, cur1);
	if(*head2 != NULL)
		freeNodeQueue(head2, cur2, cur2);
	
	if(head == NULL)
		return;
	//check validity of n1 and n2
	if(n1 < 0 || n2 <= 0)
		return;

	//copy original list to list 2
	queue* cur = head;
	while(cur != NULL){
		insertAtEndQueue(head2, tail2, cur2, cur->e);
		cur = cur->next;
	}

	//find the 1st element of list 2 in list 1
	int num = 0;	
	cur = *head2;
	while(cur != NULL){		
		if(num == n1)
			break;
		cur = cur -> next;
		num ++;
	}
	
	queue* p = cur->next; //p always point to element after cur (used incase cur is removed)
	insertAtEndQueue(head1, tail1, cur1, cur->e);    
	deleteNodeQueue(head2, tail2, &cur);
	*cur2 = cur;
    		
	num = 2;
    while(num <= n2 && p != NULL){
		cur = p;
		p = p->next;
		
		if(cur != NULL){
			insertAtEndQueue(head1, tail1, cur1, cur->e);
			deleteNodeQueue(head2, tail2, &cur);
			*cur2 = cur;
		}
		num++;
	}
}

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
	elementType info;
	struct queue_t* next;
	struct queue_t* prev;
}queuetype;

int isEmptyQueue(queuetype* head){
	return (head == NULL);
}

void enQueue(queuetype** head, queuetype** tail, elementType e){
	queuetype* new = (queuetype*)malloc(sizeof(queuetype));
	new->info = e;
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

elementType deQueue(queuetype** head, queuetype** tail){
	if(!isEmptyQueue(*head)){
		elementType e;
		queuetype* tmp = *head;
	    e = (*head)->info;
		
		*head = (*head)->next;
	    free(tmp);
		if(*head == NULL) *tail = NULL;
		else (*head)->prev = NULL;		
		return e;
	}
	else printf("Error: Queue is empty!\n");
}

elementType headElementQueue(queuetype* head, queuetype* tail){
	if(!isEmptyQueue(head)){
		return head->info;
	}
	else printf("Error: Queue is empty!\n");
}

elementType tailElementQueue(queuetype* head, queuetype* tail){
	if(!isEmptyQueue(head)){
		return tail->info;
	}
	else printf("Error: Queue is empty!\n");
}

void freeQueue(queuetype** head, queuetype** tail){
	queuetype* p = *head;
	while(p != NULL){
		*head = (*head)->next;
		free(p);
		p = *head;
	}
	
	*head = NULL;
	*tail = NULL;
}

void displayNodeQueue(queuetype* a){
	if(a == NULL){
		printf("This is a NULL element!\n");
		return;
	}
	printf("%-20s%-15d%-15d%-15d%-15d\n", a->info.name, a->info.mau, a->info.tancong, a->info.nhanhnhen, a->info.phongthu); 	
}

void displayQueue(queuetype* head){
	int i = 1;
	printf("%-5s%-20s%-15s%-15s%-15s%-15s\n\n", "STT", "BIET HIEU", "MAU", "TAN CONG", "NHANH NHEN", "PHONG THU");
	if(head != NULL)
		for(queuetype* p = head; p != NULL; p = p->next){
			printf("%-5d", i++);
			displayNodeQueue(p);
		}
}

queuetype* makeNewNodeQueue(elementType a){
  queuetype* new = (queuetype*)malloc(sizeof(queuetype));
  new->info = a;
  new->next = NULL;
  new->prev = NULL;

  return new; 
}


void insertAtHeadQueue(queuetype** head, queuetype** tail, queuetype** cur, elementType a){
  queuetype* new = makeNewNodeQueue(a);

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
void insertAtEndQueue(queuetype** head, queuetype** tail, queuetype** cur, elementType a){
  queuetype* new = makeNewNodeQueue(a);
  
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

void insertBeforeCurQueue(queuetype** head, queuetype** tail, queuetype** cur, elementType a){
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
  queuetype* new = makeNewNodeQueue(a);
  
  (*cur)->prev->next = new;
  new->prev = (*cur)->prev;
  (*cur)->prev = new;
  new->next = *cur;
  *cur = new;  
}


void insertAfterCurQueue(queuetype** head, queuetype** tail, queuetype** cur, elementType a){
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
  queuetype* new = makeNewNodeQueue(a);
  
  (*cur)->next->prev = new;
  new->next = (*cur)->next;
  (*cur)->next = new;
  new->prev = *cur;
  *cur = new;  
}


void deleteNodeQueue(queuetype** head, queuetype** tail, queuetype** cur){
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
  queuetype* p = (*cur)->next;
  free(*cur);
  *cur = p;
}
 
//insert an element at a position
void insertAtPositionQueue(queuetype** head, queuetype** tail, queuetype** cur, elementType a, int n){
  if(n < 0){
    printf("Error: Invalid value of position!\n");
    return;
  }

  if(*head == NULL){
    printf("Error: Empty list!\n");
    return;
  }

  int num = 0;
  queuetype* p = *head;
  
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
void deleteAtPositionQueue(queuetype** head, queuetype** tail, queuetype** cur, int n){
  if(n < 0){
    printf("Error: Invalid value of position!\n");
    return;
  }

  if(*head == NULL){
    printf("Error: Empty list!\n");
    return;
  }

  int num = 0;
  queuetype* p = *head;
  
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

void reverseQueue(queuetype** head, queuetype** tail, queuetype** cur){
	if(*head == NULL || (*head)->next == NULL){
		return;
	}
	
	queuetype* p;
	queuetype* p_next;
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
void freeNodeQueue(queuetype** head, queuetype** tail, queuetype** cur){
  queuetype* p = *head;
  while(p != NULL){
    *head = (*head)->next;
    free(p);
    p = *head;
  }

  *head = NULL;
  *tail = NULL;
  *cur = NULL; 
}


void splitQueue(queuetype* head, queuetype** head1, queuetype** tail1, queuetype** cur1, queuetype** head2, queuetype** tail2, queuetype** cur2, int n1, int n2){
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
	queuetype* cur = head;
	while(cur != NULL){
		insertAtEndQueue(head2, tail2, cur2, cur->info);
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
	
	queuetype* p = cur->next; //p always point to element after cur (used incase cur is removed)
	insertAtEndQueue(head1, tail1, cur1, cur->info);    
	deleteNodeQueue(head2, tail2, &cur);
	*cur2 = cur;
    		
	num = 2;
    while(num <= n2 && p != NULL){
		cur = p;
		p = p->next;
		
		if(cur != NULL){
			insertAtEndQueue(head1, tail1, cur1, cur->info);
			deleteNodeQueue(head2, tail2, &cur);
			*cur2 = cur;
		}
		num++;
	}
}

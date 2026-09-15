//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section C - Stack and Queue Questions
Purpose: Implementing the required functions for Question 4 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//////////////////////////////////   linked list /////////////////////////////////

typedef struct _listnode{
   int item;
   struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int size;
   ListNode *head;
   ListNode *tail;
} LinkedList;

////////////////////////////////// stack    ///////////////////////////////////////////////////////

typedef struct stack{
	LinkedList ll;
} Stack;

//////////////////////////////////// queue ////////////////////////////////////////////////////////

typedef struct _queue{
	LinkedList ll;
} Queue;

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void reverse(Queue *q);

void push(Stack *s, int item);
int pop(Stack *s);
int peek(Stack *s);
int isEmptyStack(Stack *s);

void enqueue(Queue *q, int item);
int dequeue(Queue *q);
int isEmptyQueue(Queue *s);

///////////////////////////////////////////////////////////////////////////////////////////////////
void printList(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);
void removeAllItems(LinkedList *ll);

///////////////////////////////////////////////////////////////////////////////////////////////////


int main()
{
    int c, value;

    Queue q;

    //initialize the queue
	q.ll.head =NULL;
	q.ll.size =0;
	q.ll.tail=NULL;

    c =1;

    printf("1: Insert an integer into the queue;\n");
    printf("2: Reverse the queue;\n");
    printf("0: Quit;\n");

    while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the queue: ");
			scanf("%d", &value);
			enqueue(&q, value);
			printf("The queue is: ");
			printList(&(q.ll));
			break;
		case 2:
			reverse(&q); // You need to code this function
			printf("The resulting queue after reversing its elements is: ");
			printList(&(q.ll));
			removeAllItems(&(q.ll));
			break;
		case 0:
			removeAllItems(&(q.ll));
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}

    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void reverse(Queue *q)
{
	if (isEmptyQueue(q)){return;}      // 큐가 비어있으면 뒤집을 게 없으니 바로 종료
	Stack s;                              // 포인터가 아니라 "진짜 Stack 구조체 실체"를 하나 만듦
	s.ll.head = NULL;                       // 직접 초기화 (빈 스택 상태로)
	s.ll.size = 0;
	int popq;                                 // 큐에서 꺼낸 값을 담을 임시 변수
	int sSize;                                  // 스택 크기를 저장해둘 변수
	int pops;                                     // 스택에서 꺼낸 값을 담을 임시 변수

	int qSize = q->ll.size;                          // 원래 큐 크기를 미리 저장 (루프 도는 동안 
	                                                //   크기가 계속 변하니 고정된 기준값 필요)
	
	while (qSize)                                        // 원래 큐 크기만큼 반복
	{
		popq = dequeue(q);                                  // 큐 맨 앞에서 하나 꺼냄
		push(&s, popq);                                       // 꺼낸 값을 스택에 push
		qSize--;                                                // 반복 횟수 카운트 감소
 
	}
	
	sSize = s.ll.size;                    // 옮긴 후의 스택 크기 저장 (이 시점엔 스택 크기 = 원래 큐 크기와 같음)

	while (sSize)                                                  // 스택 크기만큼 반복
	{
		pops = pop(&s);                                              // 스택 맨 위에서 하나 꺼냄
		enqueue(q, pops);                                              // 다시 큐 뒤에 넣음
		sSize--;                                                         // 반복 횟수 감소
	}
}
/*
개선하면 좋을 점:
sSize = s.ll.size;를 굳이 별도로 다시 구할 필요 없이, 사실 qSize와 항상 같은 값이에요 
(큐에서 꺼낸 개수만큼 정확히 스택에 쌓였으니까). 그래서 sSize 변수를 새로 안 만들고 qSize를 재사용해도
(예: 두 번째 while 전에 qSize = q->ll.size 다시 세팅 없이 원래 저장해둔 값을 그대로 또 써도) 결과는 같아요. 
다만 지금처럼 명확하게 별도 변수로 나눈 것도 가독성 면에서 전혀 나쁘지 않습니다 — 선택의 문제예요.
*/

/* 4. (reverseQueue) 스택을 이용해 큐를 뒤집는 C 함수 reverseQueue()를 작성하십시오.
	이 함수는 스택에 값을 추가/제거할 때 반드시 push()와 pop()만 사용해야 하고, 
	큐에 값을 추가/제거할 때는 반드시 enqueue()와 dequeue()만 사용해야 합니다.
	만약 스택이 비어있지 않다면, 시작하기 전에 스택을 반드시 비워야 함을 기억하세요.

	함수 프로토타입은 다음과 같습니다:
	void reverseQueue(Queue *q);

	예시: 큐가 (1, 2, 3, 4, 5)이면 결과 큐는 (5, 4, 3, 2, 1)이 됩니다.

	힌트:
	스택을 사용하기 전에 반드시 초기화할 것.
*/
///////////////////////////////////////////////////////////////////////////////////////////////////

void push(Stack *s, int item){
   insertNode(&(s->ll), 0, item);
}

int pop(Stack *s){
   int item;
   if(!isEmptyStack(s)){
    item = ((s->ll).head)->item;
    removeNode(&(s->ll), 0);
    return item;
   }
    return INT_MIN;
}

int peek(Stack *s){
   return ((s->ll).head)->item;
}

int isEmptyStack(Stack *s){
   if ((s->ll).size == 0)
      return 1;
   return 0;
}

void enqueue(Queue *q, int item){
   insertNode(&(q->ll), q->ll.size, item);
}

int dequeue(Queue *q){
   int item;
   item = ((q->ll).head)->item;
   removeNode(&(q->ll), 0);
   return item;
}

int isEmptyQueue(Queue *q){
   if ((q->ll).size == 0)
      return 1;
   return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}

ListNode * findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}

void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}

//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section C - Stack and Queue Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;	// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;	// You should not change the definition of LinkedList


typedef struct _queue
{
	LinkedList ll;
} Queue;  // You should not change the definition of Queue

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void createQueueFromLinkedList(LinkedList *ll, Queue *q);
void removeOddValues(Queue *q);

void enqueue(Queue *q, int item);
int dequeue(Queue *q);
int isEmptyQueue(Queue *q);
void removeAllItemsFromQueue(Queue *q);

void printList(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);
void removeAllItems(LinkedList *ll);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	int c, i;
	LinkedList ll;
	Queue q;

	c = 1;

	// Initialize the linked list as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	// Initialize the Queue as an empty queue
	q.ll.head = NULL;
	q.ll.size = 0;


	printf("1: Insert an integer into the linked list:\n");
	printf("2: Create the queue from the linked list:\n");
	printf("3: Remove odd numbers from the queue:\n");
	printf("0: Quit:\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the List: ");
			scanf("%d", &i);
			insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			createQueueFromLinkedList(&ll, &q); // You need to code this function
			printf("The resulting queue is: ");
			printList(&(q.ll));
			break;
		case 3:
			removeOddValues(&q); // You need to code this function
			printf("The resulting queue after removing odd integers is: "); 
			printList(&(q.ll));
			removeAllItemsFromQueue(&q);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItemsFromQueue(&q);
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

	}

	return 0;
}


//////////////////////////////////////////////////////////////////////////////////

void createQueueFromLinkedList(LinkedList *ll, Queue *q)
{
	ListNode *temp = ll->head;      // 원본 연결 리스트의 첫 노드부터 순회를 시작할 임시 포인터

	removeAllItemsFromQueue(q);      // 큐가 비어있지 않을 수도 있으니, 시작 전에 무조건 큐를 비움
	                                   //   (내부에서 NULL 체크와 빈 큐 처리까지 다 해주므로 별도 조건문 불필요)
		
	while (temp != NULL) {              // 원본 리스트 끝까지 순회
		enqueue(q, temp->item);           // 현재 노드의 값을 큐에 새로 삽입 (원본은 건드리지 않고 값만 복사)
		temp = temp->next;                 // 다음 노드로 이동
	}
}
/*
개선하면 좋을 점:
굳이 아주 사소한 스타일 팁이라면, removeAllItemsFromQueue(q)를 while 루프보다 먼저 호출하는 순서가 지금처럼 
"먼저 치우고 나서 새로 채운다"는 흐름이라 직관적이에요. 지금 순서 그대로가 자연스럽고 좋습니다.
*/

void removeOddValues(Queue *q)
{
	int size = q->ll.size;         // 원래 큐의 크기를 미리 저장 (루프 도는 동안 enqueue로 size가 다시 늘어나므로, 
								  // 실시간 size를 조건으로 쓰면 안 됨)
	int val;                          // dequeue한 값을 담을 임시 변수

	for (int i = 0; i < size; i++)      // 원래 크기만큼만 정확히 반복 (한 바퀴만 순회)
	{
		val = dequeue(q);                 // 큐 맨 앞에서 값을 하나 꺼냄 (동시에 "순회 + 확인"을 겸함)
		if (val % 2 != 0)                   // 꺼낸 값이 홀수면
			{continue;}                       //   아무것도 안 하고 다음 반복으로 (이미 꺼냈으니 "제거" 완료)
		else if (val % 2 == 0)                // 짝수면
		{
			enqueue(q, val);                    // 다시 큐 뒤에 넣어서 순서를 유지하며 보존
		}
	}
}
/*
개선하면 좋을 점:
아주 사소한 스타일 제안: if (조건) continue; else if (반대조건) {...} 구조는, 사실 val % 2 != 0과 val % 2 == 0이 
서로 정확히 반대라서 else if 대신 그냥 else를 써도 완전히 동일하게 동작해요:
*/

/* 1. (createQueueFromLinkedList) 연결 리스트에 저장된 모든 정수를 큐(연결 리스트 기반)에 
	enqueue하여 큐를 생성하는 C 함수 createQueueFromLinkedList()를 작성하십시오.
	연결 리스트의 첫 번째 노드가 가장 먼저 enqueue되고, 그다음 두 번째 노드, 이런 식으로 진행됩니다.
	만약 큐가 비어있지 않다면, 시작하기 전에 큐를 반드시 비워야 함을 기억하세요.

	함수 프로토타입은 다음과 같습니다:
	void createQueueFromLinkedList(LinkedList *ll, Queue *q);

	예시 입출력 (현재 연결 리스트가 1, 2, 3, 4, 5인 경우):
	결과 연결 리스트: 1 2 3 4 5
	선택 사항(1/2/3/0)을 입력하세요: 2
	결과 큐: 1 2 3 4 5

	힌트:
	ListNode *temp = ll->head;
	while (temp != NULL) {
		// 원하는 동작 수행 //
		temp = temp->next;
	}
*/


//////////////////////////////////////////////////////////////////////////////////

void enqueue(Queue *q, int item) {
	insertNode(&(q->ll), q->ll.size, item);
}

int dequeue(Queue *q) {
	int item;

	if (!isEmptyQueue(q)) {
		item = ((q->ll).head)->item;
		removeNode(&(q->ll), 0);
		return item;
	}
	return -1;
}

int isEmptyQueue(Queue *q) {
	if ((q->ll).size == 0)
		return 1;
	return 0;
}

void removeAllItemsFromQueue(Queue *q)
{
	int count, i;
	if (q == NULL)
		return;
	count = q->ll.size;

	for (i = 0; i < count; i++)
		dequeue(q);
}


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
		if (ll->head == NULL)
		{
			exit(0);
		}
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
		if (pre->next == NULL)
		{
			exit(0);
		}
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

//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section C - Stack and Queue Questions
Purpose: Implementing the required functions for Question 2 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define MIN_INT -1000
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

typedef struct _stack
{
	LinkedList ll;
}Stack;  // You should not change the definition of Stack

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void createStackFromLinkedList(LinkedList *ll , Stack *stack);
void removeEvenValues(Stack *s);

void push(Stack *s , int item);
int pop(Stack *s);
int isEmptyStack(Stack *s);
void removeAllItemsFromStack(Stack *s);

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
	Stack s;

	c = 1;
	// Initialize the linked list as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	// Initalize the stack as an empty stack
	s.ll.head = NULL;
	s.ll.size = 0;

	printf("1: Insert an integer into the linked list:\n");
	printf("2: Create the stack from the linked list:\n");
	printf("3: Remove even numbers from the stack:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			createStackFromLinkedList(&ll, &s); // You need to code this function
			printf("The resulting stack is: ");
			printList(&(s.ll));
			break;
		case 3:
			removeEvenValues(&s); // You need to code this function
			printf("The resulting stack after removing even integers is: ");
			printList(&(s.ll));
			removeAllItemsFromStack(&s);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItemsFromStack(&s);
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

void createStackFromLinkedList(LinkedList *ll, Stack *s)
{
	ListNode *temp = ll->head;      // 원본 연결 리스트의 첫 노드부터 순회 시작

	removeAllItemsFromStack(s);      // 시작 전에 스택을 무조건 비움 (요구사항)

	while (temp != NULL) {              // 원본 리스트 끝까지 순회
		push(s, temp->item);               // 현재 노드의 값을 스택에 push (원본은 안 건드림)
		temp = temp->next;                   // 다음 노드로 이동
	}
}

void removeEvenValues(Stack *s)
{
	if (isEmptyStack(s)){return;}      // base case: 더 꺼낼 게 없으면 재귀 종료
	int val;

	val = pop(s);                        // 맨 위 값을 하나 꺼내서 보관 (호출스택에 저장됨)
	removeEvenValues(s);                  // recursive case: 나머지(더 아래쪽)를 먼저 재귀적으로 처리

	if (val % 2 == 1){push(s, val);}        // 재귀가 끝나고 돌아온 뒤, 보관해둔 값이 홀수면 다시 push
                                              //   (짝수면 그냥 버려짐 — 아무것도 안 하니 자연스럽게 제거됨)
	return;
}
/*
개선하면 좋을 점: 
지난번 세그폴트 원인이었던 s == NULL 체크를 isEmptyStack(s)로 정확히 고치셨고, 
나머지 구조(pop → 재귀 → 조건부 push)도 완벽해요. 딱 하나, 함수 끝의 return;은 void 함수라서 사실 없어도 되는 코드예요 
(함수 끝에 자연히 도달하면 알아서 종료되니까). 있어도 틀린 건 아니고 완전히 무해하지만, 지우면 한 줄 더 간결해집니다.
*/

/* 2. (createStackFromLinkedList) 연결 리스트에 저장된 모든 정수를 스택에 push하여 
	스택(연결 리스트 기반)을 생성하는 C 함수 createStackFromLinkedList()를 작성하십시오.
	연결 리스트의 첫 번째 노드가 가장 먼저 push되고, 그다음 두 번째 노드, 이런 식으로 진행됩니다.
	만약 스택이 비어있지 않다면, 시작하기 전에 스택을 반드시 비워야 함을 기억하세요.

	함수 프로토타입은 다음과 같습니다:
	void createStackFromLinkedList(LinkedList *ll, Stack *stack);

	예시 입출력 (현재 연결 리스트가 1, 3, 5, 6, 7인 경우):
	결과 연결 리스트: 1 3 5 6 7
	선택 사항(1/2/3/0)을 입력하세요: 2
	결과 스택: 7 6 5 3 1

	힌트:
	ListNode *temp = ll->head;
	while (temp != NULL) {
		// 원하는 동작 수행 //
		temp = temp->next;
	}
*/
//////////////////////////////////////////////////////////////////////////////////

void push(Stack *s, int item)
{
	insertNode(&(s->ll), 0, item);
}

int pop(Stack *s)
{
	int item;
	if (s->ll.head != NULL)
	{
		item = ((s->ll).head)->item;
		removeNode(&(s->ll), 0);
		return item;
	}
	else
		return MIN_INT;
}

int isEmptyStack(Stack *s)
{
	if ((s->ll).size == 0)
		return 1;
	else
		return 0;
}


void removeAllItemsFromStack(Stack *s)
{
	if (s == NULL)
		return;
	while (s->ll.head != NULL)
	{
		pop(s);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////


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

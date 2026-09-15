//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section C - Stack and Queue Questions
Purpose: Implementing the required functions for Question 6 */

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


typedef struct stack{
	LinkedList ll;
} Stack; // You should not change the definition of stack

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void removeUntil(Stack *s, int value);

void push(Stack *s, int item);
int pop(Stack *s);
int peek(Stack *s);
int isEmptyStack(Stack *s);
void removeAllItemsFromStack(Stack *s);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	LinkedList ll;
	Stack s;

	// Initialize the linked list as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	// Initalize the stack as an empty stack
	s.ll.head = NULL;
	s.ll.size = 0;

	printf("1: Insert an integer into the stack:\n");
	printf("2: Remove values until the given value;\n");
	printf("0: Quit:\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the stack: ");
			scanf("%d", &i);
			push(&s, i);
			printf("The resulting stack is: ");
			printList(&(s.ll));
			break;
		case 2:
		    printf("Enter an integer value in stack to remove values until that value: ");
			scanf("%d", &i);
			removeUntil(&s,i); // You need to code this function
			printf("The resulting stack after removing values until the given value: ");
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

////////////////////////////////////////////////////////////

void removeUntil(Stack *s, int value)
{
	if (s->ll.size == 0){return;}         // 스택이 처음부터 비어있으면 할 게 없으니 종료
	int size = s->ll.size;                   // 원래 스택 크기를 미리 저장 (반복 횟수 상한선 용도)

	for (int i = 0; i < size; i++)             // 최대 size번까지만 반복 (무한루프 방지용 안전장치)
	{
		if (s->ll.head->item == value)             // 현재 스택 맨 위 값이 찾던 값과 같으면
		{
			return;                                   // 더 이상 지울 필요 없으니 바로 종료
		}
		pop(s);                                         // 같지 않으면 맨 위 값을 하나 제거
	}
	return;
}
/* 
개선하면 좋을 점: 
지난번의 핵심 버그(별도의 sHead 포인터를 만들어서 pop 이후에도 계속 그걸 따라가려다 free된 메모리에 접근했던 문제)를 정확히 고치셨어요 —
매번 s->ll.head를 직접 확인하는 방식으로 바꾸신 게 정답이었습니다. 
한 가지 짚어드리고 싶은 부분은 for문의 i < size 조건의 역할이에요: 이건 "정확히 size번 반복해야 하는" 로직이 아니라, 
"찾는 값이 스택에 아예 없을 경우, 무한히 pop하지 않도록 막아주는 안전장치" 역할이에요. 만약 value가 스택 어디에도 없다면, 
이 상한선이 없으면 빈 스택에서 계속 pop을 시도하다가 문제가 생길 수 있는데(s->ll.head->item에서 head가 NULL이면 크래시), 
지금처럼 size로 상한을 걸어두신 게 좋은 방어적 설계예요.
*/

/* 6. (removeUntilStack) 스택에서 특정 값이 처음 나타날 때까지 값을 계속 pop하는 
	C 함수 removeUntilStack()를 작성하십시오.

	함수 프로토타입은 다음과 같습니다:
	void removeUntilStack(Stack *s, int value);

	예시:
	스택 (1, 2, 3, 4, 5, 6, 7) (맨 왼쪽이 top)에서 value = 4로 호출하면 
	→ 결과 스택: (4, 5, 6, 7)

	스택 (10, 20, 15, 25, 5) (맨 왼쪽이 top)에서 value = 15로 호출하면 
	→ 결과 스택: (15, 25, 5)

	힌트:
	for문도 while문처럼 break로 빠져나올 수 있음
	s->ll.size == 0인 경우도 반드시 고려할 것
*/
//////////////////////////////////////////////////////////////////////////////////

void removeAllItemsFromStack(Stack *s)
{
	if (s == NULL)
		return;
	while (s->ll.head != NULL)
	{
		pop(s);
	}
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

/////////////////////////////////////////////////////////////////////////////////////////

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

int peek(Stack *s){
    if(isEmptyStack(s))
        return MIN_INT;
    else
        return ((s->ll).head)->item;
}

int isEmptyStack(Stack *s)
{
	if ((s->ll).size == 0)
		return 1;
	else
		return 0;
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

//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 7 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


//////////////////////// function prototypes /////////////////////////////////////

// You should not change the prototype of this function
void RecursiveReverse(ListNode **ptrHead);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;
	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;


	printf("1: Insert an integer to the linked list:\n");
	printf("2: Reversed the linked list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			RecursiveReverse(&(ll.head)); // You need to code this function
			printf("The resulting linked list after reversed the given linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////

void RecursiveReverse(ListNode **ptrHead)
{
	ListNode *first = *ptrHead;

	if (first == NULL || first -> next == NULL){return;}
	

	ListNode *rest = first->next;
	RecursiveReverse(&rest);

	first->next->next = first;
	first->next = NULL;
	*ptrHead = rest;

/*
ListNode 두 개, *first, *rest. NULL이면 바로 return. recursive(&rest) 재귀 호출. 
first->next->next = first; first->next = NULL; *ptrHead = rest;
*/
	/* 
	
	7. (recursiveReverse) 주어진 연결 리스트의 next 포인터와 head 포인터를 바꿔가며 
	재귀적으로 리스트를 뒤집는 C 함수 recursiveReverse()를 작성하십시오.

	함수 프로토타입은 다음과 같습니다.	void recursiveReverse(ListNode **ptrHead);

예를 들어, 연결 리스트가 (1, 2, 3, 4, 5)인 경우, 결과 연결 리스트는 (5, 4, 3, 2, 1)이 됩니다.

背, 两个Listnode, *first, *rest, 如有NULL直接return；recursive (&rest) ；
first-next-next = first; first-next = NULL; *ptrHead = rest;
"외워라: ListNode 두 개, *first, *rest. NULL이면 바로 return. recursive(&rest) 재귀 호출. 
first->next->next = first; first->next = NULL; *ptrHead = rest;"
(이건 사실상 재귀 리스트 뒤집기의 거의 완전한 알고리즘 골격이야.)

1: 연결 리스트에 정수를 삽입합니다:
2: 뒤집힌 연결 리스트:
0: 종료:

선택 사항(1/2/0)을 입력하세요: 1
연결 리스트에 추가할 정수를 입력하세요: 1
결과 연결 리스트는 다음과 같습니다: 1

선택 사항(1/2/0)을 입력하세요: 1
연결 리스트에 추가할 정수를 입력하세요: 2
결과 연결 리스트는 다음과 같습니다: 1 2

선택 사항(1/2/0)을 입력하세요: 1
연결 리스트에 추가할 정수를 입력하세요: 3
결과 연결 리스트는 다음과 같습니다: 1 2 3

선택 사항(1/2/0)을 입력하세요: 1
연결 리스트에 추가할 정수를 입력하세요: 4
결과 연결 리스트는 다음과 같습니다: 1 2 3 4

선택 사항(1/2/0)을 입력하세요: 1
연결 리스트에 추가할 정수를 입력하세요: 5
결과 연결 리스트는 다음과 같습니다: 1 2 3 4 5

선택 사항(1/2/0)을 입력하세요: 2
원소를 뒤집은 결과 연결 리스트는 다음과 같습니다: 5 4 3 2 1

선택 사항(1/2/0)을 입력하세요: 0
	
	*/
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

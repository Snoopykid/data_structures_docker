//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 2 */

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
void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll1, ll2;
	int c, i, j;
	c = 1;
	//Initialize the linked list 1 as an empty linked list
	ll1.head = NULL;
	ll1.size = 0;

	//Initialize the linked list 2 as an empty linked list
	ll2.head = NULL;
	ll2.size = 0;

	printf("1: Insert an integer to the linked list 1:\n");
	printf("2: Insert an integer to the linked list 2:\n");
	printf("3: Create the alternate merged linked list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list 1: ");
			scanf("%d", &i);
			j = insertNode(&ll1, ll1.size, i);
			printf("Linked list 1: ");
			printList(&ll1);
			break;
		case 2:
			printf("Input an integer that you want to add to the linked list 2: ");
			scanf("%d", &i);
			j = insertNode(&ll2, ll2.size, i);
			printf("Linked list 2: ");
			printList(&ll2);
			break;
		case 3:
		    printf("The resulting linked lists after merging the given linked list are:\n");
			alternateMergeLinkedList(&ll1, &ll2); // You need to code this function
			printf("The resulting linked list 1: ");
			printList(&ll1);
			printf("The resulting linked list 2: ");
			printList(&ll2);
			removeAllItems(&ll1);
			removeAllItems(&ll2);
			break;
		case 0:
			removeAllItems(&ll1);
			removeAllItems(&ll2);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2)
{
	int FIX_SIZE1 = ll1->size;
	int FIX_SIZE2 = ll2->size;
	int n;
	if(FIX_SIZE1 <= FIX_SIZE2)
	n = FIX_SIZE1;
	if (FIX_SIZE1 > FIX_SIZE2 )
	n = FIX_SIZE2;

	for (int i = 0; i < n ; i++)
	{
		int value = ll2->head->item;
		removeNode(ll2, 0);
		insertNode(ll1, 2*i+1, value);
	}
	
	
	
	
    /* 
	2. (alternateMergeLL) 두 번째 리스트의 노드들을 첫 번째 리스트의 교대(번갈아 나오는) 위치에 삽입하는 
	C 함수 alternateMergeLL()을 작성하십시오. 두 번째 리스트의 노드는 첫 번째 리스트에 
	교대로 들어갈 자리가 있을 때만 삽입되어야 합니다.

两个fixsize变量
"두 개의 fixsize 변수가 필요함" — 즉 병합 도중 리스트 길이가 계속 바뀌니까, 시작 전에 원래 LinkedList1과 
LinkedList2의 크기를 각각 변수에 저장해두고 그 값을 기준으로 반복 횟수를 정하라는 뜻.


	함수 프로토타입은 다음과 같습니다.	void alternateMergeLL(LinkedList *ll1, LinkedList *ll2);

예를 들어, 주어진 두 연결 리스트가 LinkedList1과 LinkedList2라고 가정합니다:
	LinkedList1: 1, 2, 3
	LinkedList2: 4, 5, 6, 7

결과 연결 리스트는 다음과 같습니다:
	LinkedList1: 1, 4, 2, 5, 3, 6
	LinkedList2: 7

첫 번째 리스트가 두 번째 리스트보다 큰 경우, 두 번째 리스트는 비어있게 됩니다. 예를 들어, 
	주어진 두 연결 리스트가 LinkedList1과 LinkedList2라고 가정합니다:
	LinkedList1: 1, 5, 7, 3, 9, 11
	LinkedList2: 6, 10, 2, 4

결과 연결 리스트는 다음과 같습니다:
	LinkedList1: 1, 6, 5, 10, 7, 2, 3, 4, 9, 11
	LinkedList2: 비어있음

다음은 입력 및 출력 예시입니다 (현재 연결 리스트 1: 1, 2, 3, 연결 리스트 2: 4, 5, 6, 7인 경우):

Linked list 1: 1 2 3
Linked list 2: 4 5 6 7
선택 사항(1/2/3/0)을 입력하세요: 3
주어진 연결 리스트를 병합한 결과 연결 리스트는 다음과 같습니다:
Linked list 1: 1 4 2 5 3 6
Linked list 2: 7
	*/



}

///////////////////////////////////////////////////////////////////////////////////

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


ListNode *findNode(LinkedList *ll, int index){

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

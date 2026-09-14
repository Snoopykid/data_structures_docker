//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 5 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototype of this function
void frontBackSplitLinkedList(LinkedList* ll, LinkedList *resultFrontList, LinkedList *resultBackList);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *l);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	LinkedList ll;
	LinkedList resultFrontList, resultBackList;

	//Initialize the linked list as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	//Initialize the front linked list as an empty linked list
	resultFrontList.head = NULL;
	resultFrontList.size = 0;

	// Initialize the back linked list as an empty linked list
	resultBackList.head = NULL;
	resultBackList.size = 0;

	printf("1: Insert an integer to the linked list:\n");
	printf("2: Split the linked list into two linked lists, frontList and backList:\n");
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
			insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The resulting linked lists after splitting the given linked list are:\n");
			frontBackSplitLinkedList(&ll, &resultFrontList, &resultBackList); // You need to code this function
			printf("Front linked list: ");
			printList(&resultFrontList);
			printf("Back linked list: ");
			printList(&resultBackList);
			printf("\n");
			removeAllItems(&ll);
			removeAllItems(&resultFrontList);
			removeAllItems(&resultBackList);
			break;
		case 0:
			removeAllItems(&ll);
			removeAllItems(&resultFrontList);
			removeAllItems(&resultBackList);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void frontBackSplitLinkedList(LinkedList *ll, LinkedList *resultFrontList, LinkedList *resultBackList)
{
	int FIX_SIZE = ll->size;              // 원본 리스트의 전체 크기를 고정해서 저장
	                                       //   (아래에서 ll을 계속 비워나가므로 size가 계속 줄어들기 때문)
	int FRONT_SIZE = (FIX_SIZE + 1) / 2;  // 앞쪽 리스트로 보낼 개수 (홀수면 앞쪽이 1개 더 많음, 올림 계산)
	int BACK_SIZE = FIX_SIZE - FRONT_SIZE; // 뒤쪽 리스트로 보낼 개수 (나머지)

	for (int i = 0; i < FRONT_SIZE; i++)     // 앞쪽 개수만큼 반복
	{
		int val = ll->head->item;              // 원본 리스트의 맨 앞 값을 읽음
		insertNode(resultFrontList, i, val);   // 그 값을 앞쪽 결과 리스트의 i번 자리(=끝)에 삽입
		removeNode(ll, 0);                      // 원본 리스트에서 방금 읽은 맨 앞 노드 제거
	}
	for (int i = 0; i < BACK_SIZE; i++)        // 뒤쪽 개수만큼 반복 (이 시점에 원본엔 뒷부분만 남음)
	{
		int val = ll->head->item;               // 남은 원본의 맨 앞 값을 읽음 (원래 리스트 기준 뒷부분)
		insertNode(resultBackList, i, val);      // 뒤쪽 결과 리스트의 i번 자리에 삽입
		removeNode(ll, 0);                        // 원본에서 제거
	}
/*
개선하면 좋을 점: 
1. 스타일 면에서 FIX_SIZE, FRONT_SIZE, BACK_SIZE를 전부 대문자로 쓰는 건 보통 매크로 상수(#define)나 const에 쓰는 컨벤션이에요. 
이건 지역변수라서 fixSize, frontSize, backSize처럼 일반 변수 표기로 쓰는 게 C 스타일 관례에 더 맞아요 
(동작엔 전혀 문제없지만, 가독성/컨벤션 측면).

*/


	/* 
	
	5. (frontBackSplitLL) 단일 연결 리스트를 앞쪽 절반과 뒤쪽 절반, 두 개의 하위 리스트로 
	분할하는 C 함수 frontBackSplitLL()을 작성하십시오. 원소 개수가 홀수인 경우, 
	남는 하나의 원소는 앞쪽(front) 리스트에 들어가야 합니다. frontBackSplitLL()은 
	frontList와 backList, 두 리스트를 출력합니다.

	함수 프로토타입은 다음과 같습니다.
	void frontBackSplitLL(LinkedList *ll, LinkedList *resultFrontList, LinkedList *resultBackList);

fixsize = ll->size
"원래 크기를 fixsize에 저장" — 2번과 같은 맥락으로, 분할 도중 리스트 크기가 변하니 시작 전 
원본 크기를 따로 저장해두고 그걸로 앞/뒤 절반을 나누라는 힌트.

예를 들어, 주어진 연결 리스트가 2, 3, 5, 6, 7이라고 가정합니다.
결과 연결 리스트 frontList와 backList는 다음과 같습니다:
	frontList: 2, 3, 5
	backList: 6, 7

다음은 입력 및 출력 예시입니다:
1: 연결 리스트에 정수를 삽입합니다:
2: 연결 리스트를 출력합니다:
3: 연결 리스트를 두 개의 연결 리스트(frontList, backList)로 분할합니다:
0: 종료:

선택 사항(1/2/3/0)을 입력하세요: 1
연결 리스트에 추가할 정수를 입력하세요: 2
결과 연결 리스트는 다음과 같습니다: 2

선택 사항(1/2/3/0)을 입력하세요: 1
연결 리스트에 추가할 정수를 입력하세요: 3
결과 연결 리스트는 다음과 같습니다: 2 3

선택 사항(1/2/3/0)을 입력하세요: 1
연결 리스트에 추가할 정수를 입력하세요: 5
결과 연결 리스트는 다음과 같습니다: 2 3 5

선택 사항(1/2/3/0)을 입력하세요: 1
연결 리스트에 추가할 정수를 입력하세요: 6
결과 연결 리스트는 다음과 같습니다: 2 3 5 6

선택 사항(1/2/3/0)을 입력하세요: 1
연결 리스트에 추가할 정수를 입력하세요: 7
결과 연결 리스트는 다음과 같습니다: 2 3 5 6 7

선택 사항(1/2/3/0)을 입력하세요: 2
결과 연결 리스트는 다음과 같습니다: 2 3 5 6 7

선택 사항(1/2/3/0)을 입력하세요: 3
주어진 연결 리스트를 분할한 결과 연결 리스트는 다음과 같습니다:
Front linked list: 2 3 5
Back linked list: 6 7
	
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

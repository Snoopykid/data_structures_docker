//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

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

//You should not change the prototype of this function
int insertSortedLL(LinkedList *ll, int item);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
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

	printf("1: Insert an integer to the sorted linked list:\n");
	printf("2: Print the index of the most recent input value:\n");
	printf("3: Print sorted linked list:\n");
	printf("0: Quit:");

	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertSortedLL(&ll, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The value %d was added at index %d\n", i, j);
			break;
		case 3:
			printf("The resulting sorted linked list is: ");
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

//////////////////////////////////////////////////////////////////////////////////

int insertSortedLL(LinkedList *ll, int item)
{
	int curindex = 0;
	ListNode *cur = ll -> head;

	while (cur != NULL)
	{
		if (item == cur -> item)
			return -1;
		if (item < cur -> item)
			break;
		curindex += 1;
		cur = cur -> next;
	}
	insertNode(ll, curindex, item);

	return curindex;


	/* 사용자에게 정수를 입력받도록 한 다음, 해당 정수를 오름차순으로 연결 리스트에 삽입하는 C 함수 insertSortedLL()을 작성하십시오. 
	insertSortedLL() 함수는 현재 연결 리스트에 이미 존재하는 정수는 삽입하지 못하도록 해야 합니다. 이 함수는
	새 항목이 추가된 인덱스 위치를 반환해야 하며, 함수가 성공적으로 완료되지 못한 경우 -1을 반환해야 합니다. 
	링크드 리스트는 정렬된 링크드 리스트이거나 빈 리스트라고 가정해도 됩니다. 
	
	遍历条件是curindex <= ll->index，走到底直接塞，在途中每个比较有三种情况。
"순회 조건은 curindex <= ll->index. 끝까지 가면 그냥 바로 삽입. 도중에 매 비교마다 3가지 경우가 있음."


	함수 프로토타입은 다음과 같습니다.	int insertSortedLL(LinkedList *ll, int item);

현재 연결 리스트가 2,  3,  5,  7,  9라고 가정합니다. 값 8을 전달하여 insertSortedLL()을 호출하면 
다음과 같은 연결 리스트가 생성됩니다.	2,  3,  5,  7,  8,  9.
이 함수는 새로운 항목이 추가된 인덱스 위치를 다음과 같이 반환해야 합니다:
값 8이 인덱스 4에 추가되었습니다.

현재 연결 리스트가 5,  7,  9,  11, 15인 경우,
값 7을 인수로 전달하여 insertSortedLL()을 호출하면 다음과 같은 연결 리스트가 생성됩니다:	5,  7,  9,  11,  15.

함수가 성공적으로 완료되지 않았습니다(값 7이 연결 리스트에 삽입되지 않음).
따라서 -1을 반환해야 합니다: 값 7이 인덱스 -1에 추가되었습니다

다음은 몇 가지 입력 및 출력 예시입니다:
1: 정렬된 연결 리스트에 정수를 삽입합니다:
2: 가장 최근에 입력된 값의 인덱스를 출력합니다: 
3: 정렬된 연결 리스트를 출력합니다:
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

선택할 항목을 입력하세요(1/2/3/0): 1
연결 리스트에 추가할 정수를 입력하세요: 7
결과 연결 리스트는 다음과 같습니다: 2 3 5 7

선택할 항목을 입력하세요(1/2/3/0): 1
연결 리스트에 추가할 정수를 입력하세요: 9
결과 연결 리스트는 다음과 같습니다: 2 3 5 7 9

선택 사항(1/2/3/0)을 입력하세요: 1
연결 리스트에 추가할 정수를 입력하세요: 8
결과 연결 리스트는 다음과 같습니다: 2 3 5 7 8 9

선택할 값을 입력하세요(1/2/3/0): 2
인덱스 4에 값 8이 추가되었습니다.

선택할 값을 입력하세요(1/2/3/0): 3
정렬된 연결 리스트는 다음과 같습니다: 2 3 5 7 8 9

선택 사항(1/2/3/0)을 입력해 주세요: 1
연결 리스트에 추가할 정수를 입력해 주세요: 5
결과 연결 리스트는 다음과 같습니다: 2 3 5 7 8 9

선택 사항(1/2/3/0)을 입력해 주세요: 2
값 5가 인덱스 -1에 추가되었습니다

선택 사항(1/2/3/0)을 입력해 주세요: 3
정렬된 연결 리스트는 다음과 같습니다: 2 3 5 7 8 9

선택 사항(1/2/3/0)을 입력하세요: 1
연결 리스트에 추가할 정수를 입력하세요: 11
결과 연결 리스트는 다음과 같습니다: 2 3 5 7 8 9 11

선택할 값(1/2/3/0)을 입력하세요: 2
값 11이 인덱스 6에 추가되었습니다.

선택할 값(1/2/3/0)을 입력하세요: 3
정렬된 링크드 리스트는 다음과 같습니다: 2 3 5 7 8 9 11

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

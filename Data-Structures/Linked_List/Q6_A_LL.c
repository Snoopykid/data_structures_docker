//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 6 */

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
int moveMaxToFront(ListNode **ptrHead);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	int c, i, j;
	c = 1;

	LinkedList ll;
	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;


	printf("1: Insert an integer to the linked list:\n");
	printf("2: Move the largest stored value to the front of the list:\n");
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
			j=insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			moveMaxToFront(&(ll.head));  // You need to code this function
			printf("The resulting linked list after moving largest stored value to the front of the list is: ");
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

int moveMaxToFront(ListNode **ptrHead)
{
	if(*ptrHead == NULL || (*ptrHead)->next == NULL) return 0;

	ListNode *max = *ptrHead;
	ListNode *maxpre = NULL;
	ListNode *pre = *ptrHead;
	ListNode *cur = pre -> next;

	while (cur != NULL)
	{
		if (cur->item > max->item){
			max = cur;
			maxpre = pre;
		}
		pre = cur;
		cur = cur->next;
	}
	if(maxpre == NULL){return 0;}

	maxpre->next = max->next;
	max->next = *ptrHead;
	*ptrHead = max;

	return 0;
    /* 

	6. (moveMaxToFront) 정수로 이루어진 연결 리스트를 최대 한 번만 순회하여, 가장 큰 값을 
	가진 노드를 리스트의 맨 앞으로 옮기는 C 함수 moveMaxToFront()를 작성하십시오.

如果只有一个term，直接过；else 设三个listnode，一个遍历(遍完要初始化)，一个指最大，一个指最大前面；
front->next == max->next; max->next = *ptrHead; *ptrHead = max;

"노드가 하나뿐이면 그냥 넘어간다. 아니면 ListNode 3개를 준비: 하나는 순회용(순회 끝나면 초기화 필요), 
하나는 최댓값 노드를 가리킴, 하나는 최댓값 노드의 바로 앞 노드를 가리킴.
(최댓값을 떼어낼 때) front->next = max->next; max->next = *ptrHead; *ptrHead = max;"
(참고: 여기 ==는 비교가 아니라 대입 =의 오타/필기 실수로 보임 — 최댓값 노드를 리스트에서 떼어내서 
맨 앞에 붙이는 3줄짜리 전형적인 패턴.)


	함수 프로토타입은 다음과 같습니다.	int moveMaxToFront(ListNode **ptrHead);

这个函数头不同于之前：1.故Insertnode功能不可用 2.ListNode *temp；temp = *ptrHead；
"이 함수 시그니처는 이전 문제들과 다름: 1) 그래서 (이전에 쓰던) Insertnode 함수를 그대로 쓸 수 없음. 
2) ListNode *temp; temp = *ptrHead;로 시작해야 함."

예를 들어, 연결 리스트가 (30, 20, 40, 70, 50)인 경우, 결과 연결 리스트는 (70, 30, 20, 40, 50)이 됩니다.

1: 연결 리스트에 정수를 삽입합니다:
2: 가장 큰 값을 가진 노드를 리스트의 맨 앞으로 옮깁니다:
0: 종료:

선택 사항(1/2/0)을 입력하세요: 1
연결 리스트에 추가할 정수를 입력하세요: 30
연결 리스트는 다음과 같습니다: 30

선택 사항(1/2/0)을 입력하세요: 1
연결 리스트에 추가할 정수를 입력하세요: 20
연결 리스트는 다음과 같습니다: 30 20

선택 사항(1/2/0)을 입력하세요: 1
연결 리스트에 추가할 정수를 입력하세요: 40
연결 리스트는 다음과 같습니다: 30 20 40

선택 사항(1/2/0)을 입력하세요: 1
연결 리스트에 추가할 정수를 입력하세요: 70
연결 리스트는 다음과 같습니다: 30 20 40 70

선택 사항(1/2/0)을 입력하세요: 1
연결 리스트에 추가할 정수를 입력하세요: 50
연결 리스트는 다음과 같습니다: 30 20 40 70 50

선택 사항(1/2/0)을 입력하세요: 2
결과 연결 리스트는 다음과 같습니다: 70 30 20 40 50

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

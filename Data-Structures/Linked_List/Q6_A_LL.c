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
	// 리스트가 비어있거나(NULL) 노드가 1개뿐이면 이미 "정렬된" 상태나 다름없으니 그냥 종료

	ListNode *max = *ptrHead;    // 지금까지 찾은 "최댓값 노드"를 가리킴 (처음엔 head로 초기화)
	ListNode *maxpre = NULL;      // max 노드의 "바로 앞 노드" (max가 head면 앞 노드가 없으므로 NULL)
	ListNode *pre = *ptrHead;      // 현재 순회 중인 cur의 "바로 앞 노드"
	ListNode *cur = pre->next;      // 실제로 순회하며 비교할 현재 노드 (head 다음부터 시작)

	while (cur != NULL)               // 리스트 끝까지 순회
	{
		if (cur->item > max->item){    // 지금까지의 최댓값보다 cur이 더 크면
			max = cur;                    // 최댓값 노드 갱신
			maxpre = pre;                  // 그 최댓값의 "앞 노드"도 같이 갱신 (나중에 떼어내려면 필요)
		}
		pre = cur;                       // pre를 한 칸 전진
		cur = cur->next;                  // cur도 한 칸 전진
	}
	if(maxpre == NULL){return 0;}        // 만약 최댓값이 이미 head였다면(한 번도 갱신 안 됐으면) 
	                                       //   maxpre가 계속 NULL → 이동할 필요 없음, 그냥 종료

	maxpre->next = max->next;              // max 노드를 리스트에서 떼어냄 (앞뒤를 직접 연결해서 우회)
	max->next = *ptrHead;                   // max의 next를 원래 head로 연결 (max를 새 head로 만들 준비)
	*ptrHead = max;                          // 실제로 head를 max로 교체

	return 0;

/*
개선하면 좋을 점: 
1. 함수가 int를 반환하는데 모든 경로에서 항상 0만 반환해요. 실제로 "값이 이동했는지 여부"를 의미 있게 쓰려면, 이동이 일어난 경우엔 return 1;, 
이동이 필요 없던 경우엔 return 0;처럼 반환값에 의미를 담는 게 자연스러워요 (현재는 반환값이 사실상 아무 정보도 안 주고 있어서, void로 바꾸거나 
반환값을 제대로 활용하는 것 중 하나가 좋을 것 같아요). 다만 이건 과제 프로토타입이 이미 int로 고정되어 있다면 그 스펙을 따르되, 
내부적으로 1/0을 의미 있게 구분해주는 게 더 깔끔합니다.
*/

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

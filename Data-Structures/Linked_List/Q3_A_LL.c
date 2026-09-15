//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 3 */

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
void moveOddItemsToBack(LinkedList *ll);

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
	printf("2: Move all odd integers to the back of the linked list:\n");
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
			moveOddItemsToBack(&ll); // You need to code this function
			printf("The resulting linked list after moving odd integers to the back of the linked list is: ");
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

void moveOddItemsToBack(LinkedList *ll)
{
	int checked = 0;        // 지금까지 "확인 완료"한 원소 개수 (종료 조건용 카운터)
	int n = ll->size;        // 원래 리스트 크기를 미리 저장 (중요! 리스트가 계속 재배치되는 동안 size 자체는 안 바뀌지만, "몇 개를 다 확인했는지" 기준을 고정해야 함)
	int i = 0;                // 지금 검사 중인 인덱스 위치
	int val = 0;               // 홀수를 발견했을 때 그 값을 임시로 보관할 변수

	while (checked < n)        // 원래 크기(n)만큼 전부 확인할 때까지 반복
	{
		if (findNode(ll, i)->item % 2 == 1){   // i번째 노드 값이 홀수인지 확인
			val = findNode(ll, i)->item;         // 홀수 값을 미리 저장 (removeNode 하면 사라지니까)
			removeNode(ll, i);                    // i번째 노드를 리스트에서 제거
			insertNode(ll, ll->size, val);        // 제거한 값을 리스트 맨 끝에 다시 삽입
			checked += 1;                          // 확인한 개수 +1 (i는 그대로 유지! 왜냐면 제거 후 다음 원소가 i번 자리로 당겨졌으니까)
		}
		else{
			i += 1;             // 짝수면 그대로 두고 다음 인덱스로 이동
			checked += 1;        // 확인한 개수 +1
		}
	}
/*
개선하면 좋을 점:
1. O(n²) 시간복잡도

2. 만약 성능이 중요한 문제라면, findNode를 반복 호출하지 말고 ListNode *cur 포인터 하나로 직접 순회하면서 짝/홀 판단 + 재배치를 하는 게 훨씬 효율적이에요 

3. findNode(ll, i)->item % 2 == 1과 그 아래 findNode(ll, i)->item이 같은 걸 두 번 호출하고 있어요. ListNode *node = findNode(ll, i);로 한 번만 저장해서
 재사용하면 중복 호출을 줄일 수 있어요.
*/

	
	/* 
	3. (moveOddItemsToBackLL) 연결 리스트에서 모든 홀수 정수를 리스트의 뒤쪽으로 옮기는 
	C 함수 moveOddItemsToBackLL()을 작성하십시오.

	先找出odd number个数count，遍历count次每次放后一个，重要的是temp和count在每次遍历都要初始化
"먼저 홀수 개수(count)를 구한다. 그 다음 count번 반복하면서 매번 하나씩 뒤로 보낸다. 중요한 건 
temp와 count는 매 반복마다 초기화해야 한다는 것."

	함수 프로토타입은 다음과 같습니다.	void moveOddItemsToBackLL(LinkedList *ll);

다음은 몇 가지 입력 및 출력 예시입니다:

연결 리스트가 2, 3, 4, 7, 15, 18인 경우:
홀수 정수를 리스트 뒤쪽으로 옮긴 결과 연결 리스트는 다음과 같습니다: 2 4 18 3 7 15

연결 리스트가 2, 7, 18, 3, 4, 15인 경우:
홀수 정수를 리스트 뒤쪽으로 옮긴 결과 연결 리스트는 다음과 같습니다: 2 18 4 7 3 15

현재 연결 리스트가 1, 3, 5인 경우:
홀수 정수를 리스트 뒤쪽으로 옮긴 결과 연결 리스트는 다음과 같습니다: 1 3 5

현재 연결 리스트가 2 4 6인 경우:
홀수 정수를 리스트 뒤쪽으로 옮긴 결과 연결 리스트는 다음과 같습니다: 2 4 6
	
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

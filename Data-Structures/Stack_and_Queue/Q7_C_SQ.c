//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section C - Stack and Queue Questions
Purpose: Implementing the required functions for Question 7 */

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


typedef struct stack
{
	LinkedList ll;
} Stack; // You should not change the definition of stack

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
int balanced(char *expression);

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
	char ch, str[256];
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

	printf("1: Enter a string:\n");
	printf("2: Check whether expressions comprised of the characters ()[]{} is balanced:\n");
	printf("0: Quit:\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Enter expressions without spaces to check whether it is balanced or not: ");
			scanf("%s", str);
			break;
        case 2:
            if(balanced(str))
                printf("not balanced!\n");
            else
                printf("balanced!\n");
			break;
		case 0:
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

	}

	return 0;
}

////////////////////////////////////////////////////////////
int balanced(char *expression)
{
	if (expression == NULL){return 1;}      // NULL 문자열이면 애매한 케이스지만 일단 균형된 것으로 처리
	Stack s;                                   // Stack 실체를 직접 선언 (포인터 아님)
	s.ll.head = NULL;                            // 빈 스택으로 초기화
	s.ll.size = 0;
	int top;                                       // peek로 확인한 스택 맨 위 값을 담을 변수

	for (int i = 0; expression[i] != '\0'; i++)      // 문자열 끝(\0)까지 한 글자씩 순회
	{
		if (expression[i] == '(' || expression[i] == '[' ||expression[i] == '{')
		{                                                    // 여는 괄호를 만나면
			push(&s, expression[i]);                             // 스택에 push
		}
		else if (expression[i] == ')' || expression[i] == ']' ||expression[i] == '}')
		{                                                          // 닫는 괄호를 만나면
			top = peek(&s);                                          // 스택 맨 위를 확인 (꺼내지 않고 보기만)
			if ((top == '(' && expression[i] == ')') ||                // 짝이 맞는 조합인지 확인
				(top == '{' && expression[i] == '}') || 
				(top == '[' && expression[i] == ']') )
			{
				pop(&s);                                                  // 짝이 맞으면 실제로 pop해서 제거
			}
			
		}
		
	}
	
	if (s.ll.size != 0)                                               // 순회가 다 끝난 뒤 스택에 뭔가 남아있으면
	{
		return 1;                                                        // 짝이 안 맞은 게 있다는 뜻 → not balanced
	}
	else {return 0;}                                                    // 스택이 완전히 비었으면 → balanced
		
}
/*
개선하면 좋을 점: 
로직 정확하고, 지난번 겪으셨던 두 가지 버그(peek(&s) == expression[i]로 잘못 비교했던 것, &s.ll.size != 0으로 주소를 비교했던 것) 
모두 정확히 고치셨어요. 딱 한 가지 참고할 점: 짝이 하나도 안 맞는 케이스(예: (])를 만났을 때 지금 코드는 "아무것도 안 하고 그냥 다음 문자로 넘어가는" 
방식이에요. 최종적으로는 스택에 뭔가 남아서 어차피 1(not balanced)로 정확히 걸러지긴 하지만, 만약 "짝이 안 맞는 순간 바로 실패 처리하고 싶다"면 
else 절을 추가해서 즉시 return 1;을 할 수도 있어요. 다만 지금 방식도 최종 결과는 항상 정확하니, 이건 순수히 "더 빨리 끝낼지 vs 끝까지 다 훑을지"의 
스타일 차이일 뿐 버그는 아닙니다.
*/

/* 7. (balanced) ()[]{} 문자로만 구성된 표현식이 "균형이 맞는지(balanced)" 판별하는 
	C 함수 balanced()를 작성하십시오.

	함수 프로토타입은 다음과 같습니다:
	int balanced(char *expression);

	예시: 아래는 괄호의 순서와 개수가 맞아서 balanced인 경우입니다:
	()
	([])
	{[]()[]}

	예시 입출력:
	1: 문자열 입력
	2: ()[]{} 문자로 구성된 표현식이 balanced인지 확인
	0: 종료
	선택 사항(1/0)을 입력하세요: 1
	공백 없이 표현식을 입력하세요: {[]()[]}
	{[]()[]}
	balanced!
	선택 사항(1/0)을 입력하세요: 0

	balanced가 아닌 예시:
	{{)]
	[({{)])

	예시 입출력:
	선택 사항(1/0)을 입력하세요: 1
	공백 없이 표현식을 입력하세요: [({{)])
	[({{)])
	not balanced!
	선택 사항(1/0)을 입력하세요: 0

	힌트:
	스택 사용
	여는 괄호 {[( 를 만나면 스택에 push
	닫는 괄호 }])를 만나면 스택의 top(peek)과 짝이 맞는지 확인 → 맞으면 pop
	마지막에 스택이 비어있는지 확인
*/
////////////////////////////////////////////////////////////

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

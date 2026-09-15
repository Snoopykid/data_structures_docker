//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section E - Binary Trees Questions
Purpose: Implementing the required functions for Question 7 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _btnode
{
    int item;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;   // You should not change the definition of BTNode

/////////////////////////////////////////////////////////////////////////////////

typedef struct _stackNode
{
    BTNode *btnode;
    struct _stackNode *next;
} StackNode;

typedef struct _stack
{
    StackNode *top;
} Stack;


///////////////////////// Function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
int smallestValue(BTNode *node);

BTNode *createBTNode(int item);

BTNode *createTree();
void push( Stack *stack, BTNode *node);
BTNode* pop(Stack *stack);

void printTree(BTNode *node);
void removeAll(BTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
    char e;
    int c, value;
    BTNode *root;

    c = 1;
    root = NULL;

    printf("1: Create a binary tree.\n");
    printf("2: Smallest value;\n");
    printf("0: Quit;\n");


    while(c != 0)
    {
        printf("Please input your choice(1/2/0): ");
        if( scanf("%d",&c) > 0)
        {
            switch(c)
            {
            case 1:
                removeAll(&root);
                root = createTree();
                printf("The resulting binary tree is: ");
                printTree(root);
                printf("\n");
                break;
            case 2:
                value = smallestValue(root);
                printf("Smallest value of the binary tree is: %d\n",value);
                removeAll(&root);
                break;
            case 0:
                removeAll(&root);
                break;
            default:
                printf("Choice unknown;\n");
                break;
            }
        }
        else
        {
            scanf("%c",&e);
        }

    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////

int smallestValue(BTNode *node)
{
    if (node == NULL){return 9999;}       // 빈 노드는 "매우 큰 값"으로 취급 (비교에서 항상 짐)
    int minimum = node->item;                // 일단 내 값으로 시작
    int left_v = smallestValue(node->left);      // 왼쪽 서브트리의 최솟값
    int right_v = smallestValue(node->right);      // 오른쪽 서브트리의 최솟값

    if ( minimum <= left_v){minimum = minimum;}      // (사실상 아무것도 안 함)
    else if (minimum > left_v){minimum = left_v;}       // 왼쪽이 더 작으면 갱신
    if (minimum <= right_v){minimum = minimum;}           // (역시 아무것도 안 함)
    else if (minimum > right_v){minimum = right_v;}          // 오른쪽이 더 작으면 갱신
    
    return minimum;
}
/*
개선하면 좋을 점 두 가지:

minimum = minimum;은 자기 자신에게 대입하는 무의미한 코드예요 (아무 효과 없음). 이런 식으로 바꾸면 더 깔끔해요:

if (left_v < minimum) minimum = left_v;
if (right_v < minimum) minimum = right_v;

동작은 완전히 같고, "조건이 참일 때만 갱신"이라는 의도가 더 명확히 드러나요.

9999라는 매직넘버(sentinel)의 위험성: 만약 트리가 완전히 비어있는 상태(root == NULL)에서 이 함수를 바로 호출하면, 
9999가 그대로 "가장 작은 값"으로 반환돼요 — 실제로는 "트리가 비어서 값이 없다"는 뜻인데, 마치 진짜 값인 것처럼 출력될 수 있어요. 
또한 만약 트리에 9999 이상의 진짜 값이 들어올 수 있는 상황이라면 (이 문제에서는 가능성이 낮아 보이지만), 로직이 꼬일 여지가 있어요. 
실무였다면 NULL 트리는 별도로 에러 처리하거나, INT_MAX(더 안전한 "무한대" 값)를 쓰는 게 낫습니다.

smallestValue — BST였다면 O(h)로 끝날 일이에요
지금 함수는 힌트에서도 명시했듯 "BST가 아니라 일반 이진 트리이므로" 모든 노드를 다 봐야 했던 거예요. 근데 만약 이게 진짜 BST였다면:
BST에서 최솟값은 항상 "맨 왼쪽 끝 노드"에 있어요. (왼쪽 자식 < 부모, 오른쪽 자식 > 부모라는 규칙 때문에)

int smallestValueBST(BTNode *node) {
    while (node->left != NULL) node = node->left;
    return node->item;
}

이러면 재귀도 필요 없고, O(n) → O(h)로 단축돼요. 균형 잡힌 트리면 O(log n)까지 줄어드는 거죠. 모든 노드를 볼 필요 자체가 없어져요 — 트리의 "정렬되어 있다"는 정보 자체가 지름길이 되는 거예요.

시간복잡도: O(n), 공간복잡도: O(h)
*/

/* 7. (smallestValue) 주어진 트리에 저장된 값들 중 가장 작은 값을 반환하는 
	C 함수 smallestValue()를 작성하십시오. 이 함수는 트리의 루트 노드 포인터를 
	파라미터로 받습니다.

	함수 프로토타입은 다음과 같습니다:
	int smallestValue(BTNode *node);

	예시: 이진 트리 (25, 30, 65, 50, 10, 60, 75) (Figure 7)에서, 
	가장 작은 값은 10입니다.

	예시 입출력:
	1: 이진 트리 생성
	2: 가장 작은 값
	0: 종료

	선택 사항(1/2/0)을 입력하세요: 1
	root 값을 입력하세요: 50
	50의 왼쪽 자식: 30, 오른쪽 자식: 60
	30의 왼쪽 자식: 25, 오른쪽 자식: 65
	60의 왼쪽 자식: 10, 오른쪽 자식: 75
	(나머지는 전부 'a'로 NULL 처리)
	결과 이진 트리: 25 30 65 50 10 60 75

	선택 사항(1/2/0)을 입력하세요: 2
	이진 트리의 가장 작은 값: 10

	선택 사항(1/2/0)을 입력하세요: 0

	힌트:
	BST(이진 탐색 트리)가 아니라 일반 이진 트리이므로, 모든 노드를 
	재귀적으로 순회하면서 현재까지 발견한 최솟값과 비교/갱신해야 함
	(왼쪽/오른쪽 서브트리의 최솟값과 현재 노드 값 중 가장 작은 걸 return)
*/
//////////////////////////////////////////////////////////////////////////////////

BTNode *createBTNode(int item)
{
    BTNode *newNode = malloc(sizeof(BTNode));
    newNode->item = item;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

//////////////////////////////////////////////////////////////////////////////////


BTNode *createTree()
{
    Stack stack;
    BTNode *root, *temp;
    char s;
    int item;

    stack.top = NULL;
    root = NULL;
    printf("Input an integer that you want to add to the binary tree. Any Alpha value will be treated as NULL.\n");
    printf("Enter an integer value for the root: ");
    if(scanf("%d",&item) > 0)
    {
        root = createBTNode(item);
        push(&stack,root);
    }
    else
    {
        scanf("%c",&s);
    }

    while((temp =pop(&stack)) != NULL)
    {

        printf("Enter an integer value for the Left child of %d: ", temp->item);

        if(scanf("%d",&item)> 0)
        {
            temp->left = createBTNode(item);
        }
        else
        {
            scanf("%c",&s);
        }

        printf("Enter an integer value for the Right child of %d: ", temp->item);
        if(scanf("%d",&item)>0)
        {
            temp->right = createBTNode(item);
        }
        else
        {
            scanf("%c",&s);
        }

        if(temp->right != NULL)
            push(&stack,temp->right);
        if(temp->left != NULL)
            push(&stack,temp->left);
    }
    return root;
}

void push( Stack *stack, BTNode *node)
{
    StackNode *temp;

    temp = malloc(sizeof(StackNode));
    if(temp == NULL)
        return;
    temp->btnode = node;
    if(stack->top == NULL)
    {
        stack->top = temp;
        temp->next = NULL;
    }
    else
    {
        temp->next = stack->top;
        stack->top = temp;
    }
}

BTNode* pop(Stack *stack)
{
    StackNode *temp, *top;
    BTNode *ptr;
    ptr = NULL;

    top = stack->top;
    if(top != NULL)
    {
        temp = top->next;
        ptr = top->btnode;

        stack->top = temp;
        free(top);
        top = NULL;
    }
    return ptr;
}

void printTree(BTNode *node)
{
    if(node == NULL) return;

    printTree(node->left);
    printf("%d ",node->item);
    printTree(node->right);
}

void removeAll(BTNode **node)
{
    if(*node != NULL)
    {
        removeAll(&((*node)->left));
        removeAll(&((*node)->right));
        free(*node);
        *node = NULL;
    }
}

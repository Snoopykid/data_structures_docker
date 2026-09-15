//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section E - Binary Trees Questions
Purpose: Implementing the required functions for Question 4 */

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
int sumOfOddNodes(BTNode *root);

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
    int c,oddValueCount;
    BTNode *root;

    c = 1;
    oddValueCount = 0;
    root = NULL;

    printf("1: Create a binary tree.\n");
    printf("2: Find the sum of all odd numbers in the binary tree.\n");
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
                oddValueCount = sumOfOddNodes(root);
                printf("The sum of all odd numbers in the binary tree is: %d.\n",oddValueCount);
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

int sumOfOddNodes(BTNode *node)

{
    if (node == NULL){return 0;}     // 빈 노드는 더할 게 없음

    int value = 0;
    int left = 0;
    int right = 0;

    left = sumOfOddNodes(node->left);      // 왼쪽 서브트리 홀수 합
    right = sumOfOddNodes(node->right);      // 오른쪽 서브트리 홀수 합

    value += node->item;                       // 현재 노드 값을 저장
    if (value % 2 == 1){return left + right + value;}   // 홀수면 더해서 반환
    else {return left + right;}                             // 짝수면 그냥 전달
}
/*
개선하면 좋을 점: 로직 정확해요. 다만 int value = 0; value += node->item;은 그냥 int value = node->item; 한 줄로 충분해요 — 
0으로 초기화한 뒤 바로 더하는 건 불필요한 단계예요 (동작은 완전히 같음, 그냥 코드가 한 줄 줄어드는 정도).

시간복잡도: O(n), 공간복잡도: O(h)
*/

/* 4. (sumOfOddNodes) 정수형 이진 트리의 루트 노드를 가리키는 포인터를 받아서, 
	트리 안의 모든 홀수 값들의 합을 반환하는 재귀 C 함수 sumOfOddNodes()를 
	작성하십시오.

	함수 프로토타입은 다음과 같습니다:
	int sumOfOddNodes(BTNode *root);

	예시: 이진 트리 (11, 40, 35, 50, 80, 60, 85) (Figure 4)에서, 
	모든 홀수 값(11, 35, 85)의 합은 131입니다.

	예시 입출력:
	1: 이진 트리 생성
	2: 트리 안의 모든 홀수 값의 합 구하기
	0: 종료

	선택 사항(1/2/0)을 입력하세요: 1
	root 값을 입력하세요: 50
	50의 왼쪽 자식: 40, 오른쪽 자식: 60
	40의 왼쪽 자식: 11, 오른쪽 자식: 35
	60의 왼쪽 자식: 80, 오른쪽 자식: 85
	(나머지는 전부 'a'/'b' 등으로 NULL 처리)
	결과 이진 트리: 11 40 35 50 80 60 85

	선택 사항(1/2/0)을 입력하세요: 2
	트리 안의 모든 홀수 값의 합: 131.

	선택 사항(1/2/0)을 입력하세요: 0

	힌트:
	NULL이면 return 0
	값이 홀수면 → return (왼쪽 재귀 + 오른쪽 재귀 + 현재 값)
	그 외엔 → return (왼쪽 재귀 + 오른쪽 재귀)
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


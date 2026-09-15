//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section E - Binary Trees Questions
Purpose: Implementing the required functions for Question 6 */

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
void printSmallerValues(BTNode *node, int m);

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
    printf("2: Print smaller values.\n");
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
                printf("Enter an integer value to print smaller values: ");
                scanf("%d",&value);
                printf("The values smaller than %d are: ", value);
                printSmallerValues(root,value);
                printf("\n");
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
        {printf("\n");
            scanf("%c",&e);
        }

    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void printSmallerValues(BTNode *node, int m)
{
	if (node == NULL){return;}
    if (node->item < m ){printf("%d ", node->item);}
    printSmallerValues(node->left, m);
    printSmallerValues(node->right, m);

    return;
}

/* 6. (printSmallerValues) 이진 트리의 루트 노드 포인터와 기준값 m을 받아서, 
	트리 안에 저장된 값들 중 m보다 작은 모든 정수를 출력하는 
	C 함수 printSmallerValues()를 작성하십시오.

	함수 프로토타입은 다음과 같습니다:
	void printSmallerValues(BTNode *node, int m);

	예시: 이진 트리 (25, 30, 65, 50, 10, 60, 75) (Figure 6)에서, 
	printSmallerValues()를 value = 55로 호출하면 55보다 작은 값들 
	(50, 30, 25, 10)이 출력됩니다.

	예시 입출력:
	1: 이진 트리 생성
	2: 작은 값들 출력
	0: 종료

	선택 사항(1/2/0)을 입력하세요: 1
	root 값을 입력하세요: 50
	50의 왼쪽 자식: 30, 오른쪽 자식: 60
	30의 왼쪽 자식: 25, 오른쪽 자식: 65
	60의 왼쪽 자식: 10, 오른쪽 자식: 75
	(나머지는 전부 'a'로 NULL 처리)
	결과 이진 트리: 25 30 65 50 10 60 75

	선택 사항(1/2/0)을 입력하세요: 2
	작은 값을 출력할 기준 정수를 입력하세요: 55
	55보다 작은 값들: 50 30 25 10

	선택 사항(1/2/0)을 입력하세요: 0

	힌트 (본 문제는 preorder 순회 사용):
	root(현재 노드) → left → right 순서로 방문
	현재 노드 값이 m보다 작으면 출력
	왼쪽/오른쪽 자식에 대해 재귀 호출
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


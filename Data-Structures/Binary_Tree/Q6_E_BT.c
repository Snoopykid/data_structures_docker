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
    if (node == NULL){return;}          // 빈 노드는 출력할 게 없음
    if (node->item < m ){printf("%d ", node->item);}     // 기준값보다 작으면 출력
    printSmallerValues(node->left, m);                       // 왼쪽 서브트리 검사
    printSmallerValues(node->right, m);                         // 오른쪽 서브트리 검사

    return;
}
/*
개선하면 좋을 점: 정확해요. 여기서 짚을 점 하나 — 이건 BST(이진 탐색 트리)가 아니라 일반 이진 트리라서, 값이 어디에나 있을 수 있어요. 
그래서 "왼쪽이 다 크니까 안 가봐도 된다" 같은 가지치기(pruning)가 불가능하고, 모든 노드를 다 방문해야만 정확한 결과가 나와요. 
(만약 이게 BST였다면, node->item >= m일 때 오른쪽 서브트리를 건너뛰는 최적화가 가능했을 텐데, 일반 이진 트리라 그럴 수 없어요.)

printSmallerValues — BST였다면 오른쪽 가지 전체를 건너뛸 수 있어요

if (node->item < m ){printf("%d ", node->item);}
printSmallerValues(node->left, m);
printSmallerValues(node->right, m);

일반 이진 트리에서는 값이 어디에나 있을 수 있어서, 왼쪽/오른쪽 둘 다 무조건 다 봐야 해요. 근데 진짜 BST라면:
node->item >= m이면, 오른쪽 서브트리는 전부 node->item보다 크다는 게 BST 규칙으로 보장되니까, 오른쪽엔 m보다 작은 값이 하나도 없을 게 확실해요. 그러니 오른쪽 가지 전체를 아예 안 봐도 돼요.

if (node->item < m) {
    printf("%d ", node->item);
    printSmallerValuesBST(node->right, m);   // 왼쪽도 오른쪽도 다 볼 필요 있음
}
printSmallerValuesBST(node->left, m);          // 왼쪽은 항상 봐야 함 (m보다 작은 값이 있을 수 있으니)

이러면 **최악의 경우(트리 전체가 m보다 작을 때)엔 여전히 O(n)**이지만, 평균적으로는 가지치기(pruning) 덕분에 훨씬 빨라져요 — 특히 m이 작으면 오른쪽 서브트리들을 대거 건너뛰게 되거든요.

시간복잡도: O(n) (전체 노드 방문이 불가피), 공간복잡도: O(h)
*/

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


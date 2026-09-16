//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section E - Binary Trees Questions
Purpose: Implementing the required functions for Question 3 */

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

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
int countOneChildNodes(BTNode *node);

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
    int c,s;
    BTNode *root;

    c = 1;
    root = NULL;


    printf("1: Create a binary tree.\n");
    printf("2: Count the number of nodes that have exactly one child node.\n");
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
                s = countOneChildNodes(root);
                printf("The number of nodes that have exactly one child node is: %d.\n", s);
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

int countOneChildNodes(BTNode *node)

{
    if (node == NULL){return 0;}      // 빈 노드는 셀 게 없음

    // int lLeaf = countOneChildNodes(node->left);    // 왼쪽 서브트리에서 찾은 개수
    // int rLeaf = countOneChildNodes(node->right);      // 오른쪽 서브트리에서 찾은 개수

    int lLeaf;
    int rLeaf;

    lLeaf = countOneChildNodes(node->left);    // 왼쪽 서브트리에서 찾은 개수
    rLeaf = countOneChildNodes(node->right);      // 오른쪽 서브트리에서 찾은 개수


    if ((node->left != NULL && node->right == NULL) ||    // 왼쪽만 있거나
        (node->left == NULL && node->right != NULL)){return lLeaf + rLeaf + 1;}  // 오른쪽만 있으면 +1
    else {return lLeaf + rLeaf;}     // 둘 다 있거나 둘 다 없으면 그대로 전달
 
}
/*
개선하면 좋을 점: 정확해요. 조건문을 XOR(배타적 논리합) 느낌으로 좀 더 짧게 쓸 수도 있어요:

****** if ((node->left == NULL) != (node->right == NULL)) *******

"왼쪽이 NULL인지"와 "오른쪽이 NULL인지"가 **서로 다를 때(하나만 NULL일 때)**를 뜻하는데, 지금 코드보다 한 줄이 짧아져요 (기능은 완전히 동일, 취향 차이).

시간복잡도: O(n), 공간복잡도: O(h)
*/


/* 3. (countOneChildNodes) 이진 트리의 루트 노드를 가리키는 포인터를 받아서, 
	자식이 정확히 하나뿐인 노드의 개수를 반환하는 C 함수 countOneChildNodes()를 
	작성하십시오.

	함수 프로토타입은 다음과 같습니다:
	int countOneChildNodes(BTNode *root)

	예시: 이진 트리 (10, 20, 55, 30, 50, 60, 80) (Figure 3)에서, 
	자식이 하나뿐인 노드는 2개이며 (빨간색으로 표시), 그 노드들은 20과 60입니다.

	예시 입출력:
	1: 이진 트리 생성
	2: 자식이 하나뿐인 노드 개수 세기
	0: 종료

	선택 사항(1/2/0)을 입력하세요: 1
	root 값을 입력하세요: 50
	50의 왼쪽 자식: 20, 오른쪽 자식: 60
	20의 왼쪽 자식: 10, 오른쪽 자식: 30
	30의 왼쪽 자식: 55, 오른쪽 자식: a(NULL)
	60의 왼쪽 자식: a(NULL), 오른쪽 자식: 80
	(그 외 리프 노드들은 전부 'a'로 NULL 처리)
	결과 이진 트리: 10 20 55 30 50 60 80

	선택 사항(1/2/0)을 입력하세요: 2
	자식이 정확히 하나뿐인 노드의 개수: 2

	선택 사항(1/2/0)을 입력하세요: 0

	힌트:
	NULL이면 return 0
	자식이 하나뿐이면 → return (왼쪽+오른쪽 재귀 결과의 합) + 1
	그 외엔 → return (왼쪽+오른쪽 재귀 결과의 합)
*/
///////////////////////////////////////////////////////////////////////////////////

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


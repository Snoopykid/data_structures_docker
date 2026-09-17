//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section E - Binary Trees Questions
Purpose: Implementing the required functions for Question 8 */

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
int hasGreatGrandchild(BTNode *node);

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
    int c,value;
    BTNode *root;

    c = 1;
    root = NULL;

    printf("1: Create a binary tree.\n");
    printf("2: Find the great grandchildren of the binary tree.\n");
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
                printf("\nThe values stored in all nodes of the tree that has at least one great-grandchild are: ");
                hasGreatGrandchild(root);
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

int hasGreatGrandchild(BTNode *node)
{
    if (node == NULL){return 0;}         // 빈 노드의 깊이는 0
    int depth1 = hasGreatGrandchild(node->left);    // 왼쪽에서 계산된 깊이
    int depth2 = hasGreatGrandchild(node->right);      // 오른쪽에서 계산된 깊이

    int max = (depth1 >= depth2) ? depth1 : depth2;      // 더 깊은 쪽을 선택
    if (max >= 3){printf("\n%d\n", node->item);}            // 3단계 이상 자손이 있으면 출력

    return max+1;    // 나(현재 노드)까지 포함해서 한 단계 올려서 위로 전달
}
/*
개선하면 좋을 점:

로직은 앞서 겪으셨던 버그(depth1/depth2를 각각 따로 검사하다 중복 출력됐던 것)가 정확히 고쳐진 상태예요. 
최댓값 하나로 합쳐서 딱 한 번만 검사하는 게 정확해요.
printf("\n%d\n", ...)가 값마다 앞뒤로 줄바꿈을 두 번씩 넣고 있어요. 예시 출력(증손자를 적어도 하나 가진 노드들의 값: 50)처럼 
한 줄에 공백으로 구분해서 나열하는 걸 원한다면, printf("%d ", node->item);처럼 단순화하는 게 출력 형식과 더 맞을 수 있어요 
(지금 코드는 노드마다 앞뒤에 빈 줄이 생겨서 출력이 지저분해 보일 수 있어요).

시간복잡도: O(n), 공간복잡도: O(h)
*/

/* 8. (hasGreatGrandchild) 이진 트리의 모든 노드 중 "증손자(great-grandchild, 
	즉 3대 아래 자손)"를 적어도 하나 가진 노드들의 값을 출력하는 
	재귀 C 함수 hasGreatGrandchild()를 작성하십시오. 이 함수는 파라미터 하나
	(이진 트리의 루트 노드 포인터)만 받습니다.

	함수 프로토타입은 다음과 같습니다:
	int hasGreatGrandchild(BTNode *node);

	예시: 이진 트리 (25, 30, 20, 65, 50, 10, 60, 75, 15) (Figure 9)에서, 
	노드 50이 증손자(빨간색으로 표시)를 가지고 있습니다.

	예시 입출력:
	1: 이진 트리 생성
	2: 트리의 증손자 찾기
	0: 종료

	선택 사항(1/2/0)을 입력하세요: 1
	root 값을 입력하세요: 50
	50의 왼쪽 자식: 30, 오른쪽 자식: 60
	30의 왼쪽 자식: 25, 오른쪽 자식: 65
	65의 왼쪽 자식: 20, 오른쪽 자식: a(NULL)
	60의 왼쪽 자식: 10, 오른쪽 자식: 75
	75의 왼쪽 자식: a(NULL), 오른쪽 자식: 15
	(나머지는 전부 'a'로 NULL 처리)
	결과 이진 트리: 25 30 20 65 50 10 60 75 15

	선택 사항(1/2/0)을 입력하세요: 2
	증손자를 적어도 하나 가진 노드들의 값: 50

	선택 사항(1/2/0)을 입력하세요: 0

	힌트 (본질적으로 각 노드의 "깊이(depth)"를 검사하는 문제):
	함수 자체가 현재 노드 기준의 depth를 return하도록 설계
	만약 현재 노드의 depth가 3 이상이면 → 그 노드의 값을 출력
	(depth 3 이상 = 그 조상 노드 입장에서 증손자에 해당한다는 뜻)
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


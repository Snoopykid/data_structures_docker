//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section E - Binary Trees Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////
typedef struct _btnode{
	int item;
	struct _btnode *left;
	struct _btnode *right;
} BTNode;   // You should not change the definition of BTNode

/////////////////////////////////////////////////////////////////////////////////

typedef struct _stackNode{
    BTNode *btnode;
    struct _stackNode *next;
}StackNode;

typedef struct _stack{
    StackNode *top;
}Stack;

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
int identical(BTNode *tree1, BTNode *tree2);

BTNode* createBTNode(int item);

BTNode* createTree();
void push( Stack *stk, BTNode *node);
BTNode* pop(Stack *stk);

void printTree(BTNode *node);
void removeAll(BTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
    int c, s;
    char e;
    BTNode *root1, *root2;

    root1 = NULL;
    root2 = NULL;
    c = 1;

    printf("1: Create a binary tree1.\n");
    printf("2: Create a binary tree2.\n");
    printf("3: Check whether two trees are structurally identical.\n");
    printf("0: Quit;\n");

    while(c != 0){
        printf("Please input your choice(1/2/3/0): ");
        if(scanf("%d", &c) > 0)

        {

            switch(c)
            {
            case 1:
                removeAll(&root1);
                printf("Creating tree1:\n");
                root1 = createTree();
                printf("The resulting tree1 is: ");
                printTree(root1);
                printf("\n");
                break;
            case 2:
                removeAll(&root2);
                printf("Creating tree2:\n");
                root2 = createTree();
                printf("The resulting tree2 is: ");
                printTree(root2);
                printf("\n");
                break;
            case 3:
                s = identical(root1, root2);
                if(s){
                printf("Both trees are structurally identical.\n");
                }
                else{
                printf("Both trees are different.\n");
                }
                removeAll(&root1);
                removeAll(&root2);
                break;
            case 0:
                removeAll(&root1);
                removeAll(&root2);
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

int identical(BTNode *tree1, BTNode *tree2)

{
    if (tree1 == NULL && tree2 == NULL){return 1;}
    else if (tree1 == NULL || tree2 == NULL){return 0;}
    // 값 비교 라인. 값이 다르면 return 0;
    else if (tree1->item != tree2->item){return 0;}

    return (identical(tree1->left, tree2->left) && identical(tree1->right, tree2->right));
    
    
    // identical 결과 곱해서 return
    /*
   	힌트 (거의 정답 골격):
	둘 다 NULL이면 return 1
	하나만 NULL이면 return 0
	값이 다르면 return 0
	그 외엔 왼쪽/오른쪽 서브트리의 identical 결과를 곱해서(AND) return
    */
}

/* 1. (identical) 두 개의 이진 트리(tree1, tree2)가 "구조적으로 동일한지" 판별하는 
	재귀 C 함수 identical()을 작성하십시오. 두 트리가 구조적으로 동일하면 1을 반환하고, 
	그렇지 않으면 0을 반환합니다. 두 이진 트리가 구조적으로 동일하다는 것은, 
	둘 다 비어있거나, 둘 다 비어있지 않으면서 왼쪽/오른쪽 서브트리가 
	(같은 값을 가진 노드들이 같은 방식으로 배치되어) 서로 같은 경우를 말합니다.

	함수 프로토타입은 다음과 같습니다:
	int identical(BTNode *tree1, BTNode *tree2);

	예시: tree1 (1, 3, 2, 5, 4, 7, 8)과 tree2 (1, 3, 2, 5, 4, 7, 8)이 
	Figure 1처럼 주어지면, tree1과 tree2는 구조적으로 동일합니다.

	예시 입출력:
	1: 이진 트리1 생성
	2: 이진 트리2 생성
	3: 두 트리가 구조적으로 동일한지 확인
	0: 종료

	선택 사항(1/2/3/0)을 입력하세요: 1
	트리1 생성 중: 이진 트리에 추가할 정수를 입력하세요. 알파벳 값은 
	모두 NULL로 처리됩니다.
	root 값을 입력하세요: 5
	5의 왼쪽 자식 값을 입력하세요: 3
	5의 오른쪽 자식 값을 입력하세요: 7
	... (이하 각 노드마다 왼쪽/오른쪽 자식 입력, 'a'는 NULL 처리)
	결과 tree1: 1 3 2 5 4 7 8

	선택 사항(1/2/3/0)을 입력하세요: 2
	(tree2도 동일하게 5, 3, 7, 1, 2, 4, 8로 생성)
	결과 tree2: 1 3 2 5 4 7 8

	선택 사항(1/2/3/0)을 입력하세요: 3
	두 트리는 구조적으로 동일합니다.

	선택 사항(1/2/3/0)을 입력하세요: 0

	힌트 (거의 정답 골격):
	둘 다 NULL이면 return 1
	하나만 NULL이면 return 0
	값이 다르면 return 0
	그 외엔 왼쪽/오른쪽 서브트리의 identical 결과를 곱해서(AND) return
*/

/////////////////////////////////////////////////////////////////////////////////

BTNode *createBTNode(int item){
    BTNode *newNode = malloc(sizeof(BTNode));
    newNode->item = item;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

//////////////////////////////////////////////////////////////////////////////////


BTNode *createTree()
{
    Stack stk;
    BTNode *root, *temp;
    char s;
    int item;

    stk.top = NULL;
    root = NULL;

    printf("Input an integer that you want to add to the binary tree. Any Alpha value will be treated as NULL.\n");
    printf("Enter an integer value for the root: ");
    if(scanf("%d",&item) > 0)
    {
        root = createBTNode(item);
        push(&stk,root);
    }
    else
    {
        scanf("%c",&s);
    }

    while((temp =pop(&stk)) != NULL)
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
            push(&stk,temp->right);
        if(temp->left != NULL)
            push(&stk,temp->left);
    }
    return root;
}

void push( Stack *stk, BTNode *node){
    StackNode *temp;

    temp = malloc(sizeof(StackNode));
    if(temp == NULL)
        return;
    temp->btnode = node;
    if(stk->top == NULL){
        stk->top = temp;
        temp->next = NULL;
    }
    else{
        temp->next = stk->top;
        stk->top = temp;
    }
}

BTNode* pop(Stack *stk){
   StackNode *temp, *top;
   BTNode *ptr;
   ptr = NULL;

   top = stk->top;
   if(top != NULL){
        temp = top->next;
        ptr = top->btnode;

        stk->top = temp;
        free(top);
        top = NULL;
   }
   return ptr;
}

void printTree(BTNode *node){
    if(node == NULL) return;

    printTree(node->left);
    printf("%d ",node->item);
    printTree(node->right);
}

void removeAll(BTNode **node){
    if(*node != NULL){
        removeAll(&((*node)->left));
        removeAll(&((*node)->right));
        free(*node);
        *node = NULL;
    }
}

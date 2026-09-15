
//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section F - Binary Search Trees Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024
///////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode{
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode;   // You should not change the definition of BSTNode

typedef struct _QueueNode {
	BSTNode *data;
	struct _QueueNode *nextPtr;
}QueueNode; // You should not change the definition of QueueNode


typedef struct _queue
{
	QueueNode *head;
	QueueNode *tail;
}Queue; // You should not change the definition of queue

///////////////////////////////////////////////////////////////////////////////////

// You should not change the prototypes of these functions
void levelOrderTraversal(BSTNode *node);

void insertBSTNode(BSTNode **node, int value);

BSTNode* dequeue(QueueNode **head, QueueNode **tail);
void enqueue(QueueNode **head, QueueNode **tail, BSTNode *node);
int isEmpty(QueueNode *head);
void removeAll(BSTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	//Initialize the Binary Search Tree as an empty Binary Search Tree
	BSTNode *root;
	root = NULL;

	printf("1: Insert an integer into the binary search tree;\n");
	printf("2: Print the level-order traversal of the binary search tree;\n");
	printf("0: Quit;\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the Binary Search Tree: ");
			scanf("%d", &i);
			insertBSTNode(&root, i);
			break;
		case 2:
			printf("The resulting level-order traversal of the binary search tree is: ");
			levelOrderTraversal(root); // You need to code this function
			printf("\n");
			break;
		case 0:
			removeAll(&root);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void levelOrderTraversal(BSTNode* root)
{
	if (root == NULL){return;}

	QueueNode *head = NULL, *tail = NULL;

	// QueueNode = enqueue();

	while (!isEmpty(head))
	{
		
		BSTNode *current = dequeue(&head, &tail);

		if (current->left != NULL)
		{
			current->item;
			current->left;
			current->right;
		}
		enqueue(&head, &tail, current);

		printf("%d ", current->item);
	}
	



    /* add your code here */
}


/* 1. (levelOrderTraversal) 이진 트리를 root 레벨부터 시작해서 "레벨 단위로" 순회하며 
	출력하는 반복(iterative) C 함수 levelOrderTraversal을 작성하십시오. 
	큐를 사용해야 하며, 큐에 정수를 추가/제거할 때는 반드시 enqueue()와 dequeue()만 
	사용해야 합니다. 큐가 비어있지 않다면, 시작하기 전에 반드시 큐를 비워야 함을 기억하세요.

	함수 프로토타입은 다음과 같습니다:
	void levelOrderIterative(BSTNode *root);

	For example, for the binary tree in Figure 1, the level order tree traversal is:
	20, 15, 50, 10, 18, 25, 80.
	(예시: Figure 1의 이진 트리에서, 레벨 순서 순회 결과는 20, 15, 50, 10, 18, 25, 80입니다.)

	힌트:
	- 큐를 이용한 BFS(너비 우선 탐색) 방식
	- root를 먼저 enqueue
	- 큐가 빌 때까지 반복: dequeue한 노드를 출력 → 그 노드의 왼쪽 자식이 있으면 enqueue, 
	  오른쪽 자식이 있으면 enqueue (왼쪽 먼저 enqueue해야 같은 레벨에서 왼→오 순서가 유지됨)
*/

///////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value){
	if (*node == NULL)
	{
		*node = malloc(sizeof(BSTNode));

		if (*node != NULL) {
			(*node)->item = value;
			(*node)->left = NULL;
			(*node)->right = NULL;
		}
	}
	else
	{
		if (value < (*node)->item)
		{
			insertBSTNode(&((*node)->left), value);
		}
		else if (value >(*node)->item)
		{
			insertBSTNode(&((*node)->right), value);
		}
		else
			return;
	}
}

//////////////////////////////////////////////////////////////////////////////////

// enqueue node
void enqueue(QueueNode **headPtr, QueueNode **tailPtr, BSTNode *node)
{
	// dynamically allocate memory
	QueueNode *newPtr = malloc(sizeof(QueueNode));

	// if newPtr does not equal NULL
	if (newPtr != NULL) {
		newPtr->data = node;
		newPtr->nextPtr = NULL;

		// if queue is empty, insert at head
		if (isEmpty(*headPtr)) {
			*headPtr = newPtr;
		}
		else { // insert at tail
			(*tailPtr)->nextPtr = newPtr;
		}

		*tailPtr = newPtr;
	}
	else {
		printf("Node not inserted");
	}
}

BSTNode* dequeue(QueueNode **headPtr, QueueNode **tailPtr)
{
	BSTNode *node = (*headPtr)->data;
	QueueNode *tempPtr = *headPtr;
	*headPtr = (*headPtr)->nextPtr;

	if (*headPtr == NULL) {
		*tailPtr = NULL;
	}

	free(tempPtr);

	return node;
}

int isEmpty(QueueNode *head)
{
	return head == NULL;
}

void removeAll(BSTNode **node)
{
	if (*node != NULL)
	{
		removeAll(&((*node)->left));
		removeAll(&((*node)->right));
		free(*node);
		*node = NULL;
	}
}

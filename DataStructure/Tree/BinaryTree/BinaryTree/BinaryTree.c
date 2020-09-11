#include "BinaryTree.h"
#include "LinkedQueue.h"

//创建二叉树
BTNode* BinaryTreeCreate(BTDataType* arr, int n, int* pi)
{
	if ('#' == arr[*pi])
	{
		++(*pi);
		return NULL;
	}
		
	BTNode* root = (BTNode*)malloc(sizeof(BTNode));
	root->data = arr[(*pi)++];

	root->left = BinaryTreeCreate(arr, n, pi);
	root->right = BinaryTreeCreate(arr, n, pi);

	return root;
}
// 二叉树销毁
void BinaryTreeDestory(BTNode* root)
{
	BTNode* node = root;
	if (!node)
		return;
	BinaryTreeDestory(node->left);
	BinaryTreeDestory(node->right);

	free(node);
	node = NULL;
}
// 二叉树节点个数
int BinaryTreeSize(BTNode* root)
{
	if (!root)
		return 0;

	return 1 + BinaryTreeSize(root->left) + BinaryTreeSize(root->right);
}
// 二叉树叶子节点个数
int BinaryTreeLeafSize(BTNode* root)
{
	if (!root)
		return 0;
	if (!root->right && !root->left)
		return 1;
	return BinaryTreeLeafSize(root->left) + BinaryTreeLeafSize(root->right);
}
// 二叉树第k层节点个数

int BinaryTreeHigh(BTNode* root)
{
	if (!root)
		return 0;
	int leftHigh = BinaryTreeHigh(root->left);
	int rightHigh = BinaryTreeHigh(root->right);

	return leftHigh < rightHigh ? rightHigh + 1 : leftHigh + 1;
}

int BinaryTreeLevelKSize(BTNode* root, int k)
{
	if (!root)
		return 0;
	if (k == 1)
		return 1;

	return BinaryTreeLevelKSize(root->left, k - 1) + BinaryTreeLevelKSize(root->right, k - 1);
}
// 二叉树查找值为x的节点
BTNode* BinaryTreeFind(BTNode* root, BTDataType x)
{
	BTNode* node;
	if (!root)
		return NULL;
	if (root->data = x)
		return root;
	
	node = BinaryTreeFind(root->left, x);
	if (node)
		return node;

	node = BinaryTreeFind(root->right, x);
	if (node)
		return node;

	return NULL;

}

// 二叉树前序遍历
void BinaryTreePrevOrder(BTNode* root)
{
	if (!root)
		return;

	printf("%c ", root->data);
	BinaryTreePrevOrder(root->left);
	BinaryTreePrevOrder(root->right);
}

// 二叉树中序遍历
void BinaryTreeInOrder(BTNode* root)
{
	if (!root)
		return;

	BinaryTreeInOrder(root->left);
	printf("%c ", root->data);
	BinaryTreeInOrder(root->right);

}

// 二叉树后序遍历
void BinaryTreePostOrder(BTNode* root)
{
	if (!root)
		return;
	BinaryTreePostOrder(root->left);
	BinaryTreePostOrder(root->right);
	printf("%c ", root->data);
}

// 层序遍历
void BinaryTreeLevelOrder(BTNode* root)
{
	Queue q;
	QueueInit(&q);
	if(root)
		QueuePush(&q, root);

	while (!QueueEmpty(&q))
	{
		BTNode* node = QueueFront(&q);
		QueuePop(&q);
		printf("%c ", node->data);


		if(node->left)
			QueuePush(&q, node->left);
		if(node->right)
			QueuePush(&q, node->right);
	}
	printf("\n");
	QueueDestroy(&q);
}

int BinaryTreeComplete(BTNode* root)
{
	Queue q;
	QueueInit(&q);
	if (root)
		QueuePush(&q, root);

	while (1)
	{
		BTNode* node = QueueFront(&q);
		if (!node)
			break;
		else
			QueuePop(&q);

		QueuePush(&q, node->left);
		QueuePush(&q, node->right);
	}

	while (!QueueEmpty(&q))
	{
		BTNode* node = QueueFront(&q);

		if (node)
		{
			QueueDestroy(&q);
			return 0;
		}
		else
			QueuePop(&q);

	}

	QueueDestroy(&q);
	return 1;
}
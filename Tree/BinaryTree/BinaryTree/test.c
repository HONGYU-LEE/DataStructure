#include "BinaryTree.h"

int main()
{
	BTNode* node = (BTNode*)malloc(sizeof(BTNode));
	char str[] = "ABD##E##CF##G##";
	
	int i = 0;
	printf("先序遍历读取的字符串为：%s\n", str);
	node = BinaryTreeCreate(str, sizeof(str) / sizeof(str[0]), &i);
	printf("先序遍历为：");
	BinaryTreePrevOrder(node);
	printf("\n");
	printf("中序遍历为：");
	BinaryTreeInOrder(node);
	printf("\n");
	printf("后序遍历为：");
	BinaryTreePostOrder(node);
	printf("\n");
	printf("层序遍历为：");
	BinaryTreeLevelOrder(node);
	printf("\n");

	printf("节点数为：%d \n", BinaryTreeSize(node));
	printf("叶子节点数为：%d \n", BinaryTreeLeafSize(node));
	printf("第k层节点数为节点数为：%d \n", BinaryTreeLevelKSize(node, 2));
	printf("二叉树高度为：%d \n", BinaryTreeHigh(node));
	//BTNode* ret = BinaryTreeFind(node, 'g');
	//printf("%c\n", ret->data);
	printf("二叉树是不是完全二叉树%d", BinaryTreeComplete(node));
	
	return 0;
}
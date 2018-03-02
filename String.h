#pragma once

#include<stdio.h>
#include<assert.h>
#include<windows.h>
#include<malloc.h>

//判断一个单词是否拼写正确
typedef char* KeyType;

typedef struct BinarySearchTreeNode
{
	struct BinarySearchTreeNode* _left;
	struct BinarySearchTreeNode* _right;
	KeyType _value;
}BSTreeNode;

BSTreeNode *BuyBSTreeNode(KeyType x);//创建节点
int BSTreeNodeInsert(BSTreeNode** tree, KeyType data);
BSTreeNode* BSTreeNodeFind(BSTreeNode* tree, KeyType data);//查找


BSTreeNode* BuyBSTreeNode(KeyType data)
{
	BSTreeNode* node = (BSTreeNode*)malloc(sizeof(BSTreeNode));
	assert(node);

	node->_value = data;
	node->_left = NULL;
	node->_right = NULL;

	return node;
}

//成功返回0，失败返回-1
int BSTreeNodeInsert(BSTreeNode** tree, KeyType data)//非递归
{
	if (*tree == NULL)
	{
		*tree = BuyBSTreeNode(data);
		return 0;
	}
	BSTreeNode* cur = *tree;
	BSTreeNode* parent = *tree;
	while (cur)
	{
		parent = cur;
		if (strcmp(parent->_value, data) > 0)//左树
		{
			cur = cur->_left;
		}
		else if (strcmp(parent->_value, data) < 0)//右树
		{
			cur = cur->_right;
		}
		else
			return -1;
	}
	//树里没有相同数据，插入，判断所插位置
	if (strcmp(parent->_value, data) > 0)//如果数据小于父亲，向父亲节点的左树链接
		parent->_left = BuyBSTreeNode(data);
	else
		parent->_right = BuyBSTreeNode(data);
	return 0;
}
BSTreeNode* BSTreeNodeFind(BSTreeNode* tree, KeyType data)
{
	assert(tree);
	while (tree)
	{
		KeyType cur = tree->_value;
		if (strcmp(cur, data) == 0)
			return tree;
		else if (strcmp(cur, data) > 0)
			tree = tree->_left;
		else
			tree = tree->_right;
	}
	return NULL;
}
void TestBSTree()
{
	BSTreeNode* tree = NULL;

	BSTreeNodeInsert(&tree, "tree");
	BSTreeNodeInsert(&tree, "list");
	BSTreeNodeInsert(&tree, "heap");
	BSTreeNodeInsert(&tree, "return");
	BSTreeNodeInsert(&tree, "student");
	
	printf("%s\n", BSTreeNodeFind(tree, "tree")->_value);
	printf("%s\n", BSTreeNodeFind(tree, "list")->_value);
	printf("%s\n", BSTreeNodeFind(tree, "heap")->_value);
	printf("%s\n", BSTreeNodeFind(tree, "return")->_value);
	printf("%s\n", BSTreeNodeFind(tree, "student")->_value);

	printf("%p\n", BSTreeNodeFind(tree, "tre e"));
	printf("%p\n", BSTreeNodeFind(tree, "lits"));
	printf("%p\n", BSTreeNodeFind(tree, "Heap"));
	printf("%p\n", BSTreeNodeFind(tree, "hehe"));
}
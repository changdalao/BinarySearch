#pragma once

#include<stdio.h>
#include<assert.h>
#include<windows.h>
#include<malloc.h>

typedef char* KeyType;
typedef char* ValueType;

typedef struct BinarySearchTreeNode
{
	struct BinarySearchTreeNode* _left;
	struct BinarySearchTreeNode* _right;
	KeyType _key;//查找
	ValueType _value;
}BSTreeNode;

BSTreeNode *BuyBSTreeNode(KeyType _key, ValueType _value);//创建节点
int BSTreeNodeInsert(BSTreeNode** tree, KeyType key, ValueType value);
BSTreeNode* BSTreeNodeFind(BSTreeNode* tree, KeyType key);//查找
int BSTreeNodeRemove(BSTreeNode** tree, KeyType key);//删除

void BSTreeInOrder(BSTreeNode* tree)//中序遍历
{
	if (NULL == tree)
		return;
	BSTreeInOrder(tree->_left);
	printf("%s->%s ", tree->_key, tree->_value);
	BSTreeInOrder(tree->_right);
}
BSTreeNode *BuyBSTreeNode(KeyType _key, ValueType _value)
{
	BSTreeNode* node = (BSTreeNode*)malloc(sizeof(BSTreeNode));
	assert(node);

	node->_value = _value;
	node->_key = _key;
	node->_left = NULL;
	node->_right = NULL;

	return node;
}
int BSTreeNodeRemove(BSTreeNode** tree, KeyType key)
{
	if ((*tree) == NULL)
		return NULL;
	BSTreeNode* cur = *tree;
	BSTreeNode* parent = *tree;
	BSTreeNode* del = NULL;
	BSTreeNode* sub = NULL;
	//1.左为空
	//2.右为空
	//3.左右不为空
	while (cur)
	{

		if (strcmp(cur->_key, key)<0)
		{
			parent = cur;
			cur = cur->_right;
		}
		else if (strcmp(cur->_key, key)>0)
		{
			parent = cur;
			cur = cur->_left;
		}
		//已经找到被删除节点cur
		else
		{
			del = cur;
			if (cur->_left == NULL)//左孩子空
			{
				if (parent->_left == cur)
					parent->_left = cur->_right;
				else if (parent->_right == cur)
					parent->_right = cur->_right;
				else if (parent == cur)//所删节点无孩子
					*tree = parent->_right;
				cur = NULL;//删除后要跳出循环
			}
			else if (cur->_right == NULL)//右孩子为空
			{
				if (parent->_right == cur)
					parent->_right = cur->_left;
				else if (parent->_left == cur)
					parent->_left = cur->_left;
				else if (parent == cur)
					*tree = parent->_left;
				cur = NULL;
			}
			else//左右孩子都不为空
			{
				sub = cur;
				del = cur->_right;
				while (del->_left)
				{
					sub = del;
					del = del->_left;
				}
				cur->_key = del->_key;
				cur->_value = del->_value;
				if (sub->_right == del)
					sub->_right = del->_right;
				else
					sub->_left = del->_right;
			}
		}
	}
	free(del);
	del = NULL;
	return 0;
}
int BSTreeNodeInsert(BSTreeNode** tree, KeyType key, ValueType value)//非递归
{
	if (*tree == NULL)
	{
		*tree = BuyBSTreeNode(key, value);
		return 0;
	}
	BSTreeNode* cur = *tree;
	BSTreeNode* parent = *tree;
	while (cur)
	{
		parent = cur;
		if (strcmp(parent->_key, key) > 0)//左树
		{
			cur = cur->_left;
		}
		else if (strcmp(parent->_key, key) < 0)//右树
		{
			cur = cur->_right;
		}
		else
			return -1;
	}
	//树里没有相同数据，插入，判断所插位置
	if (strcmp(parent->_key, key) > 0)//如果数据小于父亲，向父亲节点的左树链接
		parent->_left = BuyBSTreeNode(key, value);
	else
		parent->_right = BuyBSTreeNode(key, value);
	return 0;
}
BSTreeNode* BSTreeNodeFind(BSTreeNode* tree, KeyType key)
{
	assert(tree);
	while (tree)
	{
		KeyType cur = tree->_key;
		if (strcmp(cur, key) == 0)
			return tree;
		else if (strcmp(cur, key) > 0)
			tree = tree->_left;
		else
			tree = tree->_right;
	}
	return NULL;
}
void TestBSTree()
{
	BSTreeNode* tree = NULL;
	BSTreeNodeInsert(&tree, "man", "男人");
	BSTreeNodeInsert(&tree, "list", "链表");
	BSTreeNodeInsert(&tree, "heap", "堆");
	BSTreeNodeInsert(&tree, "return", "返回");
	BSTreeNodeInsert(&tree, "student", "学生");
	BSTreeInOrder(tree);
	printf("\n");
	printf("list->%s\n", BSTreeNodeFind(tree, "list")->_value);
	printf("heap->%s\n", BSTreeNodeFind(tree, "heap")->_value);
	printf("return->%s\n", BSTreeNodeFind(tree, "return")->_value);
	printf("student->%s\n", BSTreeNodeFind(tree, "student")->_value);
	BSTreeNodeRemove(&tree, "man");
	BSTreeNodeRemove(&tree, "heap");

	BSTreeNodeRemove(&tree, "list");
	BSTreeNodeRemove(&tree, "return");
	BSTreeNodeRemove(&tree, "stuednt");

	BSTreeInOrder(tree);
	printf("\n");
}
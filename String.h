#pragma once

#include<stdio.h>
#include<assert.h>
#include<windows.h>
#include<malloc.h>

//�ж�һ�������Ƿ�ƴд��ȷ
typedef char* KeyType;

typedef struct BinarySearchTreeNode
{
	struct BinarySearchTreeNode* _left;
	struct BinarySearchTreeNode* _right;
	KeyType _value;
}BSTreeNode;

BSTreeNode *BuyBSTreeNode(KeyType x);//�����ڵ�
int BSTreeNodeInsert(BSTreeNode** tree, KeyType data);
BSTreeNode* BSTreeNodeFind(BSTreeNode* tree, KeyType data);//����


BSTreeNode* BuyBSTreeNode(KeyType data)
{
	BSTreeNode* node = (BSTreeNode*)malloc(sizeof(BSTreeNode));
	assert(node);

	node->_value = data;
	node->_left = NULL;
	node->_right = NULL;

	return node;
}

//�ɹ�����0��ʧ�ܷ���-1
int BSTreeNodeInsert(BSTreeNode** tree, KeyType data)//�ǵݹ�
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
		if (strcmp(parent->_value, data) > 0)//����
		{
			cur = cur->_left;
		}
		else if (strcmp(parent->_value, data) < 0)//����
		{
			cur = cur->_right;
		}
		else
			return -1;
	}
	//����û����ͬ���ݣ����룬�ж�����λ��
	if (strcmp(parent->_value, data) > 0)//�������С�ڸ��ף����׽ڵ����������
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
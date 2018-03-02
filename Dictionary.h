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
	KeyType _key;//����
	ValueType _value;
}BSTreeNode;

BSTreeNode *BuyBSTreeNode(KeyType _key, ValueType _value);//�����ڵ�
int BSTreeNodeInsert(BSTreeNode** tree, KeyType key, ValueType value);
BSTreeNode* BSTreeNodeFind(BSTreeNode* tree, KeyType key);//����
int BSTreeNodeRemove(BSTreeNode** tree, KeyType key);//ɾ��

void BSTreeInOrder(BSTreeNode* tree)//�������
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
	//1.��Ϊ��
	//2.��Ϊ��
	//3.���Ҳ�Ϊ��
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
		//�Ѿ��ҵ���ɾ���ڵ�cur
		else
		{
			del = cur;
			if (cur->_left == NULL)//���ӿ�
			{
				if (parent->_left == cur)
					parent->_left = cur->_right;
				else if (parent->_right == cur)
					parent->_right = cur->_right;
				else if (parent == cur)//��ɾ�ڵ��޺���
					*tree = parent->_right;
				cur = NULL;//ɾ����Ҫ����ѭ��
			}
			else if (cur->_right == NULL)//�Һ���Ϊ��
			{
				if (parent->_right == cur)
					parent->_right = cur->_left;
				else if (parent->_left == cur)
					parent->_left = cur->_left;
				else if (parent == cur)
					*tree = parent->_left;
				cur = NULL;
			}
			else//���Һ��Ӷ���Ϊ��
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
int BSTreeNodeInsert(BSTreeNode** tree, KeyType key, ValueType value)//�ǵݹ�
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
		if (strcmp(parent->_key, key) > 0)//����
		{
			cur = cur->_left;
		}
		else if (strcmp(parent->_key, key) < 0)//����
		{
			cur = cur->_right;
		}
		else
			return -1;
	}
	//����û����ͬ���ݣ����룬�ж�����λ��
	if (strcmp(parent->_key, key) > 0)//�������С�ڸ��ף����׽ڵ����������
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
	BSTreeNodeInsert(&tree, "man", "����");
	BSTreeNodeInsert(&tree, "list", "����");
	BSTreeNodeInsert(&tree, "heap", "��");
	BSTreeNodeInsert(&tree, "return", "����");
	BSTreeNodeInsert(&tree, "student", "ѧ��");
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
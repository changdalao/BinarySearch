#include"BinarySearchTree.h"

void BSTreeInOrder(BSTreeNode* tree)//�������
{
	if (NULL == tree)
		return;
	BSTreeInOrder(tree->_left);
	printf("%d ", tree->data);
	BSTreeInOrder(tree->_right);
}
void BTreePrevOrder(BSTreeNode* tree)//ǰ�����
{
	if (NULL == tree)
		return;
	printf("%d ", tree->data);
	BTreePrevOrder(tree->_left);
	BTreePrevOrder(tree->_right);
}
BSTreeNode* BuyBSTreeNode(DataType data)
{
	BSTreeNode* node = (BSTreeNode*)malloc(sizeof(BSTreeNode));
	assert(node);

	node->data = data;
	node->_left = NULL;
	node->_right = NULL;

	return node;
}

//�ɹ�����0��ʧ�ܷ���-1
int BSTreeNodeInsertR(BSTreeNode** tree, DataType data)//�ݹ�
{
	if (*tree == NULL)
	{
		*tree = BuyBSTreeNode(data);
		return 0;
	}
	if ((*tree)->data > data)
		return BSTreeNodeInsertR(&(*tree)->_left, data);
	else if ((*tree)->data < data)
		return BSTreeNodeInsertR(&(*tree)->_right, data);
	else
		return -1;
}
int BSTreeNodeInsert(BSTreeNode** tree, DataType data)//�ǵݹ�
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
		if (parent->data > data)//����
		{
			cur = cur->_left;
		}
		else if (parent->data < data)//����
		{
			cur = cur->_right;
		}
		else
			return -1;
	}
	//����û����ͬ���ݣ����룬�ж�����λ��
	if (parent->data > data)//�������С�ڸ��ף����׽ڵ����������
		parent->_left = BuyBSTreeNode(data);
	else
		parent->_right = BuyBSTreeNode(data);
	return 0;
}
const BSTreeNode* BSTreeNodeFind(BSTreeNode* tree, DataType data)
{
	assert(tree);
	while (tree)
	{
		if (tree->data == data)
			return tree;
		else if (tree->data > data)
			tree = tree->_left;
		else
			tree = tree->_right;
	}
	return NULL;
}
int BSTreeRemove(BSTreeNode** tree, DataType data)
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
		
		if (cur->data < data)
		{
			parent = cur;
			cur = cur->_right;
		}
		else if (cur->data > data)
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
				cur->data = del->data;
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
int BSTreeRemoveR(BSTreeNode** tree, DataType data)
{
	if (NULL == *tree)
		return -1;
	if ((*tree)->data > data)
		return BSTreeRemoveR(&(*tree)->_left, data);
	else if ((*tree)->data < data)
		return BSTreeRemoveR(&(*tree)->_right, data);
	else//�ҵ�ɾ���Ľڵ�
	{
		BSTreeNode* del = *tree;
		if ((*tree)->_left == NULL)//���
			*tree = (*tree)->_right;
		else if ((*tree)->_right == NULL)//�ҿ�
			*tree = (*tree)->_left;
		else//���Ҷ���Ϊ��
		{
			BSTreeNode* sub = (*tree);
			del = (*tree)->_right;
			while (del->_left)
			{
				sub = del;
				del = del->_left;
			}
			(*tree)->data = del->data;
			if (sub->_right == del)
				sub->_right = del->_right;
			else
				sub->_left = del->_right;
		}
		free(del);
		del = NULL;
	}
	return 0;
}

void TestBSTree()
{
	BSTreeNode* tree = NULL;

	BSTreeNodeInsert(&tree, 5);
	BSTreeNodeInsert(&tree, 1);
	BSTreeNodeInsert(&tree, 2);
	BSTreeNodeInsert(&tree, 3);
	BSTreeNodeInsert(&tree, 4);
	BSTreeNodeInsert(&tree, 6);
	BSTreeNodeInsert(&tree, 0);
	BSTreeNodeInsert(&tree, 7);
	BSTreeNodeInsert(&tree, 8);
	BSTreeNodeInsert(&tree, 9);

	BSTreeInOrder(tree);
	printf("\n");

	const BSTreeNode* cur = BSTreeNodeFind(tree, 7);
	printf("����7��%d\n",cur->data );

	BSTreeRemove(&tree, 4);
	BSTreeRemove(&tree, 8);
	BSTreeRemove(&tree, 3);
	BSTreeRemove(&tree, 7);
	BSTreeRemove(&tree, 5);
	BSTreeInOrder(tree);
	printf("\n");

	BSTreeRemove(&tree, 0);
	BSTreeRemove(&tree, 1);
	BSTreeRemove(&tree, 2);
	BSTreeRemove(&tree, 3);
	BSTreeRemove(&tree, 4);
	BSTreeRemove(&tree, 5);
	BSTreeRemove(&tree, 6);
	BSTreeRemove(&tree, 7);
	BSTreeRemove(&tree, 8);
	BSTreeRemove(&tree, 9);
	BSTreeInOrder(tree);
	printf("\n");

}
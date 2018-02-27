#include"BinarySearchTree.h"

void BSTreeInOrder(BSTreeNode* tree)//中序遍历
{
	if (NULL == tree)
		return;
	BSTreeInOrder(tree->_left);
	printf("%d ", tree->data);
	BSTreeInOrder(tree->_right);
}
void BTreePrevOrder(BSTreeNode* tree)//前序遍历
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

//成功返回0，失败返回-1
int BSTreeNodeInsertR(BSTreeNode** tree, DataType data)//递归
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
int BSTreeNodeInsert(BSTreeNode** tree, DataType data)//非递归
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
		if (parent->data > data)//左树
		{
			cur = cur->_left;
		}
		else if (parent->data < data)//右树
		{
			cur = cur->_right;
		}
		else
			return -1;
	}
	//树里没有相同数据，插入，判断所插位置
	if (parent->data > data)//如果数据小于父亲，向父亲节点的左树链接
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
	//1.左为空
	//2.右为空
	//3.左右不为空
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
	else//找到删除的节点
	{
		BSTreeNode* del = *tree;
		if ((*tree)->_left == NULL)//左空
			*tree = (*tree)->_right;
		else if ((*tree)->_right == NULL)//右空
			*tree = (*tree)->_left;
		else//左右都不为空
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
	printf("查找7？%d\n",cur->data );

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
#include<stdio.h>
#include<assert.h>
#include<windows.h>
#include<malloc.h>


typedef int DataType;

typedef struct BinarySearchTreeNode
{
	struct BinarySearchTreeNode* _left;
	struct BinarySearchTreeNode* _right;
	DataType data;
}BSTreeNode;

BSTreeNode *BuyBSTreeNode(DataType x);//�����ڵ�
int BSTreeNodeInsert(BSTreeNode** tree, DataType data);
int BSTreeNodeInsertR(BSTreeNode** tree, DataType data);//�ݹ����
const BSTreeNode* BSTreeNodeFind(BSTreeNode* tree, DataType data);//����
int BSTreeRemove(BSTreeNode** tree, DataType data);
int BSTreeRemoveR(BSTreeNode** tree, DataType data);//�ݹ�ɾ��
void BSTreeInOrder(BSTreeNode* tree);//�������


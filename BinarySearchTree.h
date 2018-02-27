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

BSTreeNode *BuyBSTreeNode(DataType x);//创建节点
int BSTreeNodeInsert(BSTreeNode** tree, DataType data);
int BSTreeNodeInsertR(BSTreeNode** tree, DataType data);//递归插入
const BSTreeNode* BSTreeNodeFind(BSTreeNode* tree, DataType data);//查找
int BSTreeRemove(BSTreeNode** tree, DataType data);
int BSTreeRemoveR(BSTreeNode** tree, DataType data);//递归删除
void BSTreeInOrder(BSTreeNode* tree);//中序遍历


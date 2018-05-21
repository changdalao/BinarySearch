#include<iostream>
#include<string>
using namespace std;

template<class T>
struct BinTreeNode {
	BinTreeNode<T>* _left;
	BinTreeNode<T>* _right;
	T _data;
	BinTreeNode(const T& data = T())
		:_data(data)
		, _left(NULL)
		, _right(NULL)
	{}
};

template<class T>
class BinTree {
	typedef struct BinTreeNode<T> Node;
public:
	BinTree()
		:root(new Node(T()))
	{}
	virtual ~BinTree()
	{
		delete root;
	}
	void Insert(const T& data)
	{
		if (root->_data ==T())//判断是否为空
		{
			root = new Node(data);
			return;
		}
		Node* cur = root;
		Node* parent = root;
		while (cur)
		{
			parent = cur;
			if (data > cur->_data)
				cur = cur->_right;
			else if (data < cur->_data)
				cur = cur->_left;
			else
				return;
		}
		if (parent->_data > data)
			parent->_left = new Node(data);
		else
			parent->_right = new Node(data);
	}
	const T& Find(const T& data) const
	{
		if (root->_data == T())
			return T();
		else
		{
			Node* cur = root;
			while (cur)
			{
				if (cur->_data > data)
					cur = cur->_left;
				else if (cur->_data < data)
					cur = cur->_right;
				else
					return data;
			}
			return T();
		}
	}
private:
	Node* root;
};
void Test()
{
	BinTree<string> node;
	node.Insert("5");
	node.Insert("3");
	node.Insert("4");
	node.Insert("6");
	cout << node.Find("3") << endl;
  /////////////////////////////////////////////////
  BinTree<int> node1;
	node1.Insert(5);
	node1.Insert(6);
	node1.Insert(4);
	node1.Insert(1);
	cout << node1.Find(5) << endl;
}

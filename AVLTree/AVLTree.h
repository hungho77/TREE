#pragma once
#include<iostream>
#include<stack>
using namespace std;

struct AVLNode
{
	int data;
	int bal;
	AVLNode *pLeft;
	AVLNode *pRight;
	AVLNode(int data)
	{
		this->pLeft = this->pRight = NULL;
		this->data = data;
		this->bal = 0;
	}
};
class AVLTree
{
	AVLNode *m_root;
	bool insert_recursive_data(AVLNode *&root, int data);
	/*bool delete_data(AVLNode *&root, int data);*/
	bool delNode(AVLNode *&T, int data);
	bool searchStandFor(AVLNode *&p, AVLNode *&q);
	AVLNode *getSuccessor(AVLNode *x);
	void leftRotate(AVLNode *&p);
	void rightRotate(AVLNode*& p);
	void leftBalance(AVLNode *&p);
	void rightBalance(AVLNode*& p);
public:
	AVLTree();
	AVLNode *Search_recursive(int data);
	AVLNode *Search_nonrecursive(int data);
	bool insert_nonrecursive(int data);
	bool insert_recursive(int data);
	bool remove(int data);
	~AVLTree();
};


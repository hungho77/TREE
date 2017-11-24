#pragma once
#include<iostream>
using namespace std;

enum color_t { RED, BLACK };

struct RBNode
{
	int key;
	color_t color;
	RBNode *pLeft;
	RBNode *pRight;
	RBNode *pParent;
	RBNode();
	RBNode(int key);
};
class RBTree
{
	RBNode *root;
	void left_rotate(RBTree & T, RBNode * x);
	void right_rotate(RBTree & T, RBNode * x);
	void RB_insert(RBTree & T, RBNode * z);
	void RB_insert_fixup(RBTree & T, RBNode * z);
	void RB_Transplant(RBTree & T, RBNode *u, RBNode *v);
	void RB_remove(RBTree & T, RBNode *z);
	void RB_remove_fixup(RBTree & T, RBNode *x);
	RBNode *RB_search(RBNode *ROOT, int key);
	void printLNR(RBNode *x);
	void RB_removeAll(RBNode *x);
public:
	static RBNode *NIL;
	RBTree();
	void insert(int key);
	void remove(int key);
	void removeAll();
	RBNode *sucessor(RBNode *x);
	RBNode* search(int key);
	void print();
	~RBTree();
};


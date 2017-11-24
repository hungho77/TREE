#include "RBTree.h"

RBNode::RBNode()
{
	this->color = BLACK;
	this->key = 0;
	this->pLeft = this->pRight = this->pParent = NULL;
}
RBNode::RBNode(int key)
{
	this->color = RED;
	this->key = key;
	this->pLeft = this->pRight = this->pParent = RBTree::NIL;
}

RBNode * RBTree::RB_search(RBNode *ROOT, int key)
{
	RBNode *p = ROOT;
	if (p == NIL)
		return NIL;
	if (p->key == key)
		return p;
	if (p->key > key)
		RB_search(p->pLeft, key);
	else
		RB_search(p->pRight, key);
}

void RBTree::printLNR(RBNode * x)
{
	if (x != RBTree::NIL)
	{
		printLNR(x->pLeft);
		cout << x->key << " ";
		printLNR(x->pRight);
	}
}

void RBTree::RB_removeAll(RBNode * x)
{
	if (x != NIL)
	{
		RB_removeAll(x->pLeft);
		RB_removeAll(x->pRight);
		delete x;
	}
}


RBNode* RBTree::search(int key)
{
	return RB_search(this->root, key);
}

void RBTree::print()
{
	printLNR(this->root);
}

void RBTree::left_rotate(RBTree & T, RBNode * x)
{
	RBNode *y = x->pRight;
	x->pRight = y->pLeft;
	if (y->pLeft != NIL)
		y->pLeft->pParent = x;
	y->pParent = x->pParent;
	if (x->pParent == NIL)
		T.root = y;
	else if (x == x->pParent->pLeft)
		x->pParent->pLeft = y;
	else
		x->pParent->pRight = y;
	x->pParent = y;
	y->pLeft = x;
}

void RBTree::right_rotate(RBTree & T, RBNode * x)
{
	RBNode *y = x->pLeft;
	x->pLeft = y->pRight;
	if (y->pRight != NIL)
		y->pRight->pParent = x;
	y->pParent = x->pParent;
	if (x->pParent == NIL)
		T.root = y;
	else if (x == x->pParent->pLeft)
		x->pParent->pLeft = y;
	else
		x->pParent->pRight = y;
	x->pParent = y;
	y->pRight = x;
}

void RBTree::RB_insert(RBTree & T, RBNode * z)
{
	RBNode *y = T.NIL;
	RBNode *x = T.root;
	while (x != T.NIL)
	{
		y = x;
		if (z->key == x->key)
			return;
		if (z->key < x->key)
			x = x->pLeft;
		else
			x = x->pRight;
	}
	z->pParent = y;
	if (y == T.NIL)
		T.root = z;
	else if (z->key < y->key)
		y->pLeft = z;
	else
		y->pRight = z;
	RB_insert_fixup(T, z);
}

void RBTree::RB_insert_fixup(RBTree & T, RBNode * z)
{
	while (z->pParent->color == RED)
	{
		if (z->pParent == z->pParent->pParent->pLeft)
		{
			RBNode *y = z->pParent->pParent->pRight;
			if (y->color == RED)
			{
				z->pParent->color = BLACK;
				y->color = BLACK;
				z->pParent->pParent->color = RED;
				z = z->pParent->pParent;
			}
			else
			{
				if (z == z->pParent->pRight)
				{
					z = z->pParent;
					left_rotate(T, z);
				}
				z->pParent->color = BLACK;
				z->pParent->pParent->color = RED;
				right_rotate(T, z->pParent->pParent);

			}
		}
		else
		{
			RBNode *y = z->pParent->pParent->pLeft;
			if (y->color == RED)
			{
				z->pParent->color = BLACK;
				y->color = BLACK;
				z->pParent->pParent->color = RED;
				z = z->pParent->pParent;
			}
			else
			{
				if (z == z->pParent->pLeft)
				{
					z = z->pParent;
					right_rotate(T, z);
				}
				z->pParent->color = BLACK;
				z->pParent->pParent->color = RED;
				left_rotate(T, z->pParent->pParent);
			}
		}
	}
	T.root->color = BLACK;
}

void RBTree::RB_Transplant(RBTree & T, RBNode * u, RBNode * v)
{
	if (u->pParent == NIL)
		T.root = v;
	else if (u == u->pParent->pLeft)
		u->pParent->pLeft = v;
	else
		u->pParent->pRight = v;
	v->pParent = u->pParent;
}

void RBTree::RB_remove(RBTree & T, RBNode * z)
{
	RBNode *y = z;
	RBNode *x = NIL;
	color_t y_original_color = y->color;
	if (z->pLeft == NIL)
	{
		x = z->pRight;
		RB_Transplant(T, z, z->pRight);
	}
	else if (z->pRight == NIL)
	{
		x = z->pLeft;
		RB_Transplant(T, z, z->pLeft);
	}
	else
	{
		y = sucessor(z);
		y_original_color = y->color;
		x = y->pRight;
		if (y->pParent == z)
			x->pParent = z;
		else
		{
			RB_Transplant(T, y, y->pRight);
			y->pRight = z->pRight;
			y->pRight->pParent = y;
		}
		RB_Transplant(T, z, y);
		y->pLeft = z->pLeft;
		y->pLeft->pParent = z;
		y->color = z->color;
		delete z;
	}
	if (y_original_color == BLACK)
		RB_remove_fixup(T, x);
}

void RBTree::RB_remove_fixup(RBTree & T, RBNode * x)
{
	while (x != T.root && x->color == BLACK)
	{
		if (x == x->pParent->pLeft)
		{
			RBNode *w = x->pParent->pRight;
			if (w->color == RED)
			{
				w->color = BLACK;
				x->pParent->color = RED;
				left_rotate(T, x->pParent);
				w = x->pParent->pRight;
			}
			if (w->pLeft->color == BLACK && w->pRight->color)
			{
				w->color = RED;
				x = x->pParent;
			}
			else
			{
				if (w->pRight->color == BLACK)
				{
					w->pLeft->color = BLACK;
					w->color = RED;
					right_rotate(T, w);
					w = w->pParent->pRight;
				}
				w->color = x->pParent->color;
				x->pParent->color = BLACK;
				w->pRight->color = BLACK;
				left_rotate(T, x->pParent);
				x = T.root;
			}
		}
		else
		{
			RBNode *w = x->pParent->pLeft;
			if (w->color == RED)
			{
				w->color = BLACK;
				x->pParent->color = RED;
				right_rotate(T, x->pParent);
				w = x->pParent->pLeft;
			}
			if (w->pRight->color == BLACK && w->pLeft->color)
			{
				w->color = RED;
				x = x->pParent;
			}
			else
			{
				if (w->pLeft->color == BLACK)
				{
					w->pRight->color = BLACK;
					w->color = RED;
					right_rotate(T, w);
					w = w->pParent->pLeft;
				}
				w->color = x->pParent->color;
				x->pParent->color = BLACK;
				w->pLeft->color = BLACK;
				left_rotate(T, x->pParent);
				x = T.root;
			}
		}
	}
	x->color = BLACK;
}

RBTree::RBTree()
{
	this->root = NIL;
}

void RBTree::insert(int key)
{
	RBNode * z = new RBNode(key);
	RB_insert(*this, z);
}

void RBTree::remove(int key)
{
	RB_remove(*this, this->search(key));
}

void RBTree::removeAll()
{
	RB_removeAll(this->root);
}

RBNode * RBTree::sucessor(RBNode * x)
{
	if (x->pRight != NIL)
	{
		RBNode *y = x->pRight;
		while (y->pLeft != NIL)
			y = y->pLeft;
		return y;
	}
	RBNode *y = x->pParent;
	while (y != NIL && x == y->pRight)
	{
		x = y;
		y = y->pParent;
	}
	return y;
}


RBTree::~RBTree()
{
}

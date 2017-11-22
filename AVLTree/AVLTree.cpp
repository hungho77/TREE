#include "AVLTree.h"



AVLTree::AVLTree()
{
	this->m_root = NULL;
}

AVLNode * AVLTree::Search_recursive(int data)
{
	if (this->m_root == NULL)
		return NULL;
	if (this->m_root->data = data)
		return this->m_root;
	if (data < this->m_root->data)
	{
		this->m_root = this->m_root->pLeft;
		this->Search_recursive(data);
	}
	else
	{
		this->m_root = this->m_root->pRight;
		this->Search_recursive(data);
	}
}

AVLNode * AVLTree::Search_nonrecursive(int data)
{
	if (this->m_root == NULL)
		return NULL;
	AVLNode *p = this->m_root;
	while (p)
	{
		if (p->data == data)
			return p;
		if (p->data > data)
			p = p->pLeft;
		else
			p = p->pRight;
	}
	return NULL;
}

void AVLTree::leftRotate(AVLNode *&p)
{
	AVLNode *q;
	q = p->pRight;
	p->pRight = q->pLeft;
	q->pLeft = p;
	p = q;
}

void AVLTree::rightRotate(AVLNode*& p)
{
	AVLNode *q;
	q = p->pLeft;
	p->pLeft = q->pRight;
	q->pRight = p;
	p = q;
}

void AVLTree::leftBalance(AVLNode *&p)
{
	switch (p->pLeft->bal)
	{
	case -1:
	{
		this->rightRotate(p);
		p->pRight->bal = 0;
		p->bal = 0;
		break;
	}
	case 1:
	{
		this->leftRotate(p->pLeft);
		this->rightRotate(p);
		switch (p->bal)
		{
		case 0:
		{
			p->pLeft->bal = 0;
			p->pRight->bal = 0;
			break;
		}
		case -1:
		{
			p->pLeft->bal = 0;
			p->pRight->bal = 1;
			break;
		}
		case 1:
		{
			p->pLeft->bal = -1;
			p->pRight->bal = 0;
		}

		}
		p->bal = 0;
		break;
	}
	}
}

void AVLTree::rightBalance(AVLNode*& p)
{
	switch (p->pRight->bal)
	{
	case 1:
	{
		this->leftRotate(p);
		p->pLeft->bal = 0;
		p->bal = 0;
		break;
	}
	case -1:
	{
		this->rightRotate(p->pRight);
		this->leftRotate(p);
		switch (p->bal)
		{
		case 0:
		{
			p->pRight->bal = 0;
			p->pLeft->bal = 0;
			break;
		}
		case -1:
		{
			p->pLeft->bal = 0;
			p->pRight->bal = 1;
			break;
		}
		case 1:
		{
			p->pRight->bal = 0;
			p->pLeft->bal = -1;
		}
		}
		p->bal = 0;
		break;
	}
	}
}

bool AVLTree::insert_nonrecursive(int data)
{
	if (m_root == NULL)
	{
		m_root = new AVLNode(data);
		m_root->data = data;
		return true;
	}
	stack<AVLNode*> a;
	while (m_root)
	{
		if (m_root->data == data)
			return false;
		if (m_root->data > data)
		{
			if (m_root->pLeft == NULL)
			{
				a.push(m_root);
				m_root->pLeft = new AVLNode(data);
				break;
			}
			a.push(m_root);
			m_root = m_root->pLeft;
		}
		else
		{
			if (m_root->pRight == NULL)
			{

				a.push(m_root);
				m_root->pRight = new AVLNode(data);
				break;
			}
			a.push(m_root);
			m_root = m_root->pRight;
		}
	}
	int check = 0;
	int i = 0;
	while (!a.empty())
	{
		AVLNode *p = m_root;
		m_root = a.top();
		a.pop();
		/////////////////////////////////////
		if (check == -2)
		{
			m_root->pLeft = p;
		}
		else if (check == 2)
		{
			m_root->pRight = p;
		}
		////////////////////////////////
		if (check)
			continue;
		if (m_root->data > data)
		{
			switch (m_root->bal)
			{
			case 0:
			{
				m_root->bal = -1;
				check = 0;
				break;
			}
			case -1:
			{
				leftBalance(m_root);
				check = -2;
				break;
			}
			case 1:
			{
				m_root->bal = 0;
				check = 1;
				break;
			}
			}
		}
		else
		{
			switch (m_root->bal)
			{
			case 0:
			{
				m_root->bal = 1;
				check = 0;
				break;
			}
			case 1:
			{
				rightBalance(m_root);
				check = 2;
				break;
			}
			case -1:
			{
				m_root->bal = 0;
				check = 1;
				break;
			}
			}
		}
	}
	//end while
	return true;

}

bool AVLTree::insert_recursive(int data)
{
	return insert_recursive_data(this->m_root, data);
}

bool AVLTree::remove(int data)
{
	return delNode(this->m_root, data);
}

bool AVLTree::insert_recursive_data(AVLNode *&root, int data)
{
	bool needsUpdate;
	if (root == NULL)
	{
		root = new AVLNode(data);
		if (root == NULL)
			return false;
		else
			return true;
	}
	else
	{
		if (root->data == data)
			return false;
		else if (root->data > data)
		{
			needsUpdate = insert_recursive_data(root->pLeft, data);
			if (!needsUpdate)
				return needsUpdate;
			switch (root->bal)
			{
			case 0:
			{
				root->bal = -1;
				return true;
			}
			case -1:
			{
				leftBalance(root);
				return false;
			}
			case 1:
			{
				root->bal = 0;
				return false;
			}
			}
		}
		else
		{
			needsUpdate = insert_recursive_data(root->pRight, data);
			if (!needsUpdate)
				return needsUpdate;
			switch (root->bal)
			{
			case 0:
			{
				root->bal = 1;
				return true;
			}
			case 1:
			{
				rightBalance(root);
				return false;
			}
			case -1:
			{
				root->bal = 0;
				return false;
			}
			}
		}
	}
}

//bool AVLTree::delete_data(AVLNode *& root, int data)
//{
//	bool needsUpdate;
//	if (root == NULL)
//		return false;
//	else
//	{
//		if (data == root->data)
//		{
//			//If the node has two children, replace it with it's successor.
//			if (root->pRight != NULL && root->pLeft != NULL)
//			{
//				AVLNode *successor = getSuccessor(root);
//				/*needsUpdate = checkForUpdates(root, successor->data);*/
//				if (successor->pParent != root)
//				{
//					if (successor->pRight != NULL)
//					{
//						(successor->pRight)->pParent = successor->pParent;
//						(successor->pParent)->pLeft = successor->pRight;
//					}
//					else
//						(successor->pParent)->pLeft = NULL;
//					successor->pRight = root->pRight;
//					(root->pRight)->pParent = successor;
//				}
//				successor->pLeft = root->pLeft;
//
//				(root->pLeft)->pParent = successor;
//				if (root == this->m_root) {
//					successor->pParent = NULL;
//					root = successor;
//				}
//				else if ((root->pParent)->pLeft == root) {
//					successor->pParent = root->pParent;
//					(root->pParent)->pLeft = successor;
//				}
//				else {
//					successor->pParent = root->pParent;
//					(root->pParent)->pRight = successor;
//				}
//				free(root);
//				/*if (successor->leftHeight - successor->rightHeight > 1) {
//					successor = balance(successor);
//					if (successor->parent != NULL && (successor->parent)->left == successor) {
//						if (successor->leftHeight > successor->rightHeight) return (successor->leftHeight != (successor->parent)->leftHeight - 1);
//						else return (successor->rightHeight != (successor->parent)->leftHeight - 1);
//					}
//					if (successor->parent != NULL && (successor->parent)->right == successor) {
//						if (successor->leftHeight > successor->rightHeight) return (successor->rightHeight != (successor->parent)->rightHeight - 1);
//						else return (successor->rightHeight != (successor->parent)->rightHeight - 1);
//					}
//				}
//				return (needsUpdate && successor->rightHeight + 1 > successor->leftHeight);*/
//				if (successor->bal == -1)
//				{
//					leftBalance(successor);
//					return false;
//				}
//				else
//					return true;
//			}
//			//If data has one child, it's child can replace it in the tree.
//			else if (root->pRight == NULL && root->pLeft != NULL) {
//				if (root->pParent != NULL) {
//					if ((root->pParent)->pRight == root) {
//						(root->pParent)->pRight = root->pLeft;
//						(root->pLeft)->pParent = root->pParent;
//					}
//					else {
//						(root->pParent)->pLeft = root->pLeft;
//						(root->pLeft)->pParent = root->pParent;
//					}
//					free(root);
//					return true;
//				}
//				else {
//					this->m_root = root->pLeft;
//					(root->pLeft)->pParent = NULL;
//					free(root);
//					return true;
//				}
//			}
//			else if (root->pRight != NULL && root->pLeft == NULL) {
//				if (root->pParent != NULL) {
//					if ((root->pParent)->pRight == root) {
//						(root->pParent)->pRight = root->pRight;
//						(root->pRight)->pParent = root->pParent;
//					}
//					else {
//						(root->pParent)->pLeft = root->pRight;
//						(root->pRight)->pParent = root->pParent;
//					}
//					free(root);
//					return true;
//				}
//				else {
//					this->m_root = root->pRight;
//					(root->pRight)->pParent = NULL;
//					free(root);
//					return true;
//				}
//			}
//			//If data has no children, it is a leaf and should simply be deleted.
//			else {
//				if (root->pParent == NULL)
//					this->m_root = NULL;
//				else if ((root->pParent)->pRight == root) {
//					(root->pParent)->pRight = NULL;
//					free(root);
//					return true;
//				}
//				else {
//					(root->pParent)->pLeft = NULL;
//					free(root);
//					return true;
//				}
//			}
//		}
//		else if (data < root->data)
//		{
//			needsUpdate = delete_data(root->pLeft, data);
//			if (!needsUpdate)
//				return needsUpdate;
//			switch (root->bal)
//			{
//			case 0:
//			{
//				root->bal = -1;
//				return true;
//			}
//			case 1:
//			{
//				rightBalance(root);
//				return false;
//			}
//			case -1:
//			{
//				root->bal = 0;
//				return false;
//			}
//			}
//		}
//		else
//		{
//			needsUpdate = delete_data(root->pRight, data);
//			if (!needsUpdate)
//				return needsUpdate;
//			switch (root->bal)
//			{
//			case 0:
//			{
//				root->bal = -1;
//				return true;
//			}
//			case 1:
//			{
//				rightBalance(root);
//				return false;
//			}
//			case -1:
//			{
//				root->bal = 0;
//				return false;
//			}
//			}
//		}
//	}
//}

AVLNode * AVLTree::getSuccessor(AVLNode * data)
{
	data = data->pRight;
	while (data->pLeft != NULL)
	{
		data = data->pLeft;
	}
	return data;
}

bool AVLTree::delNode(AVLNode *&T, int data)
{
	bool needsUpdate;
	if (T == NULL) 
		return false;
	if (T->data > data)
	{
		needsUpdate = delNode(T->pLeft, data);
		if (!needsUpdate) 
			return needsUpdate;
		switch (T->bal)
		{
		case -1:
			T->bal = 0;
			return true;
		case 0:
			T->bal = 1;
			return false;
		case 1:
			rightBalance(T);
			return false;
		}
	}
	if (T->data < data)
	{
		needsUpdate = delNode(T->pRight, data);
		if (!needsUpdate)
			return needsUpdate;
		switch (T->bal)
		{
		case 1:
			T->bal = 0;
			return true;
		case 0:
			T->bal = -1;
			return false;
		case -1:
			leftBalance(T);
			return false;
		}
	}
	else  //T->data == data
	{
		AVLNode* p = T;
		if (T->pLeft == NULL)
		{
			T = T->pRight; 
			needsUpdate = true;
		}
		else if (T->pRight == NULL)
		{
			T = T->pLeft; 
			needsUpdate = true;
		}
		else //T có cả 2 con
		{
			needsUpdate = searchStandFor(p, T->pRight);
			if (!needsUpdate) 
				return needsUpdate;
			switch (T->bal)
			{
			case 1:
				T->bal = 0;
				return true;
			case 0:
				T->bal = -1;
				return false;
			case -1:
				leftBalance(T);
				return false;
			}
		}
		delete p;
		return needsUpdate;
	}
}
bool AVLTree::searchStandFor(AVLNode *&p, AVLNode *&q)
{
	int needsUpdate;
	if (q->pLeft)
	{
		needsUpdate = searchStandFor(p, q->pLeft);
		if (!needsUpdate)
			return needsUpdate;
		switch (q->bal)
		{
		case -1:
			q->bal = 0;
			return true;
		case 0:
			q->bal = 1;
			return false;
		case 1:
			rightBalance(p);
			return false;
		}

	}
	else
	{
		p->data = q->data;
		p = q;
		q = q->pRight;
		return true;
	}

}

AVLTree::~AVLTree()
{

}
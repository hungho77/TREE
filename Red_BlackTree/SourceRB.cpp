#include"RBTree.h"
#include<iostream>
using namespace std;

RBNode* RBTree::NIL = new RBNode();

void main()
{
	RBTree T;
	int n;
	cout << "Creat Red-Black Tree" << endl;
	do
	{
		cout << "Input element key (press -1 to exit): ";
		cin >> n;
		if (n == -1)
			break;
		T.insert(n);
	} while (1);
	cout << "All element of tree follow left node right..." << endl;
	T.print();
	cout << endl;
	cout << "Search an element..." << endl;
	cout << "Input element key: ";
	cin >> n;
	cout << "Element finding..." << endl;
	if (T.search(n) == RBTree::NIL)
	{
		cout << "Not found!" << endl;
		return;
	}
	cout << "key: " << T.search(n)->key << endl;
	cout << "Parent's key: " << T.search(n)->pParent->key << endl;
	cout << "remove node..." << endl;
	cout << "Input key: ";
	cin >> n;
	T.remove(n);
	cout << "Tree after remove.." << endl;
	T.print();
	cout << endl;
}
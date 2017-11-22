#include<iostream>
#include"AVLTree.h"
using namespace std;

int main()
{
	AVLTree tree;
	tree.insert_nonrecursive(4);
	tree.insert_nonrecursive(5);
	tree.insert_nonrecursive(2);
	tree.insert_nonrecursive(12);
	tree.insert_nonrecursive(30);
	tree.insert_nonrecursive(24);
	tree.insert_nonrecursive(9);
	tree.remove(24);
	return 0;
}
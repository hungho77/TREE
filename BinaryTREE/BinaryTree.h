#pragma once
#include"NODE.h"
#include<iostream>
using namespace std;

template<class T>
class BinaryTree
{
protected:
	NODE<T> *roof;
public:
	virtual BinaryTree();
	virtual NODE<T> *search(int id) = 0;
};

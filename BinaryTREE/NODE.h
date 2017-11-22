#pragma once
template<class T>
class NODE
{
	T data;
	int id;
	NODE<T> *left;
	NODE<T> *right;
public:
	NODE();
	~NODE();
};


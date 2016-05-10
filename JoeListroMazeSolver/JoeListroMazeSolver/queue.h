#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include "node.h"

using namespace std;

template <class T>
class Queue {
private:
	Node<T> *mHead, *mTail;
	int     mCount;

public:
	Queue();
	~Queue();

	int  getCount();

	void clear();
	T    dequeue();
	void display();
	void enqueue(T data);
	bool isEmpty();
	bool isExist(T searchKey);
};


template <class T>
Queue<T>::Queue()
{
	mHead = NULL;
	mTail = NULL;
	mCount = 0;
}


template <class T>
Queue<T>::~Queue()
{
	while (!isEmpty())
		dequeue();
}


template <class T>
int Queue<T>::getCount()
{
	return mCount;
}


template <class T>
void Queue<T>::clear()
{
	while (!isEmpty())
		dequeue();
}


template <class T>
T Queue<T>::dequeue()
{
	T       data = T();
	Node<T> *tmp;

	if (!isEmpty())
	{
		tmp = mHead;

		mHead = tmp->mNext;

		tmp->mNext = NULL;
		data = tmp->mData;

		delete tmp;

		mCount--;
	}

	return data;
}


template <class T>
void Queue<T>::display()
{
	Node<T> *tmp;

	if (isEmpty())
		cout << "Empty Queue\n";
	else
	{
		tmp = mHead;

		while (tmp != NULL)
		{
			cout << tmp->mData << " ";
			tmp = tmp->mNext;
		}
		cout << endl;
	}
}


template <class T>
void Queue<T>::enqueue(T data)
{
	Node<T> *newNode;

	newNode = new Node<T>(data);
	if (newNode == NULL)
	{
		cerr << "System Error:  Insufficient Space to Generate Another Node!!\n";
		return;
	}

	mCount++;

	if (mHead == NULL)
	{
		mHead = newNode;
		mTail = newNode;
	}
	else
	{
		mTail->mNext = newNode;
		mTail = newNode;
	}
}


template <class T>
bool Queue<T>::isEmpty()
{
	return mCount == 0;
}


template <class T>
bool Queue<T>::isExist(T searchKey)
{
	bool    found = false;
	Node<T> *tmp;

	if (!isEmpty())
	{
		tmp = mHead;

		while (tmp != NULL)
		{
			if (tmp->mData == searchKey)
			{
				found = true;
				break;
			}

			tmp = tmp->mNext;
		}
	}

	return found;
}


#endif
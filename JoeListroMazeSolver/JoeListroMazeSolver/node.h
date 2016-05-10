/* ***       Author:  Wei Kian Chen
*  Last Update:  September 4, 2013
*        Class:  CSI-281
*     Filename:  node.h
*
*  Description:
*      This is the template node definition.
*
*  Certification of Authenticity:
*     I certify that this assignment is entirely my own work.
**********************************************************************/

#ifndef NODE_H
#define NODE_H

#include <iostream>

using namespace std;

template <class T>
struct Node
{
	T       mData;
	Node<T> *mNext;

	Node();
	Node(T data);
};


/*      Pre:  None
*     Post:  This object is initialized using default values
*  Purpose:  To intialize date object
*************************************************************************/
template <class T>
Node<T>::Node()
{
	mData = T();
	mNext = NULL;
}


/*      Pre:  None
*     Post:  This object is initialized using specified data
*  Purpose:  To intialize date object
*************************************************************************/
template <class T>
Node<T>::Node(T data)
{
	mData = data;
	mNext = NULL;
}

#endif
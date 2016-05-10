/* ***       Author:  Wei Kian Chen
*  Modified by: Raul Quiroga
*  Last edit by: Joe Listro
*  Last Update:  February 10, 2015
*     Filename:  linkedList.h
*
*  Description:
*      This is the template linked list definition.
*
*  Certification of Authenticity:
*     I certify that this assignment is entirely my own work.
**********************************************************************/

#ifndef LINKED_LIST
#define LINKED_LIST

#include <iostream>

using namespace std;

bool displayIterations = false;
// Set to true to see each iteration of each sort.
// For testing/grading purposes to visualize sorts.

template <typename T>
class LinkedList
{
    template <typename U>
    struct Node
    {
        U       mData;
        Node<U> *mpNext;
        
        /*      Pre:  None
         *     Post:  This object is initialized using default values
         *  Purpose:  To initialize date object
         *************************************************************************/
        Node()
        {
            mData = U();
            mpNext = NULL;
        }
        
        
        /*      Pre:  None
         *     Post:  This object is initialized using specified data
         *  Purpose:  To intialize date object
         *************************************************************************/
        Node(U data)
        {
            mData = data;
            mpNext = NULL;
        }
    };
private:
	Node<T> *mpHead, 
			*mpTail;
	int     mCount;

public:
	LinkedList();
	~LinkedList();

	int  getCount();
	T    getData(int index);
	void setData(int index, T data);
    int getSize() {return mCount;};

	void clear();
	void display();
	bool insert(T data);
	bool isEmpty();
	bool isExist(T searchKey);
	bool remove(T searchKey);
	T    removeAt(int index);

	T operator[](int index);
    
    // Sorting Fun Declarations
    void bubbleSort();
    
    void insertionSort();

    void selectionSort();
    
    void shellSort();

    void quickSortCall();

    void mergeSortCall();
};


/*      Pre:  None
*     Post:  This object is initialized using the default
*  Purpose:  To initialize date object
*****************************************************************************/
template <typename T>
LinkedList<T>::LinkedList()
{
	mpHead = NULL;
	mpTail = NULL;
	mCount = 0;
}


/*      Pre:  None
*     Post:  All the nodes in the list is deleted
*  Purpose:  To remove all the nodes in the list
*****************************************************************************/
template <typename T>
LinkedList<T>::~LinkedList()
{
	// remove all nodes
	clear();

	// reinitialize the pointers
	mpHead = NULL;
	mpTail = NULL;

	// reinitialize count
	mCount = 0;
}


/*      Pre:  The object is instantiated
*     Post:  The number of nodes in the linked list is returned to the caller
*  Purpose:  To retrieve the number of nodes in the list
*****************************************************************************/
template <typename T>
int LinkedList<T>::getCount()
{
	return mCount;
}


/*      Pre:  The list is instantiated and the index is valid
*     Post:  The data in the specified index is returned to the caller
*  Purpose:  To retrieve the specified nodes in the list
*****************************************************************************/
template <typename T>
T LinkedList<T>::getData(int index)
{
	if ( isEmpty() )
	{
		return NULL;
	}
	else if ( index < mCount && index > -1 )
	{
		Node<T>* temp;
		int i = 0;
		temp = mpHead;
		while (i < mCount)
		{
			if (i == index)
			{
				return temp->mData;
			}
			else
			{
				temp = temp->mpNext;
				i++;
			}
		}
	}
	else
	{
		cout << "Index doesn't exist\n";
	}
	return NULL;
}


/*      Pre:  The list is instantiated, the index is valid and the data is
*            available
*     Post:  The data in the specified index is updated with the specified
*            data
*  Purpose:  To update the specified nodes in the list
*****************************************************************************/
template <typename T>
void LinkedList<T>::setData(int index, T data)
{
	if ( isEmpty() )
	{
		cout << "List is empty\n";
	}
	else if ( index < mCount && index > -1 )
	{
		Node<T>* temp;
		int i = 0;
		//char ans;
		bool found = false;
		temp = mpHead;
		while (i < mCount)
		{
			if (i == index)
			{
				temp->mData = data;
				found = true;
				break;
			}
			else
			{
				temp = temp->mpNext;
				i++;
			}
			
		}
	}
	else
	{
		cout << "Index doesn't exist\n";
	}
}



/*      Pre:  The list is initiated
*     Post:  All the nodes in the list is deleted
*  Purpose:  To remove all the nodes in the list
*****************************************************************************/
template <typename T>
void LinkedList<T>::clear()
{
	if (isEmpty())
	{

	}
	else
	{
		Node<T> *temp;
		temp = mpHead;
		while (temp != NULL)
		{
			mpHead = mpHead->mpNext;
			temp->mpNext = NULL;
			delete temp;
			temp = mpHead;
		}
		mCount = 0;
	}
}



/*      Pre:  The list is instantiated
*     Post:  The entire list is displayed on the screen
*  Purpose:  To show the content of the list
*****************************************************************************/
template <typename T>
void LinkedList<T>::display()
{
	int i = 0;
	if ( isEmpty() )
	{

	}
	else
	{
		Node<T>* temp;
		temp = mpHead;
		while ( temp != NULL )
		{
			cout << "Data in node " << i << ": " << temp->mData << ".\n";
			temp = temp->mpNext;
			i++;
		}
	}
}


/*      Pre:  The list is initantiated and the data is available
*     Post:  The data is inserted in ascending order
*  Purpose:  To insert a data into the list in ascending order.  However, if
*            the data already existed in the list, it will not be added again
*****************************************************************************/
template <typename T>
bool LinkedList<T>::insert(T data)
{
	Node<T> *newNode;
	newNode = new Node<T>(data);
	if ( newNode == NULL )
	{
		return false;
	}
	if ( mpHead == NULL )
	{
		mpHead = newNode;
		mpTail = newNode;
		mCount++;
		return true;
	}
	else
	{
		mpTail->mpNext = newNode;
		mpTail = newNode;
		mCount++;
		return true;
	}
	/*if ( mpHead->mData >= data )
	{
		newNode->mpNext = mpHead;
		mpHead = newNode;
		mCount++;
		return true;
	}
	else if ( mpTail->mData <= data )
	{
		mpTail->mpNext = newNode;
		mpTail = newNode;
		mCount++;
		return true;
	}
	else
	{
		temp = mpHead;
		oneBefore = mpHead;
		while ( temp->mData <= data )
		{
			oneBefore = temp;
			temp = temp->mpNext;
		}
		if (temp->mData == data)
		{
		
		//If you don't allow for duplication
		//delete newNode;
		}
		newNode->mpNext = temp;
		oneBefore->mpNext = newNode;
		mCount++;
		return true;
	}*/
}


/*      Pre:  The list is instantiated
*     Post:  The function returns true is the list is empty; false otherwise
*  Purpose:  To determine if the list is empty
*****************************************************************************/
template <typename T>
bool LinkedList<T>::isEmpty()
{
	return ( mpHead == NULL );
}


/*      Pre:  The list is instantiated and the searchKey is available
*     Post:  The function returns true if the search key exists in the list;
*            otherwise false
*  Purpose:  To determine if a specific value exists in the list or not
*****************************************************************************/
template <typename T>
bool LinkedList<T>::isExist(T searchKey)
{
	if ( !isEmpty() )
	{
		Node<T> *temp;
		temp = mpHead;
        int i = 0;
		while (temp != NULL)
		{
			if ( temp->mData == searchKey )
			{
                cout << "Data in node " << i << " is " << temp->mData << ".\n";
				return true;
			}
			else
			{
                i++;
				temp = temp->mpNext;
			}
		}
		return false;
	}
	else
	{
		return false;
	}
}


/*      Pre:  The list is instantiated and the searchKey is available
*     Post:  If the searchKey exists, removes it from the list and the
*            function returns true; otherwise the function does nothing
*            and returns false
*  Purpose:  To remove a specific value from the list
*****************************************************************************/
template <typename T>
bool LinkedList<T>::remove(T searchKey)
{
	if ( isEmpty() )
	{
		return false;
	}
	else if ( mpHead->mpNext == NULL && mpHead->mData == searchKey )
	{
		mpHead = NULL;
		delete mpHead;
		mpHead = new Node<T>(searchKey);
		mCount--;
		return true;
	}
	else
	{
	}
	Node<T> *toBeDeleted,
			*temp,
			*oneBefore;
	if ( mpHead->mData == searchKey )
	{
		toBeDeleted = mpHead;
		mpHead = mpHead->mpNext;
		toBeDeleted->mpNext = NULL;
		delete toBeDeleted;
		mCount --;
		return true;
	}
	else if ( mpTail->mData == searchKey )
	{
		temp = mpHead;
		while ( temp->mpNext != mpTail )
		{
			temp = temp->mpNext;
		}

		toBeDeleted = mpTail;
		mpTail = temp;
		mpTail->mpNext = NULL;
		delete toBeDeleted;
		mCount --;
		return true;
	}
	else
	{
		temp = mpHead;
		oneBefore = mpHead;
		while ( temp != NULL && temp->mData != searchKey )
		{
			oneBefore = temp;
			temp = temp->mpNext;
		}
		if ( temp != NULL )
		{
			toBeDeleted = temp;
			oneBefore->mpNext = temp->mpNext;
			toBeDeleted->mpNext = NULL;
			delete toBeDeleted;
			mCount --;
			return true;
		}
		return false;
	}
}


/*      Pre:  The list is instantiated and the index is valid
*     Post:  Remove the element in the specified index location and returns
*            its content to the caller.  If the index location is invalid, the
*            function returns the default value
*  Purpose:  To remove an item in the specified index location
*****************************************************************************/
template <typename T>
T LinkedList<T>::removeAt(int index)
{
	if ( isEmpty() )
	{
		cout << "List is empty\n";
		return NULL;
	}
	else if ( index == 0 )
	{
		char ans;
		Node<T>* temp = mpHead;
		T data = mpHead->mData;
		while ( true )
		{
			cout << "You are removing the head which has this data in it: " << mpHead->mData << endl << "To continue input answer.\n" << "(Y)es\n" << "(N)o\n";
			cin >> ans;
			switch ( ans )
			{
			case 'y':
			case 'Y':
				mpHead = mpHead->mpNext;
				temp->mpNext = NULL;
				delete temp;
				mCount--;
				return data;
				break;
			case 'n':
			case 'N':
				cout << "Nothing deleted\n";
				return NULL;
				break;
			default:
				cout << "Not valid input\n";
			}
		}
	}
	else if (index == (mCount - 1))
	{
		Node<T> *temp,
				*toBeDeleted;
		T data;
		char ans;
		toBeDeleted = mpHead;
		temp = mpHead;
		while (toBeDeleted->mData != mpTail->mData)
		{
			temp = toBeDeleted;
			toBeDeleted = toBeDeleted->mpNext;
		}

		while ( true )
		{
			cout << "You are removing the tail which has this data in it: \n" << "index- " << index << endl << "data- " << toBeDeleted->mData << endl << "(Y)es\n" << "(N)o\n";
			cin >> ans;
			switch ( ans )
			{
				case 'y':
				case 'Y':
					data = toBeDeleted->mData;
					temp->mpNext = NULL;
					mpTail = temp;
					toBeDeleted->mpNext = NULL;
					delete toBeDeleted;
					mCount--;
					return data;
					break;
				case 'n':
				case 'N':
					return NULL;
					break;
				default:
					cout << "Not valid input\n";
			}
		}
	}
	else if ( index < getCount() && index > -1 )
	{
		Node<T> *temp,
				*toBeDeleted;
		T data;
		int i = 0;
		char ans;
		toBeDeleted = mpHead;
		temp = mpHead;
		while (i < mCount)
		{
			if (i == index)
			{
				while ( true )
				{
					cout << "You are removing the follow data:\n" << "index- " << index << endl << "data- " << toBeDeleted->mData << endl << "(Y)es\n" << "(N)o\n";
					cin >> ans;
					switch ( ans )
					{
					case 'y':
					case 'Y':
						data = toBeDeleted->mData;
						temp->mpNext = toBeDeleted->mpNext;
						toBeDeleted->mpNext = NULL;
						delete toBeDeleted;
						mCount--;
						return data;
						break;
					case 'n':
					case 'N':
						return NULL;
						break;
					default:
						cout << "Not valid input\n";
					}
				}
				break;
			}
			else
			{
				temp = toBeDeleted;
				toBeDeleted = toBeDeleted->mpNext;
				i++;
			}

		}
	}
	else
	{
		cout << "Index doesn't exist\n";
	}
	return NULL;
}


/*      Pre:  The list is instantiated and the index is valid
*     Post:  The data in the specified index is returned to the caller
*  Purpose:  To retrieve the specified nodes in the list using [] operator
*****************************************************************************/
template <typename T>
T LinkedList<T>::operator[](int index)
{
	if ( isEmpty() )
	{
		cout << "List empty\n";
		return NULL;
	}
	else if ( index < mCount && index > -1 )
	{
		int i = 0;
		Node<T>* temp;
		temp = mpHead;
		while ( i < mCount )
		{
			if ( i == index )
			{
				return temp->mData;
			}
			else
			{
				temp = temp->mpNext;
				i++;
			}
		}
	}
	else
	{
		cout << "Index doesn't exist\n";
	}
	return NULL;
}


// Sorting Fun Implementations

template <typename T>
void LinkedList<T>::bubbleSort()
{
	T dataHold;
	for (int i = 0; i < (mCount - 1); i++)
	{
		for (int j = 0; j < (mCount - 1 - i); j++)
		{
			if (getData(j + 1) < getData(j))
			{
				dataHold = getData(j+1);
				setData(j+1, getData(j));
				setData(j, dataHold);
				if (displayIterations == true)
				{
					display();
				}
			}
		}
	}
	return;
}

template <typename T>
void LinkedList<T>::insertionSort()
{
	int i, j;
	T dataHold;
	for (i = 0; i < mCount; i++)
	{
		dataHold = getData(i);
		j = i - 1;
		while ((j>=0) && (getData(j) > dataHold))
		{
			setData(j + 1, getData(j));
			j--;
			if (displayIterations == true)
			{
				display();
			}
		}
		setData(j + 1, dataHold);
	}
	return;
}

template <typename T>
void LinkedList<T>::selectionSort()
{
	int i, j, iMin;
	T dataHold;

	for (i = 0; i < (mCount - 1); i++)
	{
		iMin = i;
		for (j = i + 1; j < mCount; j++)
		{
			if (getData(j) < getData(iMin))
			{
				iMin = j;
			}
		}

		if (iMin != i)
		{
			dataHold = getData(i);
			setData(i, getData(iMin));
			setData(iMin, dataHold);
			if (displayIterations == true)
			{
				display();
			}
		}
	}
	return;
}

template <typename T>
void LinkedList<T>::shellSort()
{
	int g, i, j;
	T dataHold;
	int gaps[6] = { 9, 7, 5, 3, 2, 1 };

	for (g = 0; g < 6; g++)
	{
		for (i = gaps[g]; i < mCount; i++)
		{
			dataHold = getData(i);
			for (j = i; ((j >= gaps[g]) && (getData(j - gaps[g]) > dataHold)); j -= gaps[g])
			{
				setData(j, getData(j - gaps[g]));
			}
			setData(j, dataHold);
			if (displayIterations == true)
			{
				display();
			}
		}
	}
	return;
}

template <typename T>
void LinkedList<T>::quickSortCall()
{
	quickSort(this, 0, mCount);

	return;
}


template <typename T>
void LinkedList<T>::mergeSortCall()
{
	mergeSort(this);
	return;
}

// Sort Functions for recursion

// QuickSort Function Declarations
template<typename T>
void quickSort(LinkedList<T>* a, int l, int r);

template<typename T>
int partition(LinkedList<T> a, int r);

// QuickSort Function Implementation
template<typename T>
void quickSort(LinkedList<T>* a, int l, int r)
{
    int s;
	if (l == r) { return; };
	if (l < r)
	{
		s = partition(a, l, r);
		quickSort(a, l, s-l);
		quickSort(a, s + 1, r);
	}
	return;
}

template<typename T>
int partition(LinkedList<T>* a, int l, int r)
{
	int p = a->getData(l), s = l, dataHold;
	for (int i = (l + 1); i < r; i++)
	{
		if (a->getData(i) < p)
		{
			s++;
			dataHold = a->getData(s);
			a->setData(s, a->getData(i));
			a->setData(i, dataHold);
		}
	}
	dataHold = a->getData(l);
	a->setData(l, a->getData(s));
	a->setData(s, dataHold);
	return s;
}

// MergeSort Function Declarations
template <typename T>
void mergeSort(LinkedList<T>* aList);

template <typename T>
void Merge(LinkedList<T>* bList, LinkedList<T>* cList, LinkedList<T>* aList);

// MergeSort Function Implementation
template <typename T>
void mergeSort(LinkedList<T>* aList)
{
	int size = aList->getSize();
	LinkedList<T> bList, cList;
	if (size > 1)
	{
		for (int i = 0; i < (size / 2); i++)
		{
			bList.insert(aList->getData(i));
		}
		for (int i = (size / 2); i < size; i++)
		{
			cList.insert(aList->getData(i));
		}
		mergeSort(&bList);
		mergeSort(&cList);
		Merge(&bList, &cList, aList);
	}
	return;
}

template <typename T>
void Merge(LinkedList<T>* bList, LinkedList<T>* cList, LinkedList<T>* aList)
{
	int i = 0, j = 0, k = 0, p = bList->getSize(), q = cList->getSize();
	while ((i < p) && (j < q))
	{
		if (bList->getData(i) <= cList->getData(j))
		{
			aList->setData(k, bList->getData(i));
			i++;
		}
		else
		{
			aList->setData(k, cList->getData(j));
			j++;
		}
		k++;
	}
	if (i == p)
	{
		do
		{
			aList->setData(k, cList->getData(j));
			j++;
			k++;
		} while (j < q);
	}
	else
	{
		do
		{
			aList->setData(k, bList->getData(i));
			i++;
			k++;
		} while (i < p);
	}
	return;
}

#endif
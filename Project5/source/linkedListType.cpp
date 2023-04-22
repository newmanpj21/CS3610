#include "linkedListType.h"

#include <cstddef>
#include <iostream>

using namespace std;


template <class Type>
bool linkedListType<Type>::isEmptyList() const {
	return (first == nullptr);
}


template <class Type>
linkedListType<Type>::linkedListType() //default constructor
{
	first = NULL;
	last = NULL;
	count = 0;
}


template <class Type>
void linkedListType<Type>::destroyList() {
	nodeType<Type>* temp; //pointer to deallocate the memory
	//occupied by the node
	while (first != nullptr) //while there are nodes in the list
	{
		temp = first; //set temp to the current node
		first = first->link; //advance first to the next node
		delete temp; //deallocate the memory occupied by temp
	}
	last = NULL; //initialize last to NULL; first has already
	//been set to NULL by the while loop
	count = 0;
}


template <class Type>
void linkedListType<Type>::initializeList() {
	destroyList(); //if the list has any nodes, delete them
}


template <class Type>
void linkedListType<Type>::print() const {
	nodeType<Type>* current; //pointer to traverse the list
	current = first; //set current point to the first node
	while (current != nullptr) //while more data to print
	{
		cout << current->info << " ";
		current = current->link;
	}
} //end print
template <class Type>
int linkedListType<Type>::length() const {
	return count;
}


template <class Type>
Type linkedListType<Type>::front() const {
	assert(first != nullptr);
	return first->info; //return the info of the first node
} //end front
template <class Type>
Type linkedListType<Type>::back() const {
	assert(last != nullptr);
	return last->info; //return the info of the last node
} //end back
template <class Type>
linkedListIterator<Type> linkedListType<Type>::begin() {
	linkedListIterator<Type> temp(first);
	return temp;
}


template <class Type>
linkedListIterator<Type> linkedListType<Type>::end() {
	linkedListIterator<Type> temp(NULL);
	return temp;
}


template <class Type>
void linkedListType<Type>::copyList
(const linkedListType<Type>& otherList) {
	nodeType<Type>* newNode; //pointer to create a node
	nodeType<Type>* current; //pointer to traverse the list
	if (first != nullptr) //if the list is nonempty, make it empty
		destroyList();
	if (otherList.first == nullptr) //otherList is empty
	{
		first = NULL;
		last = NULL;
		count = 0;
	}
	else {
		current = otherList.first; //current points to the
		//list to be copied
		count = otherList.count;
		//copy the first node
		first = new nodeType<Type>; //create the node
		first->info = current->info; //copy the info
		first->link = NULL; //set the link field of the node to NULL
		last = first; //make last point to the first node
		current = current->link; //make current point to the next
		// node
		//copy the remaining list
		while (current != nullptr) {
			newNode = new nodeType<Type>; //create a node
			newNode->info = current->info; //copy the info
			newNode->link = NULL; //set the link of newNode to NULL
			last->link = newNode; //attach newNode after last
			last = newNode; //make last point to the actual last
			//node
			current = current->link; //make current point to the
			//next node
		} //end while
	} //end else
} //end copyList
template <class Type>
linkedListType<Type>::~linkedListType() //destructor
{
	destroyList();
}


template <class Type>
linkedListType<Type>::linkedListType
(const linkedListType<Type>& otherList) {
	first = NULL;
	copyList(otherList);
} //end copy constructor
//overload the assignment operator
template <class Type>
const linkedListType<Type>& linkedListType<Type>::operator=
(const linkedListType<Type>& otherList) {
	if (this != &otherList) //avoid self-copy
	{
		copyList(otherList);
	} //end else
	return *this;
}

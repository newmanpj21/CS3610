#pragma once
//*************************************************************
// Author: D.S. Malik
//
// This class specifies the basic operations on a queue as a
// linked list.
//*************************************************************
//Definition of the node
#include "queueADT.h"


template <class Type>
class linkedQueueType : public queueADT<Type> {
public:
	const linkedQueueType<Type>& operator=
	(const linkedQueueType<Type>&);

	//Overload the assignment operator.
	bool isEmptyQueue() const override;

	//Function to determine whether the queue is empty.
	//Postcondition: Returns true if the queue is empty,
	// otherwise returns false.
	bool isFullQueue() const override;

	//Function to determine whether the queue is full.
	//Postcondition: Returns true if the queue is full,
	// otherwise returns false.
	void initializeQueue() override;

	//Function to initialize the queue to an empty state.
	//Postcondition: queueFront = NULL; queueRear = NULL
	Type front() const override;

	//Function to return the first element of the queue.
	//Precondition: The queue exists and is not empty.
	//Postcondition: If the queue is empty, the program
	// terminates; otherwise, the first element of the
	// queue is returned.
	Type back() const override;

	//Function to return the last element of the queue.
	//Precondition: The queue exists and is not empty.
	//Postcondition: If the queue is empty, the program
	// terminates; otherwise, the last element of the
	// queue is returned.
	void addQueue(const Type& queueElement) override;

	//Function to add queueElement to the queue.
	//Precondition: The queue exists and is not full.
	//Postcondition: The queue is changed and queueElement is
	// added to the queue.
	void deleteQueue() override;

	//Function to remove the first element of the queue.
	//Precondition: The queue exists and is not empty.
	//Postcondition: The queue is changed and the first element
	// is removed from the queue.
	linkedQueueType();

	//Default constructor
	linkedQueueType(const linkedQueueType<Type>& otherQueue);

	//Copy constructor
	~linkedQueueType();

	//Destructor
private:
	nodeType<Type>* queueFront; //pointer to the front of the queue
	nodeType<Type>* queueRear; //pointer to the rear of the queue
};

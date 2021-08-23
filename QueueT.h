#pragma once
#include <iostream>
#include <stdexcept>
using std::cout;
using std::endl;
using std::runtime_error;

// NodeT Class
template <class T>
class NodeT
{
	public:
	T data;
	NodeT<T>* next;

	// Constructors
	NodeT<T>(T val, NodeT<T>* nextPointer) : data(val), next(nextPointer) {};
	NodeT<T>(T val) : data(val), next(nullptr) {};
};

// QueueT Class
template <class T>
class QueueT
{
	public:
	QueueT();
	QueueT(const QueueT& queue_parameter);
	~QueueT();
	QueueT& operator=(const QueueT& queue_parameter);
	void enqueue(T parameter);
	T dequeue();
	void print() const;
	bool empty() const;
	int size() const;
	void concatenate(QueueT& queue_parameter, int n);
	QueueT merge(const QueueT& queue_parameter) const;
	NodeT<T>* getFront();

	private:
	NodeT<T>* front;
	NodeT<T>* back;
	int current_size;
	void copyQueue(const QueueT& queue_parameter);
	void deleteQueue();
};

// QueueT method implementations
// Default constructor
template <class T>
QueueT<T>::QueueT()
{
	front = back = nullptr;
	current_size = 0;
}

// Copy constructor
template <class T>
QueueT<T>::QueueT(const QueueT& queue_parameter)
{
	front = back = nullptr;

	// Deep copies its constant QueueT reference parameter
	copyQueue(queue_parameter);
	current_size = queue_parameter.current_size;
}

// Destructor
template <class T>
QueueT<T>::~QueueT()
{
	deleteQueue();
}

// Helper Function for Destroying Queue
// Deallocates dynamic memory allocated by the queue
template <class T>
void QueueT<T>::deleteQueue()
{
	// Iterate the queue, destroying one node at a time
	NodeT<T>* temp = front;
	while (front != nullptr)
	{
		front = temp->next;
		delete temp;
		temp = front;
	}
	current_size = 0;
	front = back = nullptr;
}

// Overloads the assignment operator for QueueT
template <class T>
QueueT<T>& QueueT<T>::operator=(const QueueT& queue_parameter)
{
	// If the calling object is the parameter, the operator should not copy it
	if (this != &queue_parameter)
	{
		// Dallocates dynamic memory associated with the original queue
		deleteQueue();

		// Deep copies its constant QueueT reference parameter
		copyQueue(queue_parameter);
		current_size = queue_parameter.current_size;
	}
	// Returns a reference to the calling object
	return *this;
}

// Helper function to creates a copy of the parameter
// onto the calling object queue
template <class T>
void QueueT<T>::copyQueue(const QueueT& queue_parameter)
{
	if (queue_parameter.front != nullptr)
	{
		// Iterate through the parameter queue.
		// Enqueue each data element to the calling object.
		NodeT<T>* temp = queue_parameter.front;
		while (temp != nullptr)
		{
			enqueue(temp->data);
			temp = temp->next;
		}
	}
	// Parameter queue is empty
	else
	{
		front = back = nullptr;
	}
}

// Inserts the parameter at the back of the queue
template <class T>
void QueueT<T>::enqueue(T parameter)
{
	// If the node is empty
	if (back == nullptr)
	{
		back = new NodeT<T>(parameter);
		front = back;
	}
	// Node contains items
	else
	{
		// Create a new node and assign it to the back
		NodeT<T>* temp = new NodeT<T>(parameter);
		back->next = temp;
		back = temp;
	}
	current_size++;
}

// Removes and returns the value at the front of the queue
template <class T>
T QueueT<T>::dequeue()
{
	// If the queue is empty, throw a runtime_error
	if (front == nullptr)
	{
		throw runtime_error("dequeue failed - empty");
	}
	NodeT<T>* temp = front;

	// Store the value before deleting the node
	T data = front->data;

	// Update the front and check if list becomes empty
	front = front->next;

	if (front == nullptr)
	{
		back = nullptr;
	}

	current_size--;
	delete temp;
	return data;
}

// Prints the contents of the queue
template <class T>
void QueueT<T>::print() const
{
	NodeT<T>* temp = front;

	// Print one value per line, from front to back
	while (temp != nullptr)
	{
		cout << temp->data << endl;
		temp = temp->next;
	}
}

// Returns true if the queue is empty, false otherwise
template <class T>
bool QueueT<T>::empty() const
{
	return front == nullptr && back == nullptr;
}

// Returns the number of items stored in the queue
template <class T>
int QueueT<T>::size() const
{
	return current_size;
}

// Adds the first parameter n values stored in its QueueT parameter
// to the end of the calling object
template <class T>
void QueueT<T>::concatenate(QueueT& queue_parameter, int n)
{
	int count = 0;

	// If n is invalid, throw a runtime_error 
	if (n > queue_parameter.size())
	{
		throw runtime_error("concatenate failed - n > queue size");
	}
	while (count < n)
	{
		// Remove the value from the parameter and add it to the calling object
		enqueue(queue_parameter.dequeue());
		count++;
	}
}

// Returns a QueueT object containing contents of the
// calling object and QueueT reference parameter
template <class T>
QueueT<T> QueueT<T>::merge(const QueueT& queue_parameter) const
{
	QueueT merged_queue;
	NodeT<T>* calling_object_node = front;
	NodeT<T>* parameter_node = queue_parameter.front;

	// Iterate through both queues, inserting elements from each one at a time
	while (calling_object_node != nullptr || parameter_node != nullptr)
	{
		if (calling_object_node != nullptr)
		{
			merged_queue.enqueue(calling_object_node->data);
			calling_object_node = calling_object_node->next;
		}
		if (parameter_node != nullptr)
		{
			merged_queue.enqueue(parameter_node->data);
			parameter_node = parameter_node->next;
		}
	}
	// Return a new queue containing alternating data from both queues
	return merged_queue;
}

// Returns a pointer to the node at the front of the queue 
template <class T>
NodeT<T>* QueueT<T>::getFront()
{
	return front;
};
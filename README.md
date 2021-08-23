# Queue-Implementation
Queue Implementation in C++ using Linked Lists as the underlying data structure.

### Queue Method Descriptions:

- constructor – creates an empty queue
- copy constructor – a constructor that creates a deep copy of its constant QueueT reference parameter.
- destructor – deallocates dynamic memory allocated by the queue.
- operator= – overloads the assignment operator for QueueT.
- dequeue – removes and returns the value at the front of the queue; if the queue is empty throws a runtime_error.
- print – prints the contents of the queue from front to back.
- empty – returns true if the queue is empty, false otherwise.
- size – returns the number of items stored in the queue.
concatenate – has two parameters, a QueueT reference and an integer that adds the first n values stored in its QueueT parameter to the end of the calling object.
- merge – returns a QueueT object that contains the contents of the calling object and its constant QueueT reference parameter.
- getFront – returns a pointer to the node at the front of the queue.

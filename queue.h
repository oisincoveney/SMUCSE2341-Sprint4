#ifndef QUEUE
#define QUEUE

#include "linkedlist.h"

/**
 * The Queue class provides an implementation of a queue, which is a
 * first in, first out (FIFO) data structure. A Queue uses a LinkedList
 * to provide its functionality.
 *
 * The Queue class will be used in the Sprint4: Flight Planner project
 * in SMU CSE2341.
 *
 * By: Oisin Coveney
 * Created:         March 24, 2017
 * Last Modiifed:   March 24, 2017
 */
template<class T>
class Queue
{
    public:
        T dequeue();
        T peek();
        void enqueue(T);
        bool isEmpty();
        ~Queue();

    private:
        LinkedList<T> data;

};

#endif

/**
 * dequeue()
 *
 * Removes the entry at the beginning of the queue.
 *
 * @return the data in the former first entry of the queue
 */
template<class T>
T Queue<T>::dequeue()
{
    return data.popFront();
}

/**
 * peek()
 *
 * @return the data in the first entry of the queue
 */
template<class T>
T Queue<T>::peek()
{
    return data.front();
}

/**
 * enqueue(T d)
 *
 * Adds the data given by the user into the queue
 *
 * @param d : the data to add to the end of the queue
 */
template<class T>
void Queue<T>::enqueue(T d)
{
    return data.pushBack(d);
}

/**
 * isEmpty()
 *
 * @return true if the queue is empty (size = 0), false if not
 */
template<class T>
bool Queue<T>::isEmpty()
{
    return data.empty();
}

/**
 * Destructor
 */
template <class T>
Queue<T>::~Queue() {}

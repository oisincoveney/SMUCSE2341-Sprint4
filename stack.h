#ifndef STACK
#define STACK

#include "linkedlist.h"

/**
 * The Stack class provides an implementation of a stack, which is a
 * last in, first out (LIFO) data structure. A Stack uses a LinkedList
 * to provide its functionality.
 *
 * The Stack class will be used in the Sprint4: Flight Planner project
 * in SMU CSE2341.
 *
 * By: Oisin Coveney
 * Created:         March 24, 2017
 * Last Modiifed:   March 24, 2017
 */
template<class T>
class Stack
{
    public:
        T pop();
        T& peek();
        void push(T);
        bool isEmpty();
        LinkedList<T> readStack() const;
        int size() const;
        T front();
        ~Stack();

        T* peekPointer();
    private:
        LinkedList<T> data;

};


/**
 * pop()
 *
 * Removes the last entry of the stack.
 * @return the data in the last entry of the stack
 */
template<class T>
T Stack<T>::pop()
{
    return data.popBack();
}

/**
 * peek()
 *
 * @return the data within the last entry of the stack
 */
template<class T>
T& Stack<T>::peek()
{
    return data.back();
}

template<class T>
T* Stack<T>::peekPointer()
{
    return &(data.back());
}


/**
 * push()
 *
 * Places the data given by the user into the last entry of the stack
 * @param d : the data to add to the stack
 */
template<class T>
void Stack<T>::push(T d)
{
    data.pushBack(d);
}

/**
 * empty()
 *
 * @return true if the stack is empty (size = 0), false if not
 */
template<class T>
bool Stack<T>::isEmpty()
{
    return data.empty();
}


/**
 * readStack()
 *
 * Returns the underlying LinkedList. This function will be used
 * mostly within the Flight Planner Project
 *
 * @return the underlying LinkedList of <T> values
 *
 */
template<class T>
LinkedList<T> Stack<T>::readStack() const
{
    return data;
}

/**
 * size()
 *
 * @return the size of the underlying linked list under the Stack class
 */
template<class T>
int Stack<T>::size() const
{
    return data.length();
}

/**
 * front()
 *
 * @return the first (bottom) element of the stack.
 */
template<class T>
T Stack<T>::front()
{
    return data.front();
}

/**
 * Destructor
 */
template <class T>
Stack<T>::~Stack() {}

#endif

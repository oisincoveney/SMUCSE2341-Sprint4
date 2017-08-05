#pragma once
#include <ostream>


/**
 * The Node class represents the nodes within a Linked List data structure.
 * Nodes are doubly-linked, and contain two pointers that represent Nodes
 * that come before and after it within a linked list.
 *
 * The Node class will be used within the LinkedList class, and will be used
 * for the Sprint4: Flight Planner project in SMU CSE2341.
 *
 * By: Oisin Coveney
 * Created:         March 19, 2017
 * Last Modified:   March 24, 2017
 */
template <class T>
class Node
{
    private:
        template <class U> friend class LinkedList;
        T data;
        Node<T>* next;      //Pointers to other nodes within list
        Node<T>* previous;

    public:
        //Constructors
        Node();
        Node(T data);
        Node(const Node<T>& n);
        Node<T>& operator=(const Node<T>& n);

        //Getters and setters
        T getData() const;
        void setData(const T& value);
        Node<T>* getNext() const;
        void setNext(Node<T>* value);
        Node<T>* getPrevious() const;
        void setPrevious(Node<T>* value);

        //operator<< overload
        template<class S>
        friend std::ostream& operator<<(std::ostream& o, const Node<S>& node);
};

/**
 * Default constructor
 */
template<class T>
Node<T>::Node() : next{nullptr}, previous{nullptr}, data{} {}

/**
 * Constructor with (T data) - will usually be the most-used constructor,
 * and creates a Node with nullptr references to other nodes, but contains
 * the data given by the user.
 *
 * @param data : data passed by the user
 */
template<class T>
Node<T>::Node(T data) : data{data}, next{nullptr}, previous{nullptr} {}

/**
 * Copy constructor
 */
template<class T>
Node<T>::Node(const Node<T>& n)
    : data{n.data}, next{n.next}, previous{nullptr}{}

/**
 * Copy assignment operator
 */
template<class T>
Node<T>& Node<T>::operator=(const Node<T>& n)
{
    data = n.data;
    next = n.next;
    previous = n.previous;
}

/**
 * getData() const
 *
 * @return the data within the Node
 */
template<class T>
T Node<T>::getData() const
{
    return data;
}

/**
 * setData(value)
 *
 * @param value - the value to set the data to
 */
template<class T>
void Node<T>::setData(const T& value)
{
    data = value;
}

/**
 * getNext() const
 *
 * @return a pointer containing an address to the next Node within the list
 */
template<class T>
Node<T>* Node<T>::getNext() const
{
    return next;
}

/**
 * setNext(value)
 *
 * @param value - a pointer to another Node that will be the Node after this
 */
template<class T>
void Node<T>::setNext(Node<T>* value)
{
    next = value;
}

/**
 * getPrevious() const
 *
 * @return a pointer containing an address to the previous Node within the list
 */
template<class T>
Node<T>* Node<T>::getPrevious() const
{
    return previous;
}

/**
 * setPrevious(value)
 *
 * @param value - a pointer to another Node that will be the Node before this
 */
template<class T>
void Node<T>::setPrevious(Node<T>* value)
{
    previous = value;
}

/**
 * operator<< overload
 *
 * Example output, using a Node<int> with data = 1 as an example:
 * NODE:    DATA: 1    ADDRESS: xxx     PREVIOUS: xxx   NEXT: xxx
 *
 * Usually, this operator overload will not be used within the
 * LinkedList class, whose operator<< overload will pull the
 * data from the node. This overload will usually be used for
 * debugging.
 *
 * @param o : the ostream reference to insert data into
 * @param node : a constant reference to a Node whose data will be placed into
 *               the ostream reference
 * @return an ostream reference that contains the data from (node) within the
 *         format specified in the above comments
 */
template<class S>
std::ostream& operator<<(std::ostream& o, const Node<S>& node)
{
    o << "NODE: ";
    o << "\t DATA: " << node.data;
    o << "\t ADDRESS: " << &node;
    o << "\t PREVIOUS: " << node.previous;
    o << "\t\t\t NEXT: " << node.next;
    return o;
}


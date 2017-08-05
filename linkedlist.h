#pragma once
#include <node.h>
#include <iostream>


/**
 * A LinkedList is a non-contiguously allocated of Nodes that point sequentially
 * to provide an implementation of a list. The LinkedList class can be used
 * in place of a Vector, and provides constant addition and deletion times,
 * but slower (linear) retrieval times compared to a Vector.
 *
 * This LinkedList is doubly-linked, and Nodes contain pointers to the next and
 * previous Nodes within the list.
 *
 * This LinkedList class will be used in the Sprint4: Flight Planner Project,
 * in SMU CS2341.
 *
 * By: Oisin Coveney
 * Created:       March 19, 2017
 * Last Modified: March 25, 2017
 */
template<class T>
class LinkedList
{
    private:

        int size{0};         //size of list
        Node<T>* head;      //beginning of the list
        Node<T>* tail;      //end of the list


        //Copies list from source to dest
        void listCopy(LinkedList& dest, const LinkedList& source);

        //private function to insert elements at a certain pointer
        void insert(Node<T>* ptr, T data);

        //Returns a reference to the Node at the index
        Node<T>* cycle(int index) const;

    public:

        //Rule of 3 + constructors
        LinkedList();                                   //default constructor
        LinkedList(const LinkedList& list);             //copy constructor
        LinkedList& operator=(const LinkedList& list);  //copy assignment oper.
        ~LinkedList();                                  //destructor

        //capacity
        bool empty();
        int length() const;

        //element access
        T& front();
        T get(int index) const;
        T& back();
        int find(T data);
        T* getDataPointer(int index);

        //modifiers
        void insert(int index, T data);
        void pushFront(T data);
        void pushBack(T data);
        void assign(int index, T data);
        int uniquePushBack(T data);

        //removers
        T remove(int index);
        T popFront();
        T popBack();
        void resize(int size, T val);
        void clear();

        //Operator<< overload for LinkedList
        template<class S>
        friend std::ostream& operator<<(std::ostream& o,
                                        const LinkedList<S>& list);

        //operator[] overload
        T& operator[](int);

        //Getters and setters
        Node<T>* getHead() const;
        void setHead(Node<T>* value);
        Node<T>* getTail() const;
        void setTail(Node<T>* value);

        template<class S>
        friend std::ostream& operator<<(std::ostream& o, const LinkedList<S>& list);

};


//Private functions

/**
 * listCopy()
 *
 * Copies a list from destination to source, deleting all elements of the
 * destination list and replacing them with the source list.
 *
 * @param source : the list to copy data into the destination array
 * @param dest : the list with data from the source array
*/
template<class T>
void LinkedList<T>::listCopy(LinkedList& dest, const LinkedList& source)
{
    if(source.getHead() == nullptr)
        return;

    dest.setHead(new Node<T>(source.getHead()->data));

    // Size = 1 -> special case to set tail to the head
    if(source.size == 1)
    {
        dest.setTail(head);
    }
    // Size > 1 -> all other cases to copy all nodes to new array
    else if (source.size > 1)
    {
        //Node to add to the destination array
        Node<T>* temp = dest.getHead();

        //Node to traverse the source array
        Node<T>* sourceTemp = source.getHead()->next;

        while(sourceTemp != nullptr)
        {
            //Node to add to list
            Node<T>* inserted = new Node<T>(sourceTemp->data);

            //Sort all pointers with new node
            temp->next = inserted;
            inserted->previous = temp;
            sourceTemp = sourceTemp->next;
            temp = temp->next;
        }

        //Sets the tail to the last node of the destination list
        dest.setTail(temp);
    }

}


/**
 * insert(Node* next, T data)
 *
 * Adds a Node containing the data before the next Node. This function
 * is private, and will be used with the insert(int index, T data) function.
 *
 * @param next : a pointer to a node that will be "pushed over" to the
 *               next index, and will be after the new inserted Node
 * @param data : The data that will be added to the list within a Node
 */
template<class T>
void LinkedList<T>::insert(Node<T>* next, T data)
{
    Node<T>* previous = next->previous;     //gets the node before "next"
    //for easier pointer snafu

    Node<T>* addedNode = new Node<T>(data); //Node to insert

    if(previous != nullptr)                 //If previous = nullptr, then
    {                                       //the node is the head of the list
        previous->next = addedNode;
        addedNode->previous = previous;
    }

    addedNode->next = next;                 //Because of the logic for insert()
    next->previous = addedNode;             //there will always be a node after
    //the added node

    if(next == head)                        //if next is the beginning of list
    {                                       //then the added Node will be head
        head = addedNode;
    }

    size++;
}


/**
 * cycle(int index)
 *
 * Returns the Node at the index given. The function will cycle to the index
 * Node from either the head or tail of the list, depending on the
 * location of the index compared to the size of the list.
 *
 * @param index : the index Node from the list to return
 * @exception out_of_range : if the index is greater than the last index or
 *                           less than 0
 *
 */
template<class T>
Node<T>*LinkedList<T>::cycle(int index) const
{

    //Throw an exception if the index is not within the list
    if(index < 0 || index >= size)
    {
        throw std::out_of_range("Index out of bounds");
    }

    //Current node comes from either the head or tail depending on index
    Node<T>* current = (index < size / 2) ? head : tail;

    if(current == head)                      //cycle from the front
        for(int i{}; i < index; i++)
            current = current->next;
    else                                     //cycle from back
        for(int i{size-1}; i > index; i--)
            current = current->previous;

    return current;
}


//Constructors / Rule of 3

/**
 * Default Constructor
 */
template<class T>
LinkedList<T>::LinkedList() :size{0}, head{nullptr}, tail{nullptr}{}

/**
 * Copy constructor
 *
 * @param list : a const list reference to copy data into this list
 */
template<class T>
LinkedList<T>::LinkedList(const LinkedList& list)
    : size{list.size}, head{nullptr}, tail{nullptr}
{
    listCopy(*this, list);
}

/**
 * Copy assignment operator
 *
 * @param list : a const list reference to copy data into this list
 */
template<class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& list)
{
    clear();            //deletes all data in the list
    listCopy(*this, list);
    size = list.size;
    return *this;
}

/**
 * Destructor
 */
template<class T>
LinkedList<T>::~LinkedList()
{
    clear();
    head = nullptr;
    tail = nullptr;
}


//Capacity

/**
 * empty()
 *
 * @return true if list is empty and size is 0, false if not
 */
template<class T>
bool LinkedList<T>::empty()
{
    return size == 0;
}

/**
 * length()
 *
 * @return the size of the list
 */
template<class T>
int LinkedList<T>::length() const
{
    return size;
}


//Accessor functions

/**
 * front()
 *
 * Returns the first element of the array
 *
 * @return the data in the first Node of the array
 * @exception out_of_range if there are no elements in the array
 */
template<class T>
T& LinkedList<T>::front()
{
    if(head == nullptr)
        throw std::out_of_range("LinkedList<T>::front() - head is nullptr");
    return head->data;
}


/**
 * get()
 *
 * Returns the data within the Node at the index of the list
 *
 * @param index : an integer index referencing a Node within the list
 * @return the data within the index Node
 * @exception out_of_range if the index is not within [0, size)
 */
template<class T>
T LinkedList<T>::get(int index) const
{
    return (cycle(index)->data);
}

/**
 * back()
 *
 * Returns the last element of the array
 *
 * @return the data in the last Node of the array
 * @exception out_of_range if there are no elements in the array
 */
template<class T>
T& LinkedList<T>::back()
{
    if(tail == nullptr)
        throw("LinkedList<T>::back() - head is nullptr");
    return tail->data;
}

/**
 * find(T data)
 *
 * Looks for the first instance of (T data) within the list, and returns
 * the index where the data resides
 *
 * @param data : the data payload to search for within the list
 * @return the index where data is within the list. -1 if not found
 */
template<class T>
int LinkedList<T>::find(T data)
{
    Node<T>* current = head;

    for(int i{}; i < size; i++)
    {
        if(data == current->data)
            return i;
        current = current->next;
    }

    return -1;
}


/**
 * getDataPointer(index)
 *
 * @return a pointer to the node at the given index
 */
template<class T>
T* LinkedList<T>::getDataPointer(int index)
{
    return &(cycle(index)->data);
}


//Modifier functions

/**
 * insert(int index, T data)
 *
 * Inserts a Node containing (T data) into the list at the index specified.
 * The function uses the pushBack() function if the index is the same as
 * the size of the list, but otherwise will call a private function
 * that will insert the Node into the list.
 *
 * @param index : the index where the Node and data will be in the list
 * @param data : the data to be added to the list within the Node
 * @exception out_of_range if index is not within [0, size]
 */
template<class T>
void LinkedList<T>::insert(int index, T data)
{
    if(index == size)
        pushBack(data);
    else
        insert(cycle(index), data);
}

/**
 * pushFront(T data)
 *
 * Adds element to the front of the list
 *
 * @param data : the data to add to the list within a new Node
 */
template<class T>
void LinkedList<T>::pushFront(T data)
{
    insert(0, data);
}


/**
 * pushBack(T data)
 *
 * Inserts an element to the end of the list. Because the insert function
 * only works with indices between [0, size-1], pushBack essentially
 * replicates an insert function for an index = size.
 *
 * @param data : data to be inserted into a Node at the end of the list
 *
 */
template<class T>
void LinkedList<T>::pushBack(T data)
{
    Node<T>* temp = new Node<T>(data);
    if(tail != nullptr)         //If list is empty
    {
        tail->next = temp;      //sets the new Node to the end of the array
        temp->previous = tail;
    }
    else                        //If tail is nullptr, then the list is empty
    {
        head = temp;
    }

    tail = temp;

    size++;
}

/**
 * assign(int index, T data)
 *
 * Changes the data of the index Node to the data given by the client.
 *
 * @param data : the new data for the index Node to hold
 * @param index : the index of the Node to put the data into
 * @exception out_of_range if the index is not within [0, size-1]
 */
template<class T>
void LinkedList<T>::assign(int index, T data)
{
    Node<T>* current = cycle(index);
    current->data = data;
}

/**
 * uniquePushBack(data)
 *
 * This function is the same as pushBack, except that it checks each element
 * in the list to determine whether the data given already exists.
 *
 * If it does, the index where the data already exists will be returned and
 * the new data will not be added to the list. Otherwise, the data will be
 * added to the end of the list and the index returned will be equal to the
 * new size of the list - 1.
 *
 * @param data - the data to add to the list if it doesn't already exist within
 *               the list
 * @return an integer index where the data exists within the list
 */
template<class T>
int LinkedList<T>::uniquePushBack(T data)
{
    Node<T>* current = head;
    for(int i{}; i < size; i++)
    {
        if(data == current->data)
            return i;
        current = current->next;
    }
    pushBack(data);
    return size-1;
}


//Removal Functions

/**
 * remove(int index)
 *
 * Removes a node from the list at index given by the client, and returns
 * the data that was in that Node.
 *
 * @param index : the index where a Node should be removed
 * @exception out_of_range if the index is not within [0, size-1]
 * @return the data from the removed Node
 */
template<class T>
T LinkedList<T>::remove(int index)
{
    //Pulls three nodes to make sure that all pointers are correct
    Node<T>* current = cycle(index);        //will cause exception if size=0
    Node<T>* before = current->previous;
    Node<T>* after = current->next;


    //Both conditions account for edge cases, but the combination of these
    //two statements also accounts for cases where Nodes are in the middle
    if(before != nullptr)               //start of the list
    {
        before->next = after;
        current->previous = nullptr;
    }
    if(after != nullptr)                //end of the list
    {
        after->previous = before;
        current->next = nullptr;
    }


    if(head == current)                 //checks if the head or tail must adjust
    {
        head = after;
    }
    if(tail == current)
    {
        tail = before;
    }

    T returnData = current->data;       //get data to return
    delete current;
    size--;
    return returnData;
}

/**
 * popFront()
 *
 * Removes the Node at the beginning of the array, and returns the data
 * that was at the head of the list
 *
 * @exception out_of_range if the list is empty
 * @return the data at the former head of the list
 */
template<class T>
T LinkedList<T>::popFront()
{
    return remove(0);
}

/**
 * popBack()
 *
 * Removes the Node at the end of the array, and returns the data
 * that was at the tail of the list
 *
 * @exception out_of_range if the list is empty
 * @return the data at the former head of the list
 */
template<class T>
T LinkedList<T>::popBack()
{
    return remove(size-1);
}

/**
 * resize(int size, T val)
 *
 * Resizes the array to the client-given size.
 * There are two cases for this function, given that size is valid (size > 0)
 * (1) : If the given size is less than the list size, then Nodes from the back
 *       will be deleted until the sizes are equal
 * (2) : If the given size is greater than the list size, then new Nodes that
 *       contain (val) will be inserted at the end of the list until the
 *       size requirement is met.
 *
 * @param size : the new size of the list
 * @param val : the data to be inserted with Nodes if: given size > list size
 * @exception out_of_range if the given size is < 0
 */
template<class T>
void LinkedList<T>::resize(int size, T val)
{

    if(size < 0)
        throw std::out_of_range("resize(): negative index is not allowed");

    if(size < this->size)               //Removes Nodes from the end
    {
        while(this->size != size)
            popBack();
    }
    else if(size > this->size)          //Adds nodes with val at the end
    {
        while(size != this->size)
            pushBack(val);
    }
}

/**
 * clear()
 *
 * Deletes all elements of the array using the popFront() function.
 *
 */
template<class T>
void LinkedList<T>::clear()
{
    while(size != 0)
        popFront();
}

/**
 * operator[] (int index)
 *
 * @return a reference to the data within the index Node
 *
 * This function is different from get(index), which simply returns the
 * data within the list. This function returns a REFERENCE so data can
 * be manipulated within the list.
 *
 */
template<class T>
T& LinkedList<T>::operator[](int index)
{
    return cycle(index)->data;
}


// Getters and setters

/**
 * getHead()
 *
 * Returns a pointer to the head of the list
 */
template<class T>
Node<T>* LinkedList<T>::getHead() const
{
    return head;
}

/**
 * setHead()
 *
 * Sets the head of the list to a new pointer
 */
template<class T>
void LinkedList<T>::setHead(Node<T>* value)
{
    head = value;
}

/**
 * getTail()
 *
 * Returns a pointer to the end (tail) of the list
 */
template<class T>
Node<T>* LinkedList<T>::getTail() const
{
    return tail;
}

/**
 * setTail()
 *
 * Sets the end/tail of the list to a new pointer
 */
template<class T>
void LinkedList<T>::setTail(Node<T>* value)
{
    tail = value;
}

/**
 * operator<<(std::ostream& o, const LinkedList& list)
 *
 * Returns an ostream& reference containing output for the LinkedList.
 *
 * Example output:
 *
 * [1 2 3 4 5 ]
 *
 * @param o : the ostream reference to return, containing output for the list
 * @param list : a constant reference to a LinkedList that will be outputted
 *               using the ostream& o
 * @return an ostream& o that can be used to output the contents of the list
 */
template<class S>
std::ostream& operator<<(std::ostream& o, const LinkedList<S>& list)
{
    Node<S>* temp = list.head;
    o << "[";

    if(list.head == nullptr)
    {
        return o;
    }
    else
    {
        o << temp->getData();

        while(temp->getNext() != nullptr)
        {
            temp = temp->getNext();
            o << ", " << temp->getData();
        }

    }
    o << "]";
    return o;

}

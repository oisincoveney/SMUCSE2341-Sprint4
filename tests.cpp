#include <catch.hpp>
#include <linkedlist.h>
#include <stack.h>
#include <queue.h>

using namespace std;

template<class T>
void reset(LinkedList<T>& list)
{
    list.clear();
    for(int i{0}; i < 25; i++)
    {
        list.pushBack(i);
    }

}


TEST_CASE("LinkedList", "[LinkedList]")
{
    LinkedList<int> list;
    reset(list);

    SECTION("Constructors and assignment operators")
    {
        LinkedList<int> copy = list;
        LinkedList<int> copy2(list);

        for(int i{}; i < list.length(); i++)
        {
            REQUIRE(list.get(i) == copy.get(i));
            REQUIRE(copy.get(i) == copy2.get(i));
        }
    }

    SECTION("Element access")
    {
        SECTION("front() - access front element")
        {
            REQUIRE(list.front() == 0);
        }

        SECTION("back() - access back element")
        {
            REQUIRE(list.back() == 24);
        }

        SECTION("get() - access mid-list elements")
        {
            REQUIRE(list.get(3) == 3);
            REQUIRE(list.get(7) == 7);
            REQUIRE(list.get(21) == 21);
        }
        SECTION("operator[] - access element data by reference")
        {
            for(int i{}; i < list.length(); i++)
            {
                REQUIRE(list[i] == i);
                list[i] = 0;
                REQUIRE(list[i] == 0);
            }
        }
    }

    SECTION("Modifiers")
    {
        SECTION("Insert - adding elements at beginning")
        {

            for(int i{}; i < 3; i++)
            {
                list.insert(0, 3000000);
            }

            REQUIRE(list.get(0) == 3000000);
            REQUIRE(list.get(1) == 3000000);
            REQUIRE(list.get(2) == 3000000);
            REQUIRE(list.get(3) == 0);
        }

        SECTION("Insert - adding elements in middle")
        {

            for(int i{}; i < 3; i++)
            {
                list.insert(i+1, 3000000);
            }


            REQUIRE(list.get(0) == 0);
            REQUIRE(list.get(1) == 3000000);
            REQUIRE(list.get(2) == 3000000);
            REQUIRE(list.get(3) == 3000000);
        }

        SECTION("Insert - adding elements at end")
        {

            for(int i{}; i < 3; i++)
            {
                list.insert(list.length(), 3000000);
            }


            REQUIRE(list.get(list.length() - 1) == 3000000);
            REQUIRE(list.get(list.length() - 2) == 3000000);
            REQUIRE(list.get(list.length() - 3) == 3000000);
            REQUIRE(list.get(list.length() - 4) == 24);
        }

        SECTION("pushFront - adding elements at beginning")
        {

            for(int i{}; i < 3; i++)
            {
                list.pushFront(3000000);
            }


            REQUIRE(list.get(0) == 3000000);
            REQUIRE(list.get(1) == 3000000);
            REQUIRE(list.get(2) == 3000000);
            REQUIRE(list.get(3) == 0);

            list.clear();

            for(int i{}; i < 15; i++)
            {
                list.pushFront(14-i);
            }
            for(int i{}; i < 15; i++)
            {
                REQUIRE(list[i] == i);
            }
        }

        SECTION("pushBack - adding elements at end")
        {

            for(int i{}; i < 3; i++)
            {
                list.pushBack(3000000);
            }


            REQUIRE(list.get(list.length() - 1) == 3000000);
            REQUIRE(list.get(list.length() - 2) == 3000000);
            REQUIRE(list.get(list.length() - 3) == 3000000);
            REQUIRE(list.get(list.length() - 4) == 24);

            list.clear();

            for(int i{}; i < 15; i++)
            {
                list.pushBack(i);
            }
            for(int i{}; i < 15; i++)
            {
                REQUIRE(list[i] == i);
            }
        }

        SECTION("assign - setter for elements")
        {

            for(int i{}; i < list.length(); i++)
            {
                list.assign(i, 0);
            }


            REQUIRE(list.get(15) == 0);
            REQUIRE(list.get(list.length() - 1) == 0);
            REQUIRE(list.get(2) == 0);
        }
    }

    SECTION("Removing elements")
    {
        SECTION("remove() at beginning of list")
        {
            while(list.length() != 20)
                list.remove(0);

            REQUIRE(list.get(0) == 5);
            REQUIRE(list.get(10) == 15);
            REQUIRE(list.get(19) == 24);
        }
        SECTION("remove() in the middle of list")
        {
            while(list.length() != 4)
                list.remove(2);

            REQUIRE(list.get(0) == 0);
            REQUIRE(list.get(1) == 1);
            REQUIRE(list.get(2) == 23);
        }
        SECTION("remove() at end of list")
        {
            // Removal at end of list
            while(list.length() != 0)
                list.remove(list.length() - 1);

            list.length();
            REQUIRE(list.empty());

        }

        SECTION("popFront() - removal at beginning of list")
        {
            for(int i{}; i < 10; i++)
                list.popFront();

            REQUIRE(list.get(0) == 10);
            REQUIRE(list.get(5) == 15);
            REQUIRE(list.get(list.length()-1) == 24);
        }
        SECTION("popBack() - removal at end of list")
        {
            for(int i{}; i < 10; i++)
                list.popBack();

            REQUIRE(list.get(4) == 4);
            REQUIRE(list.get(2) == 2);
        }

        SECTION("resize() - resizing the linked list")
        {
            list.resize(3, 0);
            REQUIRE(list.length() == 3);
            REQUIRE(list.back() == 2);

            list.resize(50, 0);
            REQUIRE(list.length() == 50);
            REQUIRE(list.get(25) == 0);

            list.resize(0, 0);
            REQUIRE(list.empty());

            list.clear();

            REQUIRE(list.empty());

        }
    }

}

TEST_CASE("Stack", "[Stack]")
{
    Stack<int> st;

    for(int i{}; i < 10; i++)
    {
        st.push(i);
    }
    SECTION("pop()")
    {
        int x;
        while(!st.isEmpty())
        {
            x = st.pop();
        }
        REQUIRE(x == 0);
    }

    SECTION("peek()")
    {
        REQUIRE(st.peek() == 9);
    }

    SECTION("push()")
    {
        for(int i{}; i < 20; i++)
            st.push(i);
        REQUIRE(st.peek() == 19);
        st.pop();
        REQUIRE(st.peek() == 18);
    }

    SECTION("empty()")
    {
        REQUIRE(!st.isEmpty());
        while(!st.isEmpty())
            st.pop();
        REQUIRE(st.isEmpty());
    }
}

TEST_CASE("Queue", "[Queue]")
{
    Queue<int> qu;

    for(int i{}; i < 10; i++)
    {
        qu.enqueue(i);
    }

    SECTION("dequeue()")
    {
        int x;
        while(!qu.isEmpty())
        {
            x = qu.dequeue();
        }
        REQUIRE(x == 9);
    }

    SECTION("peek()")
    {
        REQUIRE(qu.peek() == 0);
    }

    SECTION("enqueue()")
    {
        for(int i{}; i < 20; i++)
            qu.enqueue(i);
        REQUIRE(qu.peek() == 0);
        qu.dequeue();
        REQUIRE(qu.peek() == 1);
    }

    SECTION("empty()")
    {
        REQUIRE(!qu.isEmpty());
        while(!qu.isEmpty())
            qu.dequeue();
        REQUIRE(qu.isEmpty());
    }
}

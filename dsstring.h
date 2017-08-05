#pragma once

#ifndef String_H
#define String_H

#include <iostream>
#include <fstream>


/**
 * The String class provides a custom implementation of the std::string class
 * to mainly be used in CSE 2341. Because this class is meant to replicate
 * the functions of the string class in the standard library,
 * this String class possesses many of the same functions that
 * the std::string class provides.
 *
 * The class is implemented through cstring manipulation, so the
 * the only two member variables are an array of characters and
 * the length of the array.
 *
*/

class String
{
    private:

        int length;
        char* arr;

    public:

        // Constructors, including copy constructors
        String();
        String(const char*);
        String(const String&);

        // operator= to satisfy the Rule of Three
        String& operator= (const String&);
        String& operator= (const char*);


        // Size functions
        int size() const;
        void clear();       //resets the array to a length of 0
        bool empty();       //returns whether length is 0


        // accessor functions:
        // both functions do exactly the same thing with
        // different syntax
        char& operator[] (int index);
        char& at(int index);

        // Returns the character array that is the base of the class
        const char* c_str() const;

        // Index functions - finds the character with option to
        // begin from a certain index
        int find(char c, int pos = 0);
        int rfind(char c, int pos = 0);

        // Substring - returns a partial string based on index
        String substring(int pos = 0, int len = -1);

        // Compare function - uses cstring strcmp() to determine the returned int
        int compare(const String& str) const;

        // Comparison operators use the compare function to return a result
        bool operator== (const String& rhs) const;
        bool operator!= (const String& rhs) const;
        bool operator<  (const String& rhs) const;
        bool operator>  (const String& rhs) const;

        //Addition operator
        String operator+ (const String& rhs);

        // ostream and istream functions to handle file i/o
        friend std::istream& getline (std::istream&  is, String& str);
        friend std::ifstream& getline (std::ifstream&  is, String& str);
        friend std::istream& getline (std::istream&  is, String& str, char delim);
        friend std::ifstream& getline (std::ifstream&  is, String& str, char delim);

        // operator<< and operator>> overloads that
        // use the corresponding cstring operators
        friend std::istream& operator>> (std::istream& is, String& str);
        friend std::ifstream& operator>> (std::ifstream& is, String& str);
        friend std::ostream& operator<< (std::ostream& o, const String& str);

        //destructor to handle the deallocation of the char array
        ~String();
};  //end class String


#endif // String_H

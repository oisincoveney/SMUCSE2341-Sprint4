#include "dsstring.h"
#include <cstring>



/**
 * Default constructor for the String
 */
String::String() : length{0}, arr{new char[length+1]} {}


/**
 * Constructor using const char array to get data
 */
String::String(const char* c) : length{static_cast<int>(strlen(c))}, arr{new char[length+1]}
{
    strcpy(arr, c); //uses strcpy from cstring to copy
}

/**
 * Copy constructor
 *
 * @param s - String to copy information from
 */
String::String(const String& s) : length{static_cast<int>(strlen(s.c_str()))}, arr{new char[length+1]}
{
    const char* ptr = s.c_str();
    strcpy(arr, ptr);
}


/**
 * Copy assignment operator
 *
 * @param s - String to copy information from
 * @return *this - a reference to this String with the new data
 */
String& String::operator= (const String& s)
{
    delete[] arr;

    length = s.length;
    const char* ptr = s.c_str();
    arr = new char[length+1];

    strcpy(arr, ptr);

    return *this;
}

/**
 * Assignment operators
 *
 * @param c - a character array that reflects the data that will be
 *            in the String
 * @return *this - a reference to this String with the new data
 */
String& String::operator= (const char* c)
{
    delete[] arr;

    length = strlen(c);
    arr = new char[length + 1];

    strcpy(arr, c);

    return *this;
}


/**
 * @return an integer containing the length of the string
 */
int String::size() const
{
    return length;
}

/**
 * Deletes the array and resets all variables to their original state
 */
void String::clear()
{
    delete[] arr;
    length = 0;
    arr = new char[length];
}

/**
 * @return true if string is empty, false if not
 */
bool String::empty()
{
    return length == 0;
}

/**
 * Access operator
 *
 * @param index of data to return
 * @return a reference to the character in the data array
 */
char&String::operator[](int index)
{
    int i = index < 0 ? length + index : index;
    return arr[i];
}

/**
 * Access function
 *
 * @param index of data to return
 * @return a reference to the character in the data array
 */
char&String::at(int index)
{
    int i = index < 0 ? length + index : index;
    return arr[i];
}


/**
 * @return a constant character array
 */
const char*String::c_str() const
{
    return arr;
}

/**
 * Finds the position of the character within the String
 *
 * @param c - the character to find
 * @param pos - the index to start at, defaults to 0
 * @return the index of the instance of the character, or -1 if not found
 */
int String::find(char c, int pos)
{
    using namespace std;
    for(int i{pos}; i < length; i++)
    {
        if(c == arr[i])
            return i;
    }
    return -1;
}


/**
 * Finds the position of the character, starting from the last index
 *
 * @param c - the character to find
 * @param pos - the position to start with, defaults to -1
 * @return the index of the instance of the character, or -1 if not found
 */
int String::rfind(char c, int pos)
{
    using namespace std;
    for(int i{length-1}; i >= pos; i--)
    {
        if(c == arr[i])
            return i;
    }
    return -1;
}


/**
 * Returns a partial string based on the start and end index given
 *
 * @param start - the beginning index, defaults at 0
 * @param end - the end index, defaults at -1
 * @return a String containing the partial cstring based on index
 */
String String::substring(int start, int end)
{
    int s = start < 0 ? length + start +1: start;
    int e = end < 0 ? length + end +1 : end;

    //Throws an error if the indexes cannot be used
    if(e < s)
        throw std::logic_error("end index is greater than start index in substring");

    int subLength = e-s;                //create new array to contain the partial string
    char c[subLength+1]{};

    for(int i{}; i < subLength; i++)
    {
        c[i] = arr[s+i];
    }
    c[subLength] = '\0';

    return String(c);
}


/**
 * Compare function that uses the cstring compare function to compare
 * the String objects
 *
 * @param str - a constant String reference to compare this String with
 * @return the value returned by the cstring comparison function
 */
int String::compare(const String& str) const
{
    return strcmp(arr, str.c_str());
}

/**
 * Equality operator
 *
 * @param rhs - the String to compare to
 * @return true if compare == 0, false otherwise
 */
bool String::operator== (const String& rhs) const
{
    return this->compare(rhs) == 0;
}

/**
 * Inequality operator
 *
 * @param rhs - the String to compare to
 * @return false if compare == 0, true otherwise
 */
bool String::operator!=(const String& rhs) const
{
    return this->compare(rhs) != 0;
}

/**
 * Less than - operator
 *
 * @param rhs - the String to compare to
 * @return true if compare < 0, false otherwise
 */
bool String::operator< (const String& rhs) const
{
    return this->compare(rhs) < 0;
}


/**
 * Greater than operator
 *
 * @param rhs - the String to compare to
 * @return true if compare > 0, false otherwise
 */
bool String::operator> (const String& rhs) const
{
    return this->compare(rhs) > 0;
}

/**
 * Addition operator
 *
 * Concatenates the String that calls this function with the rhs string.
 *
 * @param rhs - the string to add to "this" String object
 * @return a String concatenation of the String objects "this" & "rhs"
 */
String String::operator+(const String& rhs)
{
    int nLength = rhs.length + length;
    char nString[nLength+1];
    strcpy(nString, arr);
    strcat(nString, rhs.c_str());
    return String(nString);
}


/**
 * ISTREAM
 * getline(delim) retrieves the characters of a file up to the delimiting
 * character specified by the user. The group of characters are placed
 * into the referenced String
 *
 * This function will read the delimiting character within the ifstream&,
 * but will not append it to the String.
 *
 *
 * @param is - the istream to pull data from
 * @param str - the String to place data into
 * @param delim - the character to stop character retrieval at
 * @return the istream reference originally entered as a parameter
 */
std::istream& getline(std::istream& is, String& str, char delim)
{
    if(!is.eof())
    {
        char c_string[256];
        is.getline(c_string, 256, delim);
        str = c_string;
    }
    else
    {
        is.clear();
    }
    return is;
}


/**
 * IFSTREAM
 * getline(delim) retrieves the characters of a file up to the delimiting
 * character specified by the user. The group of characters are placed
 * into the referenced String
 *
 * This function will read the delimiting character within the ifstream&,
 * but will not append it to the String.
 *
 * @param is - the istream to pull data from
 * @param str - the String to place data into
 * @param delim - the character to stop character retrieval at
 * @return the istream reference originally entered as a parameter
 */
std::ifstream& getline(std::ifstream& is, String& str, char delim)
{
    if(!is.eof())
    {
        char c_string[256];
        is.getline(c_string, 256, delim);
        str = c_string;
    }
    else
    {
        is.clear();
    }
    return is;
}

/**
 * ISTREAM
 * getline() uses an istream to find the next line of the file
 * and places the data into the referenced String
 *
 * @param is - the istream to pull data from
 * @param str - the String to place data into
 * @return the istream reference originally entered as a parameter
 */
std::istream& getline(std::istream& is, String& str)
{

    if(!is.eof())
    {
        char c_string[256];
        is.getline(c_string, 256);
        str = c_string;
    }
    else
    {
        is.clear();
    }
    return is;

}

/**
 * IFSTREAM
 * getline() uses an istream to find the next line of the file
 * and places the data into the referenced String
 *
 * @param is - the istream to pull data from
 * @param str - the String to place data into
 * @return the istream reference originally entered as a parameter
 */
std::ifstream& getline(std::ifstream& is, String& str)
{

    if(!is.eof())                   //checks if there is more data
    {
        char c_string[256];
        is.getline(c_string, 256);
        str = c_string;
    }
    else                            //otherwise nothing should be added
        is.clear();
    return is;

}

/**
 * getline() uses an ifstream to find the next line of the file
 * and places the data into the referenced String
 *
 * @param is - the ifstream to pull data from
 * @param str - the String to place data into
 * @return the ifstream reference originally entered as a parameter
 */
std::ifstream& operator>>(std::ifstream& is, String& str)
{
    if(!is.eof())                     //checks if there is more data
    {
        char c_string[256];
        is.getline(c_string, 256);
        str = c_string;
    }
    else                              //otherwise nothing should be added
    {
        is.clear();
    }
    return is;
}


/**
 * operator>> retrieves the next char* bounded by delimiting characters,
 * including spaces, tabs, or new lines.
 *
 * @param is - the istream to retrieve data
 * @param str - the String to place data into
 * @return istream that was originally passed into the function
 */
std::istream& operator>>(std::istream& is, String& str)
{
    char c_string[256];
    is  >> c_string;
    str = c_string;

    return is;
}

/**
 * operator<< overloads the stream insertion operator to be used with the
 * custom String class.
 *
 * @param o - ostream to insert data into
 * @param str - the String to put data into ostream
 * @return the ostream that was originally passed into the function
 */
std::ostream& operator<<(std::ostream& o, const String& str)
{
    if(str.length != 0)
        o << str.arr;
    return o;
}

/**
 * Destructor
 */
String::~String()
{
    if(arr != nullptr)
    {
        delete[] arr;
    }
}

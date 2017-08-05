#include "request.h"

/**
 * Default constructor
 */
Request::Request() : origin{}, destination{}, timeTag{true}{}


/**
 * Constructor with String, String, bool
 * @param orig - a String containing the origin city
 * @param dest - a String containing the destination city
 * @param timeTag - a boolean determining how the flight list will be ordered.
 *                (true if sorted by time, false if sorted by cost)
 */
Request::Request(String orig, String dest, bool timeTag)
    : origin{orig}, destination{dest}, timeTag{timeTag}{}

/**
 * Copy constructor
 * @param other - the Request object to copy data from
 */
Request::Request(const Request& other) : origin{other.getOrigin()},
    destination{other.getDestination()}, timeTag{other.getTimeTag()} {}

/**
 * operator= overload (to satisfy Rule of 3)
 * @param other - the Request object to copy data from
 * @return reference to a Request object containing the data from Request& other
 */
Request& Request::operator=(const Request& other)
{
    origin = other.getOrigin();
    destination = other.getDestination();
    timeTag = other.getTimeTag ();
    return *this;
}

/**
 * getOrigin()
 *
 * @return a String containing the origin of the journey
 */
String Request::getOrigin() const
{
    return origin;
}

/**
 * setOrigin(value)
 *
 * @param value - the String to set the origin city to
 */
void Request::setOrigin(const String& value)
{
    origin = value;
}

/**
 * getDestination()
 *
 * @return the destination String of the Request
 */
String Request::getDestination() const
{
    return destination;
}

/**
 * setDestination(value)
 *
 * @param value - the new Destination for the Request
 */
void Request::setDestination(const String& value)
{
    destination = value;
}

/**
 * getTimeTag()
 *
 * @return - the tag that determines how the final flight list will be ordered
 */
bool Request::getTimeTag() const
{
    return timeTag;
}

/**
 * setTimeTag(value)
 *
 * @param value - a boolean determining how the flight list will be ordered.
 *                (true if sorted by time, false if sorted by cost)
 */
void Request::setTimeTag(bool value)
{
    timeTag = value;
}

/**
 * operator<< overload
 * (Note: std::right, std::left, and std::setw are used for formatting)
 *
 * Example Output:
 *
 * Sandgap -> Madison Park             R: Cost
 *
 * @param o - the ostream reference to add data to
 * @param r - the Request object to pull data from
 * @return the ostream reference containing the new data from Request& r
 */
std::ostream& operator<<(std::ostream& o, const Request& r)
{
    o << std::right;
    o << std::setw(25) << r.getOrigin() << " -> ";
    o << std::left;
    o << std::setw(25) << r.getDestination();
    o << "\tR:" << r.getTimeTag();
    return o;
}

#include <city.h>


/* City Functions */

/**
 * Default Constructor
 */
City::City() : name{} {}

/**
 * Constructor with name parameter
 * @param name - the name to set the city to
 */
City::City(String name) : name{name} {}

/**
 * Operator== overload
 * @param rhs - the city reference to compare this City to
 * @return true if the names of each city are equal, false if not
 */
bool City::operator==(const City& rhs)
{
    return (name == rhs.name);
}

/**
 * Operator!= overload
 * @param rhs - the city reference to compare this City to
 * @return false if the names of each city are equal, true if not
 */
bool City::operator!=(const City& rhs)
{
    return !(this->getName() == rhs.getName());
}

/**
 * getName()
 *
 * @return name of the city
 */
String City::getName() const
{
    return name;
}

/**
 * setName(const String& value)
 *
 * @param value - the value to set the name of the city to
 */
void City::setName(const String& value)
{
    name = value;
}


/**
 * operator << overload
 * @param o - the ostream reference to add data to
 * @param city - the city whose data will be added to the ostream
 * @return the ostream reference, now containing the data from city
 */
std::ostream& operator<<(std::ostream& o, const City& city)
{
    o << city.name;
    return o;
}


/* Origin Functions */

/**
 * Default constructor
 */
Origin::Origin() : City(), cost{}, duration{}, destinations{} {}

/**
 * Constructor with String
 * @param cityName - the String to name the Origin city with
 */
Origin::Origin(String cityName) : City(cityName), cost{}, duration{}, destinations{} {}

/**
 * Copy constructor
 * @param other - the Origin reference to copy objects from
 */
Origin::Origin(const Origin& other) : City(other.getName()), cost{other.cost},
    duration{other.duration}, destinations{other.destinations} {}

/**
 * Operator= overload (to satisfy Rule of 3)
 * @param other - the Origin reference to copy objects from
 * @return a reference to this Origin object, containing the new data
 */
Origin& Origin::operator=(const Origin& other)
{
    name = other.name;
    destinations = other.destinations;
    cost = other.cost;
    duration = other.duration;
    return *this;
}

/**
 * getDuration
 * @return the duration of the flight to the next destination
 */
int Origin::getDuration() const
{
    return duration;
}

/**
 * setDuration(value)
 * @param value - the value to set the duration to
 */
void Origin::setDuration(int value)
{
    duration = value;
}

/**
 * getCost
 * @return the cost of the flight to the next destination
 */
double Origin::getCost() const
{
    return cost;
}

/**
 * setCost(value)
 * @param value - the value to set the cost to
 */
void Origin::setCost(double value)
{
    cost = value;
}

/**
 * getDestinations()
 *
 * This getter returns a reference to the list, so it can be modified or
 * accessed in any way.
 *
 * @return - a reference to the destination list
 */
LinkedList<Destination>& Origin::getDestinations()
{
    return destinations;
}

/**
 * getDestinations() const
 *
 * @return the list of destinations
 */
LinkedList<Destination> Origin::getDestinations() const
{
    return destinations;
}

/**
 * setDestinations(value)
 * @param value - the value to set the destinations list to
 */
void Origin::setDestinations(const LinkedList<Destination>& value)
{
    destinations = value;
}


/**
 * Operator<< overload
 * @param o - the ostream reference to place data from the Origin city into
 * @param orig - the Origin reference to pull data from
 * @return an ostream reference containing data from the Origin reference
 */
std::ostream& operator<<(std::ostream& o, const Origin& orig)
{
    o << orig.getName() << "\tNext destination: $";
    o << orig.cost << "\t" << orig.duration << " min\n";

    //Gets the destinations within the object
    for(int i{}; i < orig.destinations.length(); i++)
    {
        o << "\n\t -> " << orig.destinations.get(i).getName();
    }
    return o;
}


/* Destination Functions */

/**
 * Copy constructor
 * @param other - the data to copy from
 */
Destination::Destination(const Destination& other) :
    City(other.getName()), cost{other.cost}, duration{other.duration},
    originPtr{other.getOriginPtr()}, visited{other.visited} {}

/**
 * operator= overload (to satisfy Rule of 3)
 * @param other - the data to copy from
 * @return a reference to this Destination object containing the new data
 */
Destination& Destination::operator=(const Destination& other)
{
    name = other.getName();
    cost = other.getCost();
    duration = other.getDuration();
    originPtr = other.getOriginPtr();
    visited = other.getVisited();
    return *this;
}

/**
 * Constructor with String, int, int
 * @param cityName - the name of the Destination
 * @param cost - the cost to fly to the Destination from the Origin city
 * @param duration - the duration to fly to the Destination from the Origin city
 */
Destination::Destination(String cityName, double cost, int duration)
    : City(cityName), cost{cost}, duration{duration}, originPtr{nullptr}, visited{false} {}

/**
 * Constructor with String, int, int
 * @param cityName - the name of the Destination
 * @param cost - the cost to fly to the Destination from the Origin city
 * @param duration - the duration to fly to the Destination from the Origin city
 * @param ptr - the pointer to the Origin city object with the same name
 */
Destination::Destination(String cityName, double cost, int duration, Origin* ptr)
    : City(cityName), cost{cost}, duration{duration}, originPtr{ptr}, visited{false}{}

/**
 * getCost()
 * @return - the cost of to travel from the Origin holding this object
 */
double Destination::getCost() const
{
    return cost;
}

/**
 * setCost(value)
 * @param value - the value to set the cost to
 */
void Destination::setCost(double value)
{
    cost = value;
}

/**
 * getDuration()
 * @return - the time to travel from the Origin holding this object
 */
int Destination::getDuration() const
{
    return duration;
}

/**
 * setDuration(value)
 * @param value - the value to set the duration to
 */
void Destination::setDuration(int value)
{
    duration = value;
}

/**
 * getOriginPtr()
 * @return - the pointer to the Origin object with the same name
 */
Origin* Destination::getOriginPtr() const
{
    return originPtr;
}

/**
 * setOriginPtr(value)
 * @param value-the Origin pointer containing the same name as this Destination
 */
void Destination::setOriginPtr(Origin* value)
{
    originPtr = value;
}

/**
 * getVisited()
 * @return true if the city has been marked as visited, false otherwise
 */
bool Destination::getVisited() const
{
    return visited;
}

/**
 * setVisited(value)
 * @param value - the value to set visited. Set true if visited, false if not
 */
void Destination::setVisited(bool value)
{
    visited = value;
}

/**
 * ostream operator<< overload
 * @param o - the ostream reference add data to
 * @param d - the Destination reference to pull data from
 * @return an ostream reference containing the data from Destination d
 */
std::ostream& operator<<(std::ostream& o, const Destination& d)
{
    o << d.getName();
    return o;
}

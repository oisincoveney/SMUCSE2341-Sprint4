#include "plan.h"


/**
 * Default constructor
 */
Plan::Plan(): origin{}, destination{}, connections{" -> "},
    totalDuration{0}, totalCost{0} {}

/**
 * Constructor with String, String
 * @param orig - the origin of the journey
 * @param dest - the destination of the journey
 */
Plan::Plan(String orig, String dest) : origin{orig}, destination{dest},
    connections{" -> "},totalDuration{0}, totalCost{0} {}

/**
 * Constructor with Stack<Origin>, String
 * @param stack - a stack containing the origin and connections of a journey
 * @param dest - the final destination of the journey
 */
Plan::Plan(Stack<Origin> stack, String dest) : origin{},
    destination{dest}, connections{" -> "},totalDuration{0}, totalCost{0}
{
    LinkedList<Origin> list{stack.readStack()};

    origin = list[0].getName();
    totalDuration += list[0].getDuration();
    totalCost += list[0].getCost();

    for(int i{1}; i < list.length(); i++)
    {
        Origin o{list[i]};
        addConnection(o.getName());
        totalDuration += o.getDuration();
        totalCost += o.getCost();
    }
}

/**
 * Copy constructor
 * @param other - the Plan object to copy data from
 */
Plan::Plan(const Plan& other) :
    origin{other.origin}, destination{other.destination},
    connections{other.connections}, totalDuration{other.totalDuration},
                                            totalCost{other.totalCost} {}

/**
 * operator= overload (to satisfy Rule of 3)
 * @param other - the Plan object to copy data from
 * @return reference to a Plan object containing the same data as Plan& other
 */
Plan& Plan::operator=(const Plan& other)
{
    origin = other.origin;
    destination = other.destination;
    connections = other.connections;
    totalDuration = other.totalDuration;
    totalCost = other.totalCost;
    return *this;
}

/**
 * addConnection(String)
 * Appends a connection to the connections String, and inserting a " -> " String
 * between the old and new connections for better formatting.
 *
 * @param connection - a String containing a new city to connect to
 */
void Plan::addConnection(String connection)
{
    connections = (connections + connection + " -> ");
}

/**
 * getTotalDuration()
 *
 * @return the total duration of the flight
 */
int Plan::getTotalDuration() const
{
    return totalDuration;
}

/**
 * setTotalDuration()
 *
 * @param value - the new integer duration to change totalDuration to
 */
void Plan::setTotalDuration(int value)
{
    totalDuration = value;
}

/**
 * getTotalCost()
 *
 * @return the total cost of the flight
 */
double Plan::getTotalCost() const
{
    return totalCost;
}

/**
 * setTotalCost(value)
 *
 * @param value - the new total cost of the flight
 */
void Plan::setTotalCost(double value)
{
    totalCost = value;
}

/**
 * getOrigin()
 *
 * @return the origin of the journey
 */
String Plan::getOrigin() const
{
    return origin;
}

/**
 * setOrigin(value)
 *
 * @param value - a new origin string to change the variable origin to
 */
void Plan::setOrigin(const String& value)
{
    origin = value;
}

/**
 * getDestination()
 *
 * @return a string containing the destination
 */
String Plan::getDestination() const
{
    return destination;
}

/**
 * setDestination(value)
 *
 * @param value - a new destination String to change the variable destination to
 */
void Plan::setDestination(const String& value)
{
    destination = value;
}

/**
 * getConnections()
 *
 * @return a String containing the connections between the origin & destination
 */
String Plan::getConnections() const
{
    return connections;
}

/**
 * setConnections(value)
 *
 * @param value - a String reference containing new connections
 */
void Plan::setConnections(const String& value)
{
    connections = value;
}

/**
 * operator<< overload
 * (Note: std::right, std::left, and std::setw are used for formatting)
 *
 * Example Output:
 *
 * Sandgap -> Madison Park -> Jamesville.  Time: 50  Cost: 43
 *
 * @param o - the ostream reference to add data to
 * @param plan - the Plan object to pull data from
 * @return the ostream reference containing the new data from Plan& plan
 */
std::ostream& operator<<(std::ostream& o, const Plan& plan)
{
    o << plan.getOrigin() << plan.getConnections();
    o << plan.getDestination() << ".";
    o << "  Time: " << plan.totalDuration;
    o << "  Cost: " << std::setprecision(2) << std::fixed << plan.totalCost << std::endl;
    return o;
}

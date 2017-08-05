#include "flightplans.h"

/**
 * Default constructor
 */
FlightPlans::FlightPlans() : plans{}, request{} {}

/**
 * Constructor with LinkedList<Plan> and Request
 * @param p - a linked list of plans that specify different ways of
 *            journeying from an origin and destination
 * @param r - the request, containing the user's choice of origin & destination
 */
FlightPlans::FlightPlans(LinkedList<Plan> p, Request r) : plans{p}, request{r}
{
    sort();
}

/**
 * Copy constructor
 * @param plans - the FlightPlans reference to copy data from
 */
FlightPlans::FlightPlans(const FlightPlans& plans)
    : plans{plans.getPlans()}, request{plans.getRequest()}{}

/**
 * Sorts the linked list of Plan objects using the checkByTag function,
 * which uses the tag within the Request object to determine how to
 * sort the list (either by duration or cost).
 *
 * The algorithm uses insertion sort, one of the faster sorting algorithms for
 * smaller sets of data, which the Flight Planner will presumably be used for
 * more often than for large sets of data.
 *
 */
void FlightPlans::sort()
{
    //true if sorting by time, false if cost
    bool sortTag{request.getTimeTag()};

    int j{};                                   //uses int to find index to swap
    Plan t{};                                  //temp variable
    for(int i{1}; i < plans.length(); i++)
    {
        //Uses the checkByTag function as the comparison
        for(j = i; j > 0 && checkByTag(sortTag, plans[j-1], plans[j]); j--)
        {
            t = plans[j];                     //swap data
            plans[j] = plans[j-1];
            plans[j-1] = t;
        }
    }
}

/**
 * getPlans()
 * @return the linked list of Plan objects
 */
LinkedList<Plan> FlightPlans::getPlans() const
{
    return plans;
}

/**
 * setPlans(value)
 *
 * @param value - the linked list to set "plans" to
 */
void FlightPlans::setPlans(const LinkedList<Plan>& value)
{
    plans = value;
}

/**
 * getRequest()
 *
 * @return the Request within the FlightPlan
 */
Request FlightPlans::getRequest() const
{
    return request;
}

/**
 * setRequest(value)
 *
 * @param value - the Request to set the request variable to
 */
void FlightPlans::setRequest(const Request& value)
{
    request = value;
}

/**
 * checkByTag returns a boolean based on whether the tag given is
 * true or false. If the tag is true, then the function will compare
 * the duration of each Plan object. Otherwise, it will compare the
 * cost of each Plan object.
 * @param tag - the determinant of the comparison. If true, the function will
 *              compare the duration, otherwise it will compare the cost
 * @param lhs - the Plan object to compare with rhs
 * @param rhs - the Plan object to compare with lhs
 * @return a boolean based on the criteria described in the description
 */
bool FlightPlans::checkByTag(bool tag, const Plan& lhs, const Plan& rhs)
{
    if(tag)
    {
        return lhs.getTotalDuration() > rhs.getTotalDuration();
    }
    else
        return lhs.getTotalCost() > rhs.getTotalCost();
}

/**
 * operator<< overload
 *
 * Example Output:
 *
 * Sandgap, Madison Park (Cost)
 * [Sandgap -> Jamesville -> Madison Park.           Time: 129         Cost: 70
 * , Sandgap -> Madison Park.                        Time: 322         Cost: 282
 * ]
 *
 * @param o - the ostream reference to add data to
 * @param fr - the FlightPlans object to pull data from
 * @return an ostream reference containing the data from FlightPlans& fr
 */
std::ostream& operator<<(std::ostream& o, const FlightPlans& fr)
{

    o << fr.request.getOrigin() << ", " << fr.request.getDestination();
    o << " (";
    (fr.getRequest().getTimeTag()) ? o << "Time" : o << "Cost";
    o << ")";
    o << std::endl << fr.getPlans();
    return o;
}


#ifndef REQUEST_H
#define REQUEST_H

#include <dsstring.h>
#include <iostream>
#include <iomanip>

/**
 * The Request class details a single user request, which contains an origin,
 * destination, and a bool tag to determine whether the list of flights returned
 * should find the shortest or cheapest flights.
 *
 * Request class objects are used within the FlightRequests class, which takes
 * requests and aggregates them into a list that can be more easily used
 * to find multiple flight schedules for each journey request.
 *
 * This class will be used in the Sprint4: Flight Planner project
 * in SMU CSE 2341.
 *
 * @author Oisin Coveney
 * @date April 2, 2017
 */
class Request
{
    private:

        String origin;
        String destination;
        bool timeTag;       //time if true, cost if false

    public:

        //Constructors
        Request();
        Request(String orig, String dest, bool timeTag);
        Request(const Request& other);
        Request& operator=(const Request& other);

        //Getters and setters
        String getOrigin() const;
        void setOrigin(const String& value);

        String getDestination() const;
        void setDestination(const String& value);

        bool getTimeTag() const;
        void setTimeTag(bool value);

        //Operator<< overload
        friend std::ostream& operator<<(std::ostream& o, const Request& r);

};

#endif // REQUEST_H

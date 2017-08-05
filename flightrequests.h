#ifndef FLIGHTREQUESTS_H
#define FLIGHTREQUESTS_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <request.h>
#include <linkedlist.h>
#include <dsstring.h>


/**
 * The FlightRequests class contains a list of Request objects that will
 * be used to determine the list of flight plans that will be outputted
 * to the output file. The class takes a request data file and parses it
 * in the constructor and creates a linked list of Request objects that
 * the Output class will use to find flights.
 *
 * This class will be used in the Sprint4: Flight Planner project
 * in SMU CSE 2341.
 *
 * @author Oisin Coveney
 * @date April 2, 2017
 *
 */
class FlightRequests
{
    private:
        LinkedList<Request> requests;

    public:

        //Constructors
        FlightRequests();
        FlightRequests(char* requestText);

        //getters and setters
        LinkedList<Request> getRequests() const;
        void setRequests(const LinkedList<Request>& value);

        //operator<< overload
        friend std::ostream& operator<< (std::ostream& o, const FlightRequests& fr);
};

#endif // FLIGHTREQUESTS_H

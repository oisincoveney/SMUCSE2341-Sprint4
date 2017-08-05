#ifndef FLIGHTPLANS_H
#define FLIGHTPLANS_H

#include <linkedlist.h>
#include <request.h>
#include <plan.h>

/**
 * The FlightPlans class uses a linked list of Plan objects and a Request object
 * that delineates the requested origin and destination, and a list of
 * flight schedules that will bring someone from the origin to the destination.
 *
 * This class will be used in the Sprint4: Flight Planner project
 * in SMU CSE 2341.
 *
 * @author Oisin Coveney
 * @date April 6, 2017
 */
class FlightPlans
{
    private:

        LinkedList<Plan> plans;     // list of flights
        Request request;            // the flight request

    public:

        //Constructor
        FlightPlans();
        FlightPlans(LinkedList<Plan> p, Request r);
        FlightPlans(const FlightPlans& plans);

        //Sort based on the tag given by the request
        void sort();

        //getter and setter
        LinkedList<Plan> getPlans() const;
        void setPlans(const LinkedList<Plan>& value);

        Request getRequest() const;
        void setRequest(const Request& value);

        //An overload of operator== that uses the bool tag given to return
        //the correct result
        bool checkByTag(bool tag, const Plan& lhs, const Plan& rhs);

        //operator<< overload
        friend std::ostream& operator<<(std::ostream& o, const FlightPlans& fr);

};

#endif

#ifndef FLIGHTPLAN_H
#define FLIGHTPLAN_H

#include <linkedlist.h>
#include <dsstring.h>
#include <iostream>
#include <iomanip>
#include <stack.h>
#include <city.h>


/**
 * The Plan class contains the details of a single journey from an origin to
 * a destination with connections in between, as well as the cost and duration
 * of the total journey.
 *
 * Plan class objects are used within the FlightPlans class, which takes
 * multiple plans which can be more easily outputted to an output file for
 * the user to more easily understand.
 *
 * This class will be used in the Sprint4: Flight Planner project
 * in SMU CSE 2341.
 *
 * @author Oisin Coveney
 * @date April 6, 2017
 */
class Plan
{
    private:
        String origin;
        String destination;
        String connections;
        int totalDuration;              //in minutes
        double totalCost;

    public:

        //Constructors and operator= (Rule of 3)
        Plan ();
        Plan (String orig, String dest);
        Plan (Stack<Origin> stack, String dest);
        Plan (const Plan& other);
        Plan& operator=(const Plan& other);


        //Appends the connection to the connections string
        void addConnection(String connection);


        //Getters and Setters
        int getTotalDuration() const;
        void setTotalDuration(int value);

        double getTotalCost() const;
        void setTotalCost(double value);

        String getOrigin() const;
        void setOrigin(const String& value);

        String getDestination() const;
        void setDestination(const String& value);

        String getConnections() const;
        void setConnections(const String& value);

        //operator<< overload
        friend std::ostream& operator<<(std::ostream&, const Plan&);
};

#endif // FLIGHTPLAN_H

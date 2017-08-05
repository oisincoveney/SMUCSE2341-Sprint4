#ifndef FLIGHTDATA_H
#define FLIGHTDATA_H

#include <linkedlist.h>
#include <city.h>
#include <iomanip>
#include <iostream>
#include <city.h>


/**
 * The FlightData class contains the data for a flight schedule, as delineated
 * by the flight data file provided. The data is parsed within a linked list
 * of Origin objects (which each contain a linked list of Destination objects).
 *
 * The file is parsed within the constructor, and all data is placed into the
 * flights LinkedList.
 *
 * This class will be used in the Sprint4: Flight Planner project
 * in SMU CSE 2341.
 *
 * @author Oisin Coveney
 * @date March 30, 2017
 */
class FlightData
{
    private:
        LinkedList<Origin> flights;                     //flight schedule

    public:

        //Constructors
        FlightData() : flights{} {}
        FlightData(const FlightData& data) : flights{data.flights}{}
        FlightData(char* dataFile);

        //Getter and setter
        LinkedList<Origin> getFlights() const;
        void setFlights(const LinkedList<Origin>& value);

        //Adds two flights to the flights linkedlist
        void addRoundTrip(String orig, String dest, double cost, int duration);

        //operator<< overload
        friend std::ostream& operator<<(std::ostream&, const FlightData&);
};

#endif // FLIGHTDATA_H

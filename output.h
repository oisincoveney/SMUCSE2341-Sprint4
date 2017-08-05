#pragma once

#include <iostream>
#include <flightplans.h>
#include <flightdata.h>
#include <flightrequests.h>
#include <fstream>
#include <stack.h>
using namespace std;

/**
 * The Output class contains the functions for outputting a list of flight
 * schedules to an output file. The class takes in three data file names and
 * constructs FlightData, FlightRequests, and a linked list of FlightPlans
 * objects that will determine the most efficient flights asked for by each
 * request.
 *
 * The class contains the function for iterating through the flight data and
 * requests, using iterative backtracking to determine the most efficient
 * flight plan for the user.
 *
 * This class will be used in the Sprint4: Flight Planner project
 * in SMU CSE 2341.
 *
 * @author Oisin Coveney
 * @date April 6, 2017
 */
class Output
{
    private:
        FlightData data;                    //list of possible flights
        FlightRequests requests;            //list of requested schedule
        LinkedList<FlightPlans> plans;      //final list of flights
        ofstream o;                         //output to file
    public:

        //Constructors
        Output();
        Output(char* dataFile, char* requestFile, char* outputFile);

        //Iterates through the requests and calls backtrack() to find flights
        void retrieveFlights();

        //Finds the flights using iterative backtracking
        FlightPlans backTrack(LinkedList<Origin> schedule, Request r);

        //checks if the origin is within the stack
        bool inStack(Origin* o, Stack<Origin>& s);

        //returns the data from the LinkedList of FlightPlans
        void print();
};

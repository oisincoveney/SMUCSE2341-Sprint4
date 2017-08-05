#include "output.h"


/**
 * Default Constructor
 * @exception invalid_argument any time the default constructor is called, since
 *              Output needs files to complete its tasks
 */
Output::Output()
{
    throw std::invalid_argument("Output requires File I/O to function");
}

/**
 * Constructor with char*, char*, char*
 * @param dataFile - the flight data input file
 * @param requestFile - input file for requested flight plans
 * @param outputFile - the output file to put the final output in
 */
Output::Output(char* dataFile, char* requestFile, char* outputFile)
    : data{dataFile}, requests{requestFile}, plans{}
{
    o.open(outputFile);
    retrieveFlights();
}

/**
 * retrieveFlights()
 *
 * Iterates through the requests in the FlightRequests object and calls
 * the backTrack() function, which finds all possible combinations of
 * flights for each request. These flights are found with the FlightData
 * object, whose linked list of Origin objects provides the information
 * needed to find all possible flights.
 *
 * After the flights are retrieved, each FlightPlan within the plans
 * LinkedList is sorted by the user's request in finding either the
 * shortest or cheapest flight.
 *
 */
void Output::retrieveFlights()
{
    LinkedList<Origin> flightdata{data.getFlights()};
    LinkedList<Request> reqs{requests.getRequests()};

    //Get flights via backTrack()
    for(int i{}; i < reqs.length(); i++)
    {
        plans.pushBack(backTrack(flightdata, reqs[i]));
    }
}

/**
 * backTrack(LinkedList<Origin>, Request)
 *
 * Takes in a linked list of the flight data and a user request,
 * and uses iterative backtracking to find all flights that match
 * the user's request for a journey between the origin and destination.
 *
 * @param schedule - a LinkedList containing Origin objects that contain all
 *                   data about each journey
 * @param r - a user Request specifying the origin, destination, and whether
 *            flights should be sorted by
 * @return
 */
FlightPlans Output::backTrack(LinkedList<Origin> schedule, Request r)
{
    Stack<Origin> stack{};

    for(int i{}; i < schedule.length(); i++)
    {
        if(schedule[i] == r.getOrigin())
        {
            stack.push(schedule[i]);
            break;
        }
    }

    Origin* current = nullptr;
    LinkedList<Plan> flightlist{};
    String destination{r.getDestination()};

    while(!stack.isEmpty())
    {
        current = stack.peekPointer();

        if(inStack(current, stack))
            stack.pop();
        else
        {
            LinkedList<Destination>& dests{current->getDestinations()};
            int s = dests.length();
            for(int i{}; i < s; i++)
            {
                Destination& d{dests[i]};

                if(!d.getVisited())
                {
                    d.setVisited(true);

                    current->setCost(d.getCost());
                    current->setDuration(d.getDuration());

                    if(d.getName() == destination)
                        flightlist.pushBack(Plan(stack, destination));
                    else
                        stack.push(*(d.getOriginPtr()));

                    break;
                }
                else if(i == dests.length() - 1)
                    stack.pop();
            }
        }
    }
    return FlightPlans(flightlist, r);
}


bool Output::inStack(Origin* o, Stack<Origin>& s)
{

    LinkedList<Origin> list{s.readStack()};
    String oName = o->getName();


    for(int i{}; i < list.length()-1; i++)
    {
        if(oName == list[i].getName())
            return true;
    }
    return false;
}

void Output::print()
{
    for(int i{}; i < plans.length(); i++)
    {
        FlightPlans& f{plans[i]};
        Request r = f.getRequest();
        o << "Flight " << i+1 << ": ";
        o << r.getOrigin() << ", " << r.getDestination();
        o << " (";
        if(r.getTimeTag())
            o << "Time";
        else
            o << "Cost";
        o << ")" << std::endl;

        LinkedList<Plan> p{f.getPlans()};

        for(int j{}; j < 3 && j < p.length(); j++)
        {
            o << "Path " << j+1 << ": ";
            o << p[j];
        }
        o << std::endl << std::endl;
    }
}


#include "flightrequests.h"

/**
 * Default constructor
 */
FlightRequests::FlightRequests() : requests{} {}


/**
 * Constructor with char*
 *
 * Uses the file name within the parameter to parse the user request data
 * into a LinkedList of Request objects.
 *
 * @param requestText - the data file containing the user's flight requests
 * @exception invalid_argument if the file does not exist
 */
FlightRequests::FlightRequests(char* requestText)
{
    //Open the file
    std::ifstream requestFile;
    requestFile.open(requestText);

    //Throw exception if the file doesn't exist
    if(!requestFile.is_open())
    {
        throw std::invalid_argument("File is not open or cannot be found.");
    }

    //Number of requests
    int numReqs{};
    requestFile >> numReqs;
    requestFile.ignore();

    //Strings for the tag, origin, and destination, and a bool to convert
    // the String t to a boolean for the Request object
    String t{}, orig{}, dest{};
    bool tag;
    for(int i{}; i < numReqs; i++)
    {
        //Pull data using getline and delimiters
        getline(requestFile, orig, '|');
        getline(requestFile, dest, '|');
        getline(requestFile, t, '\n');

        //Convert String t to a bool tag depending on the character at the end
        tag = (t == "T") ? true : false;

        //Adds a request object to the linked list
        requests.pushBack(Request(orig, dest, tag));
    }
}

/**
 * getRequests()
 *
 * @return the LinkedList of Request objects
 */
LinkedList<Request> FlightRequests::getRequests() const
{
    return requests;
}

/**
 * setRequests(value)
 *
 * @param value - the linked list of request objects to set "requests" to
 */
void FlightRequests::setRequests(const LinkedList<Request>& value)
{
    requests = value;
}


/**
 * operator<< overload
 * (Note: std::right, std::left, and std::setw are used for formatting)
 *
 * Example Output:
 *
 * REQUESTS
 *        Sandgap -> Madison Park             R: Cost
 *        Sandgap -> Jamesville               R: Time
 *        Jamesville -> Sandgap               R: Cost
 *        Sandgap -> Jamesville               R: Time
 *
 * @param o - the ostream reference to add data to
 * @param fr - the FlightRequests file to pull data from
 * @return the ostream reference containing the new data from FlightRequests
 */
std::ostream& operator<< (std::ostream& o, const FlightRequests& fr)
{
    //Requests
    o << "REQUESTS" << std::endl;
    for(int i{}; i < fr.requests.length(); i++)
    {
        //Gets the request
        Request r = fr.requests.get(i);

        o << std::right;
        o << std::setw(25) << r.getOrigin();
        o << std::left;
        o << " -> " << std::setw(25) << r.getDestination();
        o << std::setw(3) << "R: " << std::setw(5);
        ((r.getTimeTag()) ? o << "Time" : o << "Cost");
        o << std::endl;
    }
    return o;
}

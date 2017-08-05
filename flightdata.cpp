#include <flightdata.h>

/**
 * Constructor with char*
 * @param dataText - the name of the file name to open and parse data from.
 * @exception invalid_argument if the file does not exist
 */
FlightData::FlightData(char* dataText)
{
    //open the data file
    std::ifstream dataFile;
    dataFile.open(dataText);

    //throw exception if the file doesn't exist
    if(!dataFile.is_open())
    {
        throw std::invalid_argument("File is not open or cannot be found.");
    }

    //get the number of flights to iterate through
    int numFlights{};
    dataFile >> numFlights;
    dataFile.ignore();                      //ignore newline character

    //initializing the origin, destination, cost, and duration strings,
    //as well as a double for cost and an integer duration
    String orig{}, dest{}, cos{}, dur{};
    double cost{};
    int duration{};

    //pull data from the data file, using an overloaded version of the
    //getline function for String
    for(int i{}; i < numFlights; i++)
    {
        getline(dataFile, orig, '|');
        getline(dataFile, dest, '|');
        getline(dataFile, cos, '|');
        getline(dataFile, dur);

        //Truncate any result to 2 decimal places and return to cost
        cost  = atof(cos.c_str());
        duration = atoi(dur.c_str());

        //Add information to the schedule
        addRoundTrip(orig, dest, cost, duration);
    }
    dataFile.close();

}

/**
 * getFlights()
 * @return the list of Origin objects that contains all the flight data
 */
LinkedList<Origin> FlightData::getFlights() const
{
    return flights;
}

/**
 * setFlights(value)
 * @param value - the linked list of Origin cities to change ot the flights
 */
void FlightData::setFlights(const LinkedList<Origin>& value)
{
    flights = value;
}

/**
 * addRoundTrip()
 *
 * Adds two flights to the LinkedList of Origin objects, inserting both
 * cities as origins and destinations. Because of the nature of the Sprint4
 * Project in CSE 2341, all flights can be accessed from both ends, i.e.
 * an origin and a destination are also, respectively, the destination and
 * origin for a different flight. Thus, all flights given are round trip
 * flights.
 *
 * @param city1 - name of one of the cities given
 * @param city2 - name of the other city
 * @param cost - the cost of the flight
 * @param duration - the duration of the flight
 */
void FlightData::addRoundTrip(String city1, String city2, double cost, int duration)
{
    //adds the Origin objects to the linked list and returns
    //the indices of their existence within the list
    int index1 = flights.uniquePushBack(Origin(city1));
    int index2 = flights.uniquePushBack(Origin(city2));

    //Gets the pointers for each city, so they can be added
    //as data pointers to each Destination object
    Origin* ptr1 = flights.getDataPointer(index1);
    Origin* ptr2 = flights.getDataPointer(index2);

    //Creation of destination objects
    Destination d1(city2, cost, duration, ptr2);
    Destination d2(city1, cost, duration, ptr1);

    //Pull references of the destination lists from each Origin object
    LinkedList<Destination>& dests1 = ptr1->getDestinations();
    LinkedList<Destination>& dests2 = ptr2->getDestinations();

    //pushes back each destination to each list
    dests1.pushBack(d1);
    dests2.pushBack(d2);
}


/**
 * operator<< overload
 *
 * Adds all flight data with relevant information about each flight to
 * the ostream reference parameter.
 *
 * An Example of Output:
 *
 * FLIGHTS
 * Sandgap (2 flights)
 *    Destination              Cost ($)       Duration (min)
 * -> Madison Park             282            322
 * -> Jamesville               43             50
 *
 * Madison Park (2 flights)
 *    Destination              Cost ($)       Duration (min)
 * -> Sandgap                  282            322
 * -> Jamesville               27             79
 *
 * Jamesville (2 flights)
 *    Destination              Cost ($)       Duration (min)
 * -> Sandgap                  43             50
 * -> Madison Park             27             79
 *
 * Total of 6 flights.
 *
 * @param o - the ostream reference to add data to
 * @param d - the FlightData object to pull data from
 * @return an ostream reference containing the data from FlightData d
 */
std::ostream& operator<<(std::ostream& o, const FlightData& d)
{
    o << "\nFLIGHTS" << std::endl;
    int totalFlights{0};

    //Gets the list of origins
    LinkedList<Origin> origins = d.getFlights();

    //Iterates through all of the origins
    for(int i{}; i < origins.length(); i++)
    {
        //get origin city name
        String originCity = origins.get(i).getName();
        o << originCity;

        //get destinations
        LinkedList<Destination> dests = origins.get(i).getDestinations();
        o << " (" << dests.length() << " flights)\n";
        totalFlights += dests.length();

        //Add columns for easier reading
        o << std::left;
        o << "   "  << std::setw(25) << "Destination";
        o << std::setw(15) << "Cost ($)";
        o << std::setw(20) << "Duration (min)";
        o << std::endl;

        //Iterate through destinations
        for(int j{}; j < dests.length(); j++)
        {
            //Get destination reference and output relevant data
            Destination& d = dests[j];
            o << std::left;
            o << "-> "  << std::setw(25) << d.getName();
            o << "" << std::setw(15) << d.getCost();
            o << std::setw(20) << d.getDuration();
            o << std::endl;
        }
        o << std::endl;
    }
    o << "Total of " << totalFlights << " flights.\n";
    return o;
}

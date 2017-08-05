#pragma once
#include <linkedlist.h>
#include <dsstring.h>
#include <node.h>

/**
 * The City class is used as a base class for the derived Origin and
 * Destination classes, and contains operators that allow for easier
 * comparison between an Origin and Destination city when determining
 * flight patterns.
 *
 * This class will be used in the Sprint4: Flight Planner project
 * in SMU CSE 2341.
 *
 * @author Oisin Coveney
 * @date March 30, 2017
 *
 */
class City
{
    public:
        String name;
    public:

        //Constructors
        City();
        City(String name);

        //operators to compare all derived city classes
        bool operator==(const City& rhs);
        bool operator!=(const City& rhs);

        //Getter and setter
        String getName() const;
        void setName(const String& value);

        //ostream operator<<
        friend std::ostream& operator<<(std::ostream& o, const City& city);
};

//Declaration of Destination class, so Origin can access
class Destination;

/**
 * The Origin class is a derived class of the City class. In addition to its
 * name, the Origin class holds a list of destinations that can be accessed
 * from the origin city, as specified by the data file containing the flight
 * schedule.
 *
 * The cost and duration variables are always initialized to 0, and are changed
 * when a suitable destination city is found within the flight retrievel
 * process. Then, the cost and duration from the Destination object
 * are transferred to the Origin object, which will then be accessed
 * when determining the final cost and duration of a flight.
 *
 * This class will be used in the Sprint4: Flight Planner project
 * in SMU CSE 2341.
 *
 * @author Oisin Coveney
 * @date March 30, 2017
 */
class Origin : public City
{
    private:
        double cost;
        int duration;
        LinkedList<Destination> destinations;

    public:

        //Constructors
        Origin();
        Origin(String cityName);
        Origin(const Origin& other);
        Origin& operator=(const Origin& other);

        //Getters and setters
        int getDuration() const;
        void setDuration(int value);

        double getCost() const;
        void setCost(double value);

        LinkedList<Destination>& getDestinations();
        LinkedList<Destination> getDestinations() const;
        void setDestinations(const LinkedList<Destination>& value);

        //ostream operator overload
        friend std::ostream& operator<<(std::ostream& o, const Origin& orig);
};

/**
 * The Destination class is a derived class of the City class, containing
 * the cost and duration of a flight to the city named by this Class from
 * the Origin city (which presumably has a flight to this destination).
 *
 * The class also contains a pointer to the instance of the Origin object
 * with the same name within the list of Origins that is used in retrieving
 * flights, and the visited boolean is used to determine whether a city
 * is suitable for connecting to a destination.
 *
 * This class will be used in the Sprint4: Flight Planner project
 * in SMU CSE 2341.
 *
 * @author Oisin Coveney
 * @date March 30, 2017
 */
class Destination : public City
{
    private:
        double cost;
        int duration;
        Origin* originPtr;
        bool visited;

    public:

        //Constructors
        Destination() : City(), cost{0.0}, duration{0}, originPtr{nullptr}, visited{false} {}
        Destination(const Destination& other);
        Destination& operator=(const Destination& other);
        Destination(String cityName, double cost, int duration);
        Destination(String cityName, double cost, int duration, Origin* ptr);

        //Getters and setters
        double getCost() const;
        void setCost(double value);

        int getDuration() const;
        void setDuration(int value);

        Origin* getOriginPtr() const;
        void setOriginPtr(Origin* value);

        bool getVisited() const;
        void setVisited(bool value);

        //operator<< overload
        friend std::ostream& operator<<(std::ostream& o, const Destination& d);
};

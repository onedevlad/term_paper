#include <string>
#include <vector>

#ifndef FLIGHT_H
#define FLIGHT_H

// #include "Table.h"

class Flight {
  public:
    static std::vector<std::string> headers;
    static std::vector<Flight> flights;
    int entryLine;
    std::string flightID;
    int passangersCount;
    std::string departureDate;
    std::string departureTime;
    std::string arrivalDate;
    std::string arrivalTime;
    std::string planeID;
    static void load();
    static void setHeaders(std::vector<std::string>);
    static std::vector<std::vector<std::string>> serialize();
    static void factory(int, std::vector<std::string>, bool);
    Flight(int, std::vector<std::string>);
};

#endif
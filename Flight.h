#include <string>
#include <vector>

#ifndef FLIGHT_H
#define FLIGHT_H

class Flight {
  public:
    static std::vector<std::string> headers;
    static std::vector<Flight> flights;
    int entryLine;
    std::string flightID;
    int passangersCount;
    std::string departureDate;
    std::string departureTime;
    std::string planeID;
    static void load();
    static void setHeaders(std::vector<std::string>);
    static void factory(int, std::vector<std::string>);
    Flight(int, std::vector<std::string>);
};

#endif
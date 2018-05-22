#include <string>
#include <vector>

#ifndef FLIGHT_H
#define FLIGHT_H


class Flight {
  public:
    static std::vector<Flight> flights;
    int entryLine;
    std::string flightID;
    std::string passangersCount;
    std::string departureDate;
    std::string departureTime;
    std::string arrivalDate;
    std::string arrivalTime;
    std::string planeID;
    static void load();
    static std::vector<std::vector<std::string>> find(int, std::string);
    static std::vector<std::vector<std::string>> serialize();
    static std::vector<std::string> serializeLn(Flight);
    static void factory(int, std::vector<std::string>, bool);
    Flight(int, std::vector<std::string>);
};

#endif
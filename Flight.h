#include <string>
#include <vector>

#ifndef FLIGHT_H
#define FLIGHT_H


class Flight {
  private:
    static std::vector<Flight> flights;
    std::string flightID;
    std::string passangersCount;
    std::string departureDate;
    std::string departureTime;
    std::string arrivalDate;
    std::string arrivalTime;
    std::string planeID;
    void setFields(std::vector<std::string>);
    static void updateFS();
    static std::vector<Flight*> getMatchingFlights(std::string query);
  public:
    static void load();
    static std::vector<std::vector<std::string>> find(std::string);
    static std::vector<std::vector<std::string>> update(std::string, std::vector<std::string>);
    static void remove(std::string);
    static std::vector<std::vector<std::string>> serialize();
    static std::vector<std::string> serializeLn(Flight);
    static void factory(std::vector<std::string>, bool);
    Flight(std::vector<std::string>);
};

#endif
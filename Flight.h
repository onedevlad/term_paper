#include <string>
#include <vector>

#ifndef FLIGHT_H
#define FLIGHT_H

using namespace std;

#include "Table.h"


class Flight {
  private:
    static vector<Flight> flights;
    string flightID;
    string passangersCount;
    string departureDate;
    string departureTime;
    string arrivalDate;
    string arrivalTime;
    string planeID;
    void setFields(vector<string>);
    static void updateFS();
    static vector<Flight*> getMatchingFlights(string);
    static vector<string> serializeLn(Flight);

  public:
    static vector<vector<string>> serialize();
    static vector<vector<string>> find(string);
    static vector<vector<string>> update(string, vector<string>);
    static void remove(string);
    static void factory(vector<string>, bool);
    Flight(vector<string>);
};


#endif
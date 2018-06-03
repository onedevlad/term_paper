#ifndef FLIGHT_H
#define FLIGHT_H

#include <string>
#include "Vector.hpp"


#include "Entry.hpp"

using namespace std;

class Flight : protected Entry {
  private:
    static vector<Flight> flights;
    string flightID;
    string passangersCount;
    string departureDate;
    string departureTime;
    string arrivalDate;
    string arrivalTime;
    string planeID;

  public:
    static vector<vector<string>> serialize();
    static void updateFS();
    static vector<vector<string>> find(string);
    static vector<vector<string>> update(string, vector<string>);
    static void remove(string);
    static void factory(vector<string>, bool);

    vector<string> serializeLn();
    void setFields(vector<string>);
    Flight(vector<string>);
    Flight();
};


#endif
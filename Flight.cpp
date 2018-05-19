#include <iostream>
#include <string>
#include <vector>

#include "Flight.h"
#include "Table.h"
#include "Utils.h"

using namespace std;

// Static vectors need to be initialized
vector<Flight> Flight::flights = {};
vector<string> Flight::headers = {};

void Flight::load() {
  Table::parse(Table::readFile("Flights"), Flight::setHeaders, Flight::factory);
}

void Flight::setHeaders(vector<string> _headers) {
  headers = _headers;
}

void Flight::factory(int _entryLine, vector<string> rawData) {
  Flight obj(_entryLine, rawData);
  flights.push_back(obj);
}

Flight::Flight(int _entryLine, vector<string> rawData) {
  entryLine = _entryLine;
  flightID = rawData[0];
  passangersCount = Utils::strToInt(rawData[1]);
  departureDate = rawData[2];
  departureTime = rawData[3];
  planeID = rawData[4];

  cout << "Created flight #" << flightID << " on " << planeID << endl;
}

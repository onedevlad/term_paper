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

vector<vector<string>> Flight::serialize() {
  vector<vector<string>> result;
  result.push_back(Flight::headers);

  for(int i=0; i<Flight::flights.size(); i++) {
    vector<string> record;
    record.push_back(Flight::flights[i].flightID);
    record.push_back(to_string(Flight::flights[i].passangersCount));
    record.push_back(Flight::flights[i].departureDate);
    record.push_back(Flight::flights[i].departureTime);
    record.push_back(Flight::flights[i].planeID);

    result.push_back(record);
  }

  return result;
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

  // cout << "Created flight #" << flightID << " on " << planeID << endl;
}

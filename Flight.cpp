#include <iostream>
#include <string>
#include <vector>

#include "Flight.h"
#include "Table.h"
#include "Utils.h"

using namespace std;

// Static vectors need to be initialized
vector<Flight> Flight::flights = {};

void Flight::load() {
  Table::TFlights.parse(Table::TFlights.readFile(), Flight::factory);
}

vector<vector<string>> Flight::serialize() {
  vector<vector<string>> result;
  result.push_back(Table::TFlights.headers);

  for(int i=0; i<flights.size(); i++)
    result.push_back(serializeLn(flights[i]));

  return result;
}

vector<string> Flight::serializeLn(Flight obj) {
  vector<string> record;
  record.push_back(obj.flightID);
  record.push_back(obj.passangersCount);
  record.push_back(obj.departureDate);
  record.push_back(obj.departureTime);
  record.push_back(obj.arrivalDate);
  record.push_back(obj.arrivalTime);
  record.push_back(obj.planeID);
  return record;
}

vector<vector<string>> Flight::find(int headerIndex, string searchQuery) {
  vector<vector<string>> result;
  string containedData;
  for(int i=0; i<flights.size(); i++) {
    switch(headerIndex) {
      case 0: containedData = flights[i].flightID; break;
      case 1: containedData = flights[i].passangersCount; break;
      case 2: containedData = flights[i].departureDate; break;
      case 3: containedData = flights[i].departureTime; break;
      case 4: containedData = flights[i].arrivalDate; break;
      case 5: containedData = flights[i].arrivalTime; break;
      case 6: containedData = flights[i].planeID; break;
    }

    if(Utils::contains(containedData, searchQuery)) result.push_back(serializeLn(flights[i]));
  }

  return result;
}

void Flight::factory(int _entryLine, vector<string> rawData, bool fsSync) {
  Flight obj(_entryLine, rawData);
  flights.push_back(obj);
  if(fsSync) Table::TFlights.writeFile(serialize());
}

Flight::Flight(int _entryLine, vector<string> rawData) {
  entryLine = _entryLine;

  flightID = rawData[0];
  passangersCount = rawData[1];
  departureDate = rawData[2];
  departureTime = rawData[3];
  arrivalDate = rawData[4];
  arrivalTime = rawData[5];
  planeID = rawData[6];
}

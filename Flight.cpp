#include <string>
#include <vector>
#include <iostream>

#include "Flight.h"
#include "Table.h"

using namespace std;


vector<vector<string>> Flight::serialize() {
  return serializeEntries(Table::TFlights, flights);
}

vector<vector<string>> Flight::find(string query) {
  return findEntries(query, flights);
}

vector<vector<string>> Flight::update(string query, vector<string> fields) {
  return updateEntries(query, fields, flights);
}

void Flight::remove(string query) {
  return removeEntries(query, flights);
}

void Flight::updateFS() {
  return Table::TFlights.writeFile(serialize());
}

void Flight::factory(vector<string> rawData, bool fsSync) {
  return entriesFactory(flights, rawData, fsSync);
}

void Flight::setFields (vector<string> rawData) {
  if(rawData[0].length()) flightID = rawData[0];
  if(rawData[1].length()) passangersCount = rawData[1];
  if(rawData[2].length()) departureDate = rawData[2];
  if(rawData[3].length()) departureTime = rawData[3];
  if(rawData[4].length()) arrivalDate = rawData[4];
  if(rawData[5].length()) arrivalTime = rawData[5];
  if(rawData[6].length()) planeID = rawData[6];
}

vector<string> Flight::serializeLn() {
  vector<string> record;
  record.push_back(flightID);
  record.push_back(passangersCount);
  record.push_back(departureDate);
  record.push_back(departureTime);
  record.push_back(arrivalDate);
  record.push_back(arrivalTime);
  record.push_back(planeID);
  return record;
}

Flight::Flight(vector<string> rawData) {
  setFields(rawData);
}

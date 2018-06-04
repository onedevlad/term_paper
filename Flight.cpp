#include <string>
#include "Vector.hpp"
#include <iostream>

#include "Utils.h"
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
  removeEntries(query, flights);
}

void Flight::updateFS() {
  vector<vector<string>> data = serialize();
  Table::TFlights.writeFile(data);
}

void Flight::factory(vector<string> rawData, bool fsSync) {
  entriesFactory(flights, rawData, fsSync);
}

void Flight::setFields (vector<string> rawData) {
  if(Utils::isRawItemValid(rawData, 0)) flightID = rawData[0];
  if(Utils::isRawItemValid(rawData, 1)) departureAirpt = rawData[1];
  if(Utils::isRawItemValid(rawData, 2)) arrivalAirpt = rawData[2];
  if(Utils::isRawItemValid(rawData, 3)) departureDate = rawData[3];
  if(Utils::isRawItemValid(rawData, 4)) departureTime = rawData[4];
  if(Utils::isRawItemValid(rawData, 5)) arrivalDate = rawData[5];
  if(Utils::isRawItemValid(rawData, 6)) arrivalTime = rawData[6];
  if(Utils::isRawItemValid(rawData, 7)) planeID = rawData[7];
}

vector<string> Flight::serializeLn() {
  vector<string> record;
  record.push_back(flightID);
  record.push_back(departureAirpt);
  record.push_back(arrivalAirpt);
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

Flight::Flight(){};
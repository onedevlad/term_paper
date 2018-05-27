#include <iostream>
#include <string>
#include <vector>

#include "Flight.h"
#include "Table.h"
#include "Utils.h"
#include "ExpressionBuilder.h"

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

vector<Flight*> Flight::getMatchingFlights(string query) {
  vector<Flight*> result;

  for(int i=0; i<flights.size(); i++) {
    vector<string> line = serializeLn(flights[i]);
    ExpressionBuilder expression = ExpressionBuilder(line);
    bool lineMatches = expression.parse(query);
    if(lineMatches) result.push_back(&flights[i]);
  }

  return result;
}


vector<vector<string>> Flight::find(string query) {
  vector<vector<string>> result;
  vector<Flight*> matchingFlights = getMatchingFlights(query);

  for(int i=0; i<matchingFlights.size(); i++)
    result.push_back(serializeLn(*matchingFlights[i]));

   return result;
}


vector<vector<string>> Flight::update(string query, vector<string> fields) {
  vector<vector<string>> result;
  vector<Flight*> matchingFlights = getMatchingFlights(query);

  for(int i=0; i<matchingFlights.size(); i++) {
    matchingFlights[i]->setFields(fields);
    result.push_back(serializeLn(*matchingFlights[i]));
  }

  updateFS();

  return result;
}

void Flight::remove(string query) {
  vector<Flight*> matchingFlights = getMatchingFlights(query);

  for(int i=0; i<matchingFlights.size(); i++) delete matchingFlights[i];

  updateFS();
}

void Flight::updateFS() {
  Table::TFlights.writeFile(serialize());
}

void Flight::factory(vector<string> rawData, bool fsSync) {
  Flight obj(rawData);
  flights.push_back(obj);
  if(fsSync) updateFS();
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


Flight::Flight(vector<string> rawData) {
  setFields(rawData);
}

#include <iostream>
#include <string>
#include "Vector.hpp"

#include "Passanger.h"
#include "Table.h"

using namespace std;


vector<vector<string>> Passanger::serialize() {
  return serializeEntries(Table::TPassangers, passangers);
}

vector<vector<string>> Passanger::find(string query) {
  return findEntries(query, passangers);
}

vector<vector<string>> Passanger::update(string query, vector<string> fields) {
  return updateEntries(query, fields, passangers);
}

void Passanger::remove(string query) {
  removeEntries(query, passangers);
}

void Passanger::updateFS() {
  vector<vector<string>> data = serialize();
  Table::TPassangers.writeFile(data);
}

void Passanger::factory(vector<string> rawData, bool fsSync) {
  entriesFactory(passangers, rawData, fsSync);
}

vector<string> Passanger::serializeLn() {
  vector<string> result;
  result.push_back(passangerID);
  result.push_back(lastName);
  result.push_back(firstName);
  result.push_back(flightID);

  return result;
}

void Passanger::setFields (vector<string> rawData) {
  if(rawData[0].length()) passangerID = rawData[0];
  if(rawData[1].length()) lastName = rawData[1];
  if(rawData[2].length()) firstName = rawData[2];
  if(rawData[3].length()) flightID = rawData[3];
}

Passanger::Passanger(vector<string> rawData) {
  setFields(rawData);
}

Passanger::Passanger(){}
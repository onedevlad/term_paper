#include <iostream>
#include <string>
#include "Vector.hpp"

#include "Plane.h"
#include "Table.h"
#include "ExpressionBuilder.h"

using namespace std;

vector<vector<string>> Plane::serialize() {
  return serializeEntries(Table::TPlanes, planes);
}

vector<vector<string>> Plane::find(string query) {
  return findEntries(query, planes);
}

vector<vector<string>> Plane::update(string query, vector<string> fields) {
  return updateEntries(query, fields, planes);
}

void Plane::remove(string query) {
  removeEntries(query, planes);
}

void Plane::updateFS() {
  vector<vector<string>> data = serialize();

  Table::TPlanes.writeFile(data);
}

void Plane::factory(vector<string> rawData, bool fsSync) {
  entriesFactory(planes, rawData, fsSync);
}

vector<string> Plane::serializeLn() {
  vector<string> result;
  result.push_back(planeID);
  result.push_back(maxPassangersCount);

  return result;
}

void Plane::setFields (vector<string> rawData) {
  if(rawData[0].length()) planeID = rawData[0];
  if(rawData[1].length()) maxPassangersCount = rawData[1];
}

Plane::Plane(vector<string> rawData) {
  setFields(rawData);
}

Plane::Plane(){}
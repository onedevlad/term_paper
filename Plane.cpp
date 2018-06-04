#include <iostream>
#include <string>
#include "Vector.hpp"

#include "Utils.h"
#include "Plane.h"
#include "Table.h"

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
  result.push_back(planeName);
  result.push_back(maxPassangersCount);
  result.push_back(maxSpeed);
  result.push_back(fuelCapacity);
  result.push_back(minRWYLength);

  return result;
}

void Plane::setFields (vector<string> rawData) {
  if(Utils::isRawItemValid(rawData, 0)) planeID = rawData[0];
  if(Utils::isRawItemValid(rawData, 1)) planeName = rawData[1];
  if(Utils::isRawItemValid(rawData, 2)) maxPassangersCount = rawData[2];
  if(Utils::isRawItemValid(rawData, 3)) maxSpeed = rawData[3];
  if(Utils::isRawItemValid(rawData, 4)) fuelCapacity = rawData[4];
  if(Utils::isRawItemValid(rawData, 5)) minRWYLength = rawData[5];
}

Plane::Plane(vector<string> rawData) {
  setFields(rawData);
}

Plane::Plane(){}
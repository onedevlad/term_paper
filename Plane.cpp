#include <iostream>
#include <string>
#include <vector>

#include "Plane.h"
#include "Table.h"
#include "Utils.h"

using namespace std;

// Static vectors need to be initialized
vector<Plane> Plane::planes = {};

void Plane::load() {
  Table::TPlanes.parse(Table::TPlanes.readFile(), Plane::factory);
}

vector<vector<string>> Plane::serialize() {
  vector<vector<string>> result;
  result.push_back(Table::TPlanes.headers);

  for(int i=0; i<planes.size(); i++) serializeLn(planes[i]);

  return result;
}

vector<string> Plane::serializeLn(Plane obj) {
  vector<string> result;
  result.push_back(obj.planeID);
  result.push_back(obj.maxPassangersCount);

  return result;
}

void Plane::factory(int _entryLine, vector<string> rawData, bool fsSync) {
  Plane obj(_entryLine, rawData);
  planes.push_back(obj);
  if(fsSync) Table::TPlanes.writeFile(serialize());
}

Plane::Plane(int _entryLine, vector<string> rawData) {
  entryLine = _entryLine;

  planeID = rawData[0];
  maxPassangersCount = rawData[1];
}

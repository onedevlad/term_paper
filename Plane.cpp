#include <iostream>
#include <string>
#include <vector>

#include "Plane.h"
#include "Table.h"
#include "Utils.h"

using namespace std;

vector<vector<string>> Plane::serialize() {
  vector<vector<string>> result;
  result.push_back(Table::TPlanes.getHeaders());

  for(int i=0; i<planes.size(); i++) result.push_back(serializeLn(planes[i]));

  return result;
}

vector<string> Plane::serializeLn(Plane obj) {
  vector<string> result;
  result.push_back(obj.planeID);
  result.push_back(obj.maxPassangersCount);

  return result;
}

void Plane::factory(vector<string> rawData, bool fsSync) {
  Plane obj(rawData);
  planes.push_back(obj);
  if(fsSync) Table::TPlanes.writeFile(serialize());
}

Plane::Plane(vector<string> rawData) {
  planeID = rawData[0];
  maxPassangersCount = rawData[1];
}

#include <iostream>
#include <string>
#include <vector>

#include "Passanger.h"
#include "Table.h"
#include "Utils.h"

using namespace std;

void Passanger::load() {
  Table::TPassangers.parse(Table::TPassangers.readFile(), Passanger::factory);
}

// Static vectors need to be initialized
vector<Passanger> Passanger::passangers = {};

vector<vector<string>> Passanger::serialize() {
  vector<vector<string>> result;
  result.push_back(Table::TPassangers.headers);

  for(int i=0; i<passangers.size(); i++) result.push_back(serializeLn(passangers[i]));

  return result;
}

vector<string> Passanger::serializeLn(Passanger obj) {
  vector<string> result;
  result.push_back(obj.passangerID);
  result.push_back(obj.lastName);
  result.push_back(obj.firstName);
  result.push_back(obj.flightID);

  return result;
}

void Passanger::factory(vector<string> rawData, bool fsSync) {
  Passanger obj(rawData);
  Passanger::passangers.push_back(obj);

  if(fsSync) Table::TPassangers.writeFile(serialize());
}

Passanger::Passanger(vector<string> rawData) {
  passangerID = rawData[0];
  lastName = rawData[1];
  firstName = rawData[2];
  flightID = rawData[3];
}

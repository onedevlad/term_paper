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

  for(int i=0; i<passangers.size(); i++) {
    vector<string> record;
    record.push_back(passangers[i].passangerID);
    record.push_back(passangers[i].lastName);
    record.push_back(passangers[i].firstName);
    record.push_back(passangers[i].flightID);

    result.push_back(record);
  }

  return result;

}

void Passanger::factory(int _entryLine, vector<string> rawData, bool fsSync) {
  Passanger obj(_entryLine, rawData);
  Passanger::passangers.push_back(obj);

  if(fsSync) Table::TPassangers.writeFile(serialize());
}

Passanger::Passanger(int _entryLine, vector<string> rawData) {
  entryLine = _entryLine;

  passangerID = rawData[0];
  lastName = rawData[1];
  firstName = rawData[2];
  flightID = rawData[3];
}

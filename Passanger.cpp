#include <iostream>
#include <string>
#include <vector>

#include "Passanger.h"
#include "Table.h"
#include "Utils.h"

using namespace std;

// Static vectors need to be initialized
vector<Passanger> Passanger::passangers = {};
vector<string> Passanger::headers = {};

void Passanger::load() {
  Table::parseFile(Table::readFile("Passangers"), Passanger::setHeaders, Passanger::factory);
}

vector<vector<string>> Passanger::serialize() {
  vector<vector<string>> result;
  result.push_back(Passanger::headers);

  for(int i=0; i<Passanger::passangers.size(); i++) {
    vector<string> record;
    record.push_back(Passanger::passangers[i].passangerID);
    record.push_back(Passanger::passangers[i].lastName);
    record.push_back(Passanger::passangers[i].firstName);
    record.push_back(Passanger::passangers[i].flightID);

    result.push_back(record);
  }

  return result;
}


void Passanger::setHeaders(vector<string> _headers) {
  headers = _headers;
}

void Passanger::factory(int _entryLine, vector<string> rawData, bool fsSync) {
  Passanger obj(_entryLine, rawData);
  passangers.push_back(obj);
  if(fsSync) Table::writeFile("Passanger", serialize());
}

Passanger::Passanger(int _entryLine, vector<string> rawData) {
  entryLine = _entryLine;

  passangerID = rawData[0];
  lastName = rawData[1];
  firstName = rawData[2];
  flightID = rawData[3];

  // cout << "Created passanger #" << passangerID << " on " << planeID << endl;
}

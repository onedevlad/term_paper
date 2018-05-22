#include <iostream>
#include <string>
#include <sstream>

#include "Cmd.h"
#include "Table.h"
#include "Utils.h"
#include "Flight.h"
#include "Passanger.h"
#include "Plane.h"

using namespace std;

void Cmd::simpleHandler(string cmd) {
  if(cmd == "help") help();
  else if(cmd == "tables") tables();
  else invalid();
}

void Cmd::complexHandler(string cmd) {
  istringstream iss(cmd);
  vector<string> operands;
  string operand;
  while(getline(iss, operand, ' ')) operands.push_back(operand);

  if(operands[0] == "show") show(operands[1]);
  else if(operands[0] == "add") add(operands[1]);
  else if(operands[0] == "find") find(operands[1]);
  else invalid();
}

void Cmd::handler(string cmd) {
  string command = Utils::trim(cmd);
  if(command.find(" ") == string::npos) simpleHandler(command);
  else complexHandler(command);
}

void Cmd::show(string tableName) {
  if(tableName == "flights") Table::TFlights.render();
  else if(tableName == "passangers") Table::TPassangers.render();
  else if(tableName == "planes") Table::TPlanes.render();
  else cout << "Table `" << tableName << "` doesn't exist." << endl;
}

typedef void (*Factory)(int, vector<string>, bool);

void Cmd::add(string fieldName) {
  int size;
  vector<string> headers;
  Factory factory;

  if(fieldName == "flight") {
    headers = Table::TFlights.headers;
    factory = Flight::factory;
    size = Flight::flights.size();
  }
  else if(fieldName == "passanger") {
    headers = Table::TPassangers.headers;
    factory = Passanger::factory;
    size = Passanger::passangers.size();
  }
  else if(fieldName == "plane") {
    headers = Table::TPlanes.headers;
    factory = Plane::factory;
    size = Plane::planes.size();
  }
  else {
    cout << "`" << fieldName << "` is not a valid member." << endl;
    return;
  }

  vector<string> data;
  for(int i=0; i<headers.size(); i++) {
    cout << headers[i] << ": ";
    string value;
    getline(cin, value);
    data.push_back(value);
  }
  factory(size + 1, data, true);
}

void Cmd::find(string tableName) {
  vector<string> headers;

  if(tableName == "flights") headers = Table::TFlights.headers;
  else if(tableName == "passangers") headers = Table::TPassangers.headers;
  else if(tableName == "planes") headers = Table::TPlanes.headers;
  else { invalid(); return; }

  cout << "  " << "Which field would you like to search by?" << endl;

  for(int i=0; i<headers.size(); i++) {
    cout << "    " << i << ") " << headers[i] << endl;
  }
  cout << endl;

  int headerIndex = Utils::askForInt("index", 0, headers.size()-1);
  string searchQuery = Utils::askForStr("search query for " + headers[headerIndex]);

  vector<vector<string>> searchResults;

  if(tableName == "flights") {
    searchResults = Flight::find(headerIndex, searchQuery);
    // cout << searchResults.size() << endl;
    vector<vector<string>> table;
    table.push_back(Table::TFlights.headers);
    table.insert(table.end(), searchResults.begin(), searchResults.end());
    Table::TFlights.renderTable(table);
  }

}

void Cmd::tables() {
  cout << "flights" << endl;
  cout << "passangers" << endl;
  cout << "planes" << endl;
}

void Cmd::help() {

  // Find ...
  // cout << "find - " << endl;
  cout << "tables - show all existing tables" << endl;
  cout << "show T - show table T." << endl;
  cout << "add I - add instance of table T." << endl;
  cout << "help - print this manual." << endl;
  cout << "exit - leave the CLI." << endl;
}

void Cmd::invalid() {
  cout << "Invalid query." << endl;
}

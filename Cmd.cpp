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
  else invalid();
}

void Cmd::handler(string cmd) {
  if(cmd.find(" ") == string::npos) simpleHandler(cmd);
  else complexHandler(cmd);
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
    headers = Flight::headers;
    factory = Flight::factory;
    size = Flight::flights.size();
  }
  else if(fieldName == "passanger") {
    headers = Passanger::headers;
    factory = Passanger::factory;
    size = Passanger::passangers.size();
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

void Cmd::tables() {
  cout << "flights" << endl;
  cout << "passangers" << endl;
  cout << "planes" << endl;
}

void Cmd::help() {
  cout << "tables - show all existing tables" << endl;
  cout << "show T - show table T." << endl;
  cout << "add I - add instance of table T." << endl;
  cout << "help - print this manual." << endl;
  cout << "exit - leave the CLI." << endl;
}

void Cmd::invalid() {
  cout << "Invalid query." << endl;
}

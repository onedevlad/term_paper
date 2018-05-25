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
  cout << endl;

  string command = Utils::trim(cmd);
  if(command.length() == 0) return;
  if(command.find(" ") == string::npos) simpleHandler(command);
  else complexHandler(command);

  cout << endl;
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

string Cmd::getWhereClause() {
  cout << "...> where ";
  string query;
  getline(cin, query);
  return query;
}

void Cmd::find(string tableName) {
  vector<string> headers;

  if(tableName == "flights") headers = Table::TFlights.headers;
  else if(tableName == "passangers") headers = Table::TPassangers.headers;
  else if(tableName == "planes") headers = Table::TPlanes.headers;
  else { invalid(); return; }

  cout << "  " << "List of field substitutions:" << endl;

  for(int i=0; i<headers.size(); i++) cout << "    $" << i << ": " << headers[i] << endl;

  cout << endl;

  string expression = getWhereClause();
  vector<vector<string>> searchResults;
  vector<vector<string>> table;

  if(tableName == "flights") {
    searchResults = Flight::find(expression);
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
  cout << "find T - find fields in table T." << endl;
  cout << "... where E - where clause for previous command (`find`, `update` etc)." << endl;
    cout << "  " << "Supported operators:" << endl;
    cout << '\t' << "priority [()];" << endl;
    cout << '\t' << "interolation [$N]." << endl;
    cout << '\t' << "comparison [<, <=, >, >=, ==, !=, ~];" << endl;
    cout << '\t' << "boolean [&&, ||];" << endl;
    cout << '\t' << "Sample query: ($0 <= 200 && $1 != AB1234) || $2 == 100" << endl;
  cout << "tables - show all existing tables" << endl;
  cout << "show T - show table T." << endl;
  cout << "add I - add instance of table T." << endl;
  cout << "help - print this manual." << endl;
  cout << "exit - leave the CLI." << endl;
}

void Cmd::invalid() {
  cout << "Invalid query." << endl;
}

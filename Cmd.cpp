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

void Cmd::invalid() {
  cout << "Invalid query." << endl;
}


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
  else if(operands[0] == "update") update(operands[1]);
  else if(operands[0] == "remove") remove(operands[1]);
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

typedef void (*Factory)(vector<string>, bool);

void Cmd::add(string fieldName) {
  vector<string> headers;
  Factory factory;

  if(fieldName == "flight") {
    headers = Table::TFlights.headers;
    factory = Flight::factory;
  }
  else if(fieldName == "passanger") {
    headers = Table::TPassangers.headers;
    factory = Passanger::factory;
  }
  else if(fieldName == "plane") {
    headers = Table::TPlanes.headers;
    factory = Plane::factory;
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
  factory(data, true);
}

string Cmd::getWhereClause() {
  cout << "...> where ";
  string query;
  getline(cin, query);
  return query;
}

vector<string> Cmd::getReplacements(vector<string> headers) {
  vector<string> replacements;

  cout << "Specify updated values (leave empty to keep as is):" << endl;
  for(int i=0; i<headers.size(); i++) {
    cout << headers[i] << ": ";
    string newValue;
    getline(cin, newValue);
    replacements.push_back(newValue);
  }
  cout << endl;

  return replacements;
}

void Cmd::printSubstitutions (vector<string> substitutions) {
  cout << "  " << "List of field substitutions:" << endl;
  for(int i=0; i<substitutions.size(); i++)
    cout << "    $" << i << ": " << substitutions[i] << endl;
  cout << endl;
}

vector<string> Cmd::getHeadersByTableName(string tableName) {
  vector<string> headers;

  if(tableName == "flights") headers = Table::TFlights.headers;
  else if(tableName == "passangers") headers = Table::TPassangers.headers;
  else if(tableName == "planes") headers = Table::TPlanes.headers;

  return headers;
}

void Cmd::find(string tableName) {
  vector<vector<string>> results;
  vector<vector<string>> tableToRender;
  vector<string> headers = getHeadersByTableName(tableName);
  tableToRender.push_back(headers);

  if(headers.size()) {
    printSubstitutions(headers);
    string expression = getWhereClause();
    if(tableName == "flights") {
      results = Flight::find(expression);
      tableToRender.insert(tableToRender.end(), results.begin(), results.end());
      Table::TFlights.renderTable(tableToRender);
    }
  }
  else return invalid();
}

void Cmd::update(string tableName) {
  vector<vector<string>> results;
  vector<vector<string>> tableToRender;
  vector<string> headers = getHeadersByTableName(tableName);
  tableToRender.push_back(headers);

  if(headers.size()) {
    printSubstitutions(headers);
    string expression = getWhereClause();

    vector<string> replacements = getReplacements(headers);

    if(tableName == "flights") {
      results = Flight::update(expression, replacements);
      tableToRender.insert(tableToRender.end(), results.begin(), results.end());
      Table::TFlights.renderTable(tableToRender);
    }
  }
  else return invalid();
}

void Cmd::remove(string tableName) {
  vector<string> headers = getHeadersByTableName(tableName);
  if(headers.size()) {
    printSubstitutions(headers);
    string expression = getWhereClause();
    if(tableName == "flights") Flight::remove(expression);
  }
  else return invalid();
}

void Cmd::tables() {
  cout << "flights" << endl;
  cout << "passangers" << endl;
  cout << "planes" << endl;
}

void Cmd::help() {
  cout << "tables - print all existing tables' names." << endl;
  cout << "find T - find field(s) in table T." << endl;
  cout << "show T - show table T." << endl;
  cout << "add I - add instance of table T." << endl;
  cout << "update T - update field(s) in table T, which match the `where` clause." << endl;
  cout << "remove T - remove field(s) in table T, which match the `where` clause." << endl;
  cout << "... where E - where clause for previous command (`find`, `update` etc)." << endl;
    cout << "  " << "Supported operators:" << endl;
    cout << '\t' << "priority [()];" << endl;
    cout << '\t' << "interolation [$N]." << endl;
    cout << '\t' << "comparison [<, <=, >, >=, ==, !=, ~];" << endl;
    cout << '\t' << "boolean [&&, ||];" << endl;
    cout << '\t' << "Sample query: ($0 <= 200 && $1 != AB1234) || $2 == 100" << endl;
  cout << "help - print this manual." << endl;
  cout << "exit - leave the CLI." << endl;
}

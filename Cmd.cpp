#include <iostream>
#include <string>
#include <sstream>

#include "Cmd.h"
#include "Table.h"
#include "Renderer.h"
#include "Utils.h"
#include "Flight.h"
#include "Passanger.h"
#include "Plane.h"

using namespace std;

void Cmd::invalidMsg() {
  cout << "Invalid query." << endl;
}

void Cmd::simpleHandler(string cmd) {
  if(cmd == "help") help();
  else if(cmd == "tables") tables();
  else invalidMsg();
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
  else invalidMsg();
}

Cmd::Cmd(string cmd) {
  cout << endl;

  string command = Utils::trim(cmd);
  if(command.length() == 0) return;
  if(command.find(" ") == string::npos) simpleHandler(command);
  else complexHandler(command);

  cout << endl;
}

void Cmd::noTableMsg(string tableName) {
  cout << "Table `" << tableName << "` doesn't exist." << endl;
}

void Cmd::enoentMsg() {
  cout << "No results found." << endl;
}

void Cmd::show(string tableName) {
  if(tableName == "flights") Table::TFlights.render();
  else if(tableName == "passangers") Table::TPassangers.render();
  else if(tableName == "planes") Table::TPlanes.render();
  else noTableMsg(tableName);
}

typedef void (*Factory)(vector<string>, bool);

void Cmd::add(string fieldName) {
  vector<string> headers;
  Factory factory;

  if(fieldName == "flight") {
    headers = Table::TFlights.getHeaders();
    factory = Flight::factory;
  }
  else if(fieldName == "passanger") {
    headers = Table::TPassangers.getHeaders();
    factory = Passanger::factory;
  }
  else if(fieldName == "plane") {
    headers = Table::TPlanes.getHeaders();
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

string Cmd::getWhereClause(vector<string> headers) {
  cout << "  " << "Use short-hand aliases inside your query instead of full fields' names:" << endl;

  for(int i=0; i<headers.size(); i++)
    cout << "    $" << i << ": " << headers[i] << endl;
  cout << endl << "...> where ";

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

vector<string> Cmd::getHeadersByTableName(string tableName) {
  vector<string> headers;

  if(tableName == "flights") headers = Table::TFlights.getHeaders();
  else if(tableName == "passangers") headers = Table::TPassangers.getHeaders();
  else if(tableName == "planes") headers = Table::TPlanes.getHeaders();

  return headers;
}

void Cmd::find(string tableName) {
  vector<string> headers = getHeadersByTableName(tableName);

  if(headers.size()) {
    vector<vector<string>> results;
    string expression = getWhereClause(headers);

    if(tableName == "flights") results = Flight::find(expression);
    if(tableName == "planes") results = Plane::find(expression);
    if(tableName == "passangers") results = Passanger::find(expression);

    if(results.size()) {
      Renderer resultingTable(headers, results);
      resultingTable.render();
    } else enoentMsg();
  }
  else return noTableMsg(tableName);
}

void Cmd::update(string tableName) {
  vector<string> headers = getHeadersByTableName(tableName);

  if(headers.size()) {
    vector<vector<string>> results;
    string expression = getWhereClause(headers);
    vector<string> replacements = getReplacements(headers);

    if(tableName == "flights") results = Flight::update(expression, replacements);
    if(tableName == "planes") results = Plane::update(expression, replacements);
    if(tableName == "passanger") results = Passanger::update(expression, replacements);

    if(results.size()) {
      Renderer resultingTable(headers, results);
      resultingTable.render();
    } else enoentMsg();
  }
  else return noTableMsg(tableName);
}

typedef void (*Remover)(string);

void Cmd::remove(string tableName) {
  vector<string> headers = getHeadersByTableName(tableName);

  if(headers.size()) {
    string expression = getWhereClause(headers);
    vector<vector<string>> results;
    Remover remover;
    if(tableName == "flights") { results = Flight::find(expression); remover = Flight::remove; }
    if(tableName == "planes") { results = Plane::find(expression); remover = Plane::remove; }
    if(tableName == "passanger") { results = Passanger::find(expression); remover = Passanger::remove; }

    if(results.size()) {
      cout << "The following fields will be permanently deleted." << endl;
      Renderer resultingTable(headers, results);
      resultingTable.render();
      cout << "Do you want to continue? (Y/n): ";
      string answer;
      getline(cin, answer);
      if(answer[0] == 'Y' || answer[0] == 'y') remover(expression);
      else cout << "Aborting..." << endl;
    }
    else enoentMsg();
  }
  else return noTableMsg(tableName);
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

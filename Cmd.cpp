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

#include "Vector.hpp"

using namespace std;

void Cmd::invalidMsg() {
  cout << "Invalid query." << endl;
}

void Cmd::simpleHandler(string const& cmd) {
  if(cmd == "help") help();
  else if(cmd == "tables") tables();
  else invalidMsg();
}

void Cmd::complexHandler(string const& cmd) {
  vector<string> operands = Utils::strSplitBySpace(cmd);


  int whereClausePosition = cmd.find("where");

  if(operands[0] == "show") show(operands[1]);
  else if(operands[0] == "add") add(operands[1]);
  else if(operands[0] == "interpolations") interpolations(operands[1]);
  else if(operands.size() > 2 && whereClausePosition != string::npos) {
    string expression = Utils::slice(cmd, whereClausePosition + 5, cmd.length());
    if(operands[0] == "find") find(operands[1], expression);
    else if(operands[0] == "update") update(operands[1], expression);
    else if(operands[0] == "remove") remove(operands[1], expression);
  }
  else invalidMsg();
}

Cmd::Cmd(string const& cmd) {
  cout << endl;

  string command = Utils::trim(cmd);
  if(command.length() == 0) return;
  if(command.find(" ") == string::npos) simpleHandler(command);
  else complexHandler(command);

  cout << endl;
}

void Cmd::noTableMsg(string const& tableName) {
  cout << "Table `" << tableName << "` doesn't exist." << endl;
}

void Cmd::enoentMsg() {
  cout << "No results found." << endl;
}

void Cmd::show(string const& tableName) {
  if(tableName == "flights") Table::TFlights.render();
  else if(tableName == "passangers") Table::TPassangers.render();
  else if(tableName == "planes") Table::TPlanes.render();
  else noTableMsg(tableName);
}

typedef void (*Factory)(vector<string>, bool);

void Cmd::add(string const& fieldName) {
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

void Cmd::interpolations(string const& tableName) {
  vector<string> headers = getHeadersByTableName(tableName);
  if(headers.size()) {
    cout << "Use these indices for corresponding substitutions." << endl;
    for(int i=0; i<headers.size(); i++)
      cout << "\t$" << i << ": " << headers[i] << endl;
  } else noTableMsg(tableName);
}

vector<string> Cmd::getReplacements(vector<string>& headers) {
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

vector<string> Cmd::getHeadersByTableName(string const& tableName) {
  vector<string> headers;

  if(tableName == "flights") headers = Table::TFlights.getHeaders();
  else if(tableName == "passangers") headers = Table::TPassangers.getHeaders();
  else if(tableName == "planes") headers = Table::TPlanes.getHeaders();

  return headers;
}

void Cmd::find(string const& tableName, string const& expression) {
  vector<string> headers = getHeadersByTableName(tableName);

  if(headers.size()) {
    vector<vector<string>> results;

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

void Cmd::update(string const& tableName, string const& expression) {
  vector<string> headers = getHeadersByTableName(tableName);

  if(headers.size()) {
    vector<vector<string>> results;
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

void Cmd::remove(string const& tableName, string const& expression) {
  vector<string> headers = getHeadersByTableName(tableName);

  if(headers.size()) {
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
  cout << "find Tabl where Expr - find field(s) in table T, which match the `where` clause." << endl;
  cout << "show Tabl - show table Tabl." << endl;
  cout << "add Inst - add instance of table Tabl." << endl;
  cout << "update Tabl where Expr - update field(s) in table T, which match Expr." << endl;
  cout << "remove Tabl where Expr - remove field(s) in table T, which match Expr." << endl;
  cout << "  " << "Supported Expr operators:" << endl;
    cout << '\t' << "priority [()];" << endl;
    cout << '\t' << "interolation [$N] (N being the row index)." << endl;
    cout << '\t' << "comparison [<, <=, >, >=, ==, !=, ~];" << endl;
    cout << '\t' << "boolean [&&, ||];" << endl;
    cout << '\t' << "Sample Expr: ($0 <= 200 && $1 != AB1234) || $2 == 100" << endl;
  cout << "interpolations Tabl - print an interpolations list for table Tabl.";
  cout << "help - print this manual." << endl;
  cout << "exit - leave the CLI." << endl;
}

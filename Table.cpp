#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "Vector.hpp"

#include "Table.h"
#include "Renderer.h"

using namespace std;


void Table::parse(vector<string> file, void (*factoryCB)(vector<string>, bool)) {
  for(int i=0; i<file.size(); i++) {
    vector<string> items;
    string item;

    istringstream iss(file[i]);
    while(getline(iss, item, '\t')) items.push_back(item);

    if(!i) headers = items;
    else factoryCB(items, false);
  }
}

void Table::render() {
  Renderer table(serializer());
  table.render();
}

vector<string> Table::getHeaders() {
  return headers;
}

Table::Table(string _tableName, vector<vector<string>> (*_serializer)(), void (*_factory)(vector<string>, bool)) {
  tableName = _tableName;
  serializer = _serializer;
  parse(readFile(), _factory);
}

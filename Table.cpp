#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

#include "Table.h"

using namespace std;

vector<string> Table::readFile() {
  string line;
  vector<string> file;

  ifstream fss ("./storage/" + tableName + ".txt");
  while(getline(fss, line)) file.push_back(line);
  fss.close();

  return file;
};

void Table::writeFile(vector<vector<string>> data) {
  ofstream table;
  table.open("./storage/" + tableName + ".txt");
  for(int i=0; i<data.size(); i++) {
    for(int j=0; j<data[i].size(); j++) {
      table << data[i][j];
      if(j != data[i].size() - 1) table << '\t';
    }
    table << endl;
  }
  table.close();
}

void Table::parse(vector<string> file, void (*factoryCB)(int, vector<string>, bool)) {
  for(int i=0; i<file.size(); i++) {
    vector<string> items;
    string item;

    istringstream iss(file[i]);

    while(getline(iss, item, '\t')) items.push_back(item);

    if(!i) headers = items;
    else factoryCB(i, items, false);
  }
}

void Table::render() {
  renderTable(serializer());
}

Table::Table(string _tableName, vector<vector<string>> (*_serializer)()) {
  tableName = _tableName;
  serializer = _serializer;
  // Wouldn't it be nice to do smth like this?
  // parse(readFile(), factory);
  // NO. (c) G++ devs.
}

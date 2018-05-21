#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

#include "Table.h"

#include "Flight.h"
#include "Plane.h"
#include "Passanger.h"

using namespace std;

vector<string> Flight::headers = {};

void Table::setHeaders(vector<string> _headers) {
  headers = _headers;
}

vector<string> Table::readFile(string filename) {
  string line;
  vector<string> file;

  ifstream fss ("./storage/" + filename + ".txt");
  while(getline(fss, line)) file.push_back(line);
  fss.close();

  return file;
};

void Table::writeFile(string filename, vector<vector<string>> data) {
  ofstream table;
  table.open("./storage/" + filename + ".txt");
  for(int i=0; i<data.size(); i++) {
    for(int j=0; j<data[i].size(); j++) {
      table << data[i][j];
      if(j != data[i].size() - 1) table << '\t';
    }
    table << endl;
  }
  table.close();
}

void Table::parseFile(vector<string> file, void (*headersCB)(vector<string>), void (*factoryCB)(int, vector<string>, bool)) {
  for(int i=0; i<file.size(); i++) {
    vector<string> items;
    string item;

    istringstream iss(file[i]);

    while(getline(iss, item, '\t')) items.push_back(item);

    if(!i) headersCB(items);
    else factoryCB(i, items, false);
  }
}

void Table::render() {
  renderTable(serializer());
}

Table::Table(string tableName, vector<vector<string>> (*_serializer)()) {
  serializer = _serializer;
}

// class Table {
// private:
//   int tableWidth;

//   void fsWrite(string name, vector<string> headers) {
//     ofstream table;
//     table.open("./storage/" + name + ".txt");
//     for(int i=0; i<headers.size(); i++) {
//       table << headers[i];
//       if(i != headers.size() - 1) table << "\t";
//     }

//     table.close();
//   }

// public:
//   string tableName;
//   vector<string> headers;

//   void createTable() {
//     tableName = Utils::askForStr("new table name");
//     tableWidth = Utils::askForInt("table width", 1, 10);
//     for(int i=1; i<=tableWidth; i++) {
//       headers.push_back(Utils::askForStr("header #"+to_string(i)));
//     }
//   }

//   Table() {
//     // fsWrite(tableName, headers);

//     vector<vector<string>> table;
//     table.push_back(headers);
//     Renderer newTable(table);
//   }
// };
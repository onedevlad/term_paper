#include <sstream>
#include <fstream>
#include <string>
#include <vector>

#include "FS.h"

vector<string> FS::readFile() {
  string line;
  vector<string> file;

  ifstream fss ("./storage/" + tableName + ".txt");
  while(getline(fss, line)) file.push_back(line);
  fss.close();

  return file;
};

void FS::writeFile(vector<vector<string>> data) {
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
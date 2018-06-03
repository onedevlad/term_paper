#include <string>
#include "Vector.hpp"

#ifndef FS_H
#define FS_H

using namespace std;

class FS {
  protected:
    string tableName;
  public:
    vector<string> readFile();
    void writeFile(vector<vector<string>>&);
};

#endif

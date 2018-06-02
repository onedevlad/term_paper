#include <string>
#include <vector>

#ifndef FS_H
#define FS_H

using namespace std;

class FS {
  protected:
    string tableName;
  public:
    vector<string> readFile();
    void writeFile(vector<vector<string>> const&);
};

#endif

#include <string>
#include <vector>

#ifndef CMD_H
#define CMD_H

using namespace std;

class Cmd {
  private:
    vector<string> getHeadersByTableName(string);
    vector<string> getReplacements(vector<string>);
    string getWhereClause(vector<string>);
    void simpleHandler(string);
    void complexHandler(string);
    void show(string);
    void add(string);
    void update(string);
    void remove(string);
    void tables();
    void find(string);
    void help();
    void invalidMsg();
    void noTableMsg(string);
    void enoentMsg();
  public:
    Cmd(string);
};

#endif
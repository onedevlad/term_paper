#ifndef CMD_H
#define CMD_H

#include <string>
#include <vector>

using namespace std;

class Cmd {
  private:
    vector<string> getHeadersByTableName(string const&);
    vector<string> getReplacements(vector<string>&);
    void simpleHandler(string const&);
    void complexHandler(string const&);
    void show(string const&);
    void add(string const&);
    void update(string const&, string const&);
    void remove(string const&, string const&);
    void tables();
    void find(string const&, string const&);
    void interpolations(string const&);
    void help();
    void invalidMsg();
    void noTableMsg(string const&);
    void enoentMsg();
  public:
    Cmd(string const&);
};

#endif
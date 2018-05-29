#ifndef PASSANGER_H
#define PASSANGER_H

#include <string>
#include <vector>

#include "Entry.hpp"

using namespace std;

class Passanger : protected Entry {
  private:
    static vector<Passanger> passangers;
    string passangerID;
    string lastName;
    string firstName;
    string flightID;

  public:
    static vector<vector<string>> serialize();
    static void updateFS();
    static vector<vector<string>> find(string);
    static vector<vector<string>> update(string, vector<string>);
    static void remove(string);
    static void factory(vector<string>, bool);

    vector<string> serializeLn();
    void setFields(vector<string>);
    Passanger(vector<string>);
};

#endif
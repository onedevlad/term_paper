#ifndef PASSANGER_H
#define PASSANGER_H

#include <string>
#include <vector>

using namespace std;

class Passanger {
  private:
    static vector<Passanger> passangers;
    string passangerID;
    string lastName;
    string firstName;
    string flightID;

  public:
    static vector<vector<string>> serialize();
    static vector<string> serializeLn(Passanger);
    static void factory(vector<string>, bool);
    Passanger(vector<string>);
};

#endif
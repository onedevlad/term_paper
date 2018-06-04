#ifndef PLANE_H
#define PLANE_H

#include <string>
#include "Vector.hpp"

#include "Entry.hpp"

using namespace std;

class Plane : protected Entry {
  private:
    static vector<Plane*> planes;
    string planeID;
    string planeName;
    string maxPassangersCount;
    string maxSpeed;
    string fuelCapacity;
    string minRWYLength;

  public:
    static vector<vector<string>> serialize();
    static void updateFS();
    static vector<vector<string>> find(string);
    static vector<vector<string>> update(string, vector<string>);
    static void remove(string);
    static void factory(vector<string>, bool);

    vector<string> serializeLn();
    void setFields(vector<string>);
    Plane(vector<string>);
    Plane();
};

#endif
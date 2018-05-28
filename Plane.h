#ifndef PLANE_H
#define PLANE_H

#include <string>
#include <vector>

using namespace std;

class Plane {
  private:
    static vector<Plane> planes;
    string planeID;
    string maxPassangersCount;

  public:
    static vector<vector<string>> serialize();
    static vector<string> serializeLn(Plane);
    static void load();
    static void factory(vector<string>, bool);
    Plane(vector<string>);
};

#endif
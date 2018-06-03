#ifndef TABLE_H
#define TABLE_H

#include <string>
#include "Vector.hpp"

#include "FS.h"


using namespace std;
typedef vector<vector<string>> (*Serializer)();


class Table : public FS {
  private:
    Serializer serializer;
    vector<string> headers;

  public:
    static Table TFlights;
    static Table TPassangers;
    static Table TPlanes;
    void parse(vector<string>, void (*)(vector<string>, bool));
    void render();
    vector<string> getHeaders();
    Table(string, vector<vector<string>>(*)(), void(*)(vector<string>, bool));
};

#endif
#include <string>
#include <vector>


#ifndef PLANE_H
#define PLANE_H

class Plane {
  public:
    static std::vector<Plane> planes;
    int entryLine;
    std::string planeID;
    std::string maxPassangersCount;
    static std::vector<std::vector<std::string>> serialize();
    static std::vector<std::string> serializeLn(Plane);
    static void load();
    static void factory(int, std::vector<std::string>, bool);
    Plane(int, std::vector<std::string>);
};

#endif
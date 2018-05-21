#include <string>
#include <vector>


#ifndef PLANE_H
#define PLANE_H

class Plane {
  public:
    static std::vector<Plane> planes;
    int entryLine;
    std::string planeID;
    int maxPassangersCount;
    static std::vector<std::vector<std::string>> serialize();
    static void load();
    static void factory(int, std::vector<std::string>, bool);
    Plane(int, std::vector<std::string>);
};

#endif
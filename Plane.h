#include <string>
#include <vector>


#ifndef PLANE_H
#define PLANE_H

class Plane {
  private:
    static std::vector<Plane> planes;
    std::string planeID;
    std::string maxPassangersCount;

  public:
    static std::vector<std::vector<std::string>> serialize();
    static std::vector<std::string> serializeLn(Plane);
    static void load();
    static void factory(std::vector<std::string>, bool);
    Plane(std::vector<std::string>);
};

#endif
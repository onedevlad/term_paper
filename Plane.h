#include <string>
#include <vector>


#ifndef PLANE_H
#define PLANE_H

class Plane {
  public:
    static std::vector<std::string> headers;
    static std::vector<Plane> flights;
    int entryLine;
    std::string planeID;
    int maxPassangersCount;
    static void load();
    static void setHeaders(std::vector<std::string>);
    static std::vector<std::vector<std::string>> serialize();
    static void factory(int, std::vector<std::string>);
    Flight(int, std::vector<std::string>);
};

#endif
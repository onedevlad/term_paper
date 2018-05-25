#include <string>
#include <vector>

#ifndef PASSANGER_H
#define PASSANGER_H

class Passanger {
  public:
    static std::vector<Passanger> passangers;
    int entryLine;

    std::string passangerID;
    std::string lastName;
    std::string firstName;
    std::string flightID;

    static std::vector<std::vector<std::string>> serialize();
    static std::vector<std::string> serializeLn(Passanger);
    static void factory(int, std::vector<std::string>, bool);
    static void load();
    Passanger(int, std::vector<std::string>);
};

#endif
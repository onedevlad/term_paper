#include <string>
#include <vector>

#ifndef PASSANGER_H
#define PASSANGER_H

class Passanger {
  private:
    static std::vector<Passanger> passangers;
    std::string passangerID;
    std::string lastName;
    std::string firstName;
    std::string flightID;

  public:
    static std::vector<std::vector<std::string>> serialize();
    static std::vector<std::string> serializeLn(Passanger);
    static void factory(std::vector<std::string>, bool);
    static void load();
    Passanger(std::vector<std::string>);
};

#endif
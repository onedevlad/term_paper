#include <string>
#include <vector>

#ifndef CMD_H
#define CMD_H

class Cmd {
  private:

    static std::vector<std::string> getHeadersByTableName(std::string);
    static std::vector<std::string> getReplacements(std::vector<std::string>);
    static void printSubstitutions(std::vector<std::string>);
  public:
    static void simpleHandler(std::string);
    static void complexHandler(std::string);
    static void handler(std::string);
    static void show(std::string);
    static void add(std::string);
    static void update(std::string);
    static void remove(std::string);
    static void tables();
    static std::string getWhereClause();
    static void find(std::string);
    static void help();
    static void invalid();
};

#endif
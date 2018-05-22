#include <string>

#ifndef CMD_H
#define CMD_H

class Cmd {
  public:
    static void simpleHandler(std::string);
    static void complexHandler(std::string);
    static void handler(std::string);
    static void show(std::string);
    static void add(std::string);
    static void tables();
    static void find(std::string);
    static void help();
    static void invalid();
};

#endif
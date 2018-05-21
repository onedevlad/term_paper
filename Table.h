#include <string>
#include <vector>

#include "Renderer.h"

#ifndef TABLE_H
#define TABLE_H

typedef std::vector<std::vector<std::string>> (*Serializer)();

class Table : public Renderer {
public:
  Serializer serializer;
  static Table TFlights;
  static Table TPassangers;
  static Table TPlanes;
  static std::vector<std::string> readFile(std::string);
  static void parse(std::vector<std::string>, void (*)(std::vector<std::string>), void (*)(int, std::vector<std::string>, bool));
  void render();
  Table(std::vector<std::vector<std::string>>(*)());
};

#endif
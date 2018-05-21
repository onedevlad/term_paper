#include <string>
#include <vector>

#include "Renderer.h"

#ifndef TABLE_H
#define TABLE_H

typedef std::vector<std::vector<std::string>> (*Serializer)();

class Table : public Renderer {
public:
  static Table TFlights;
  static Table TPassangers;
  static Table TPlanes;
  Serializer serializer;
  <vector::string> headers;
  void setHeaders(std::vector<std::string>);
  static std::vector<std::string> readFile(std::string);
  static void writeFile(std::string, std::vector<std::vector<std::string>>);
  static void parseFile(std::vector<std::string>, void (*)(std::vector<std::string>), void (*)(int, std::vector<std::string>, bool));
  void render();
  Table(std::string, std::vector<std::vector<std::string>>(*)());
};

#endif
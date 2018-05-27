#include <string>
#include <vector>

#include "Renderer.h"

#ifndef TABLE_H
#define TABLE_H

typedef std::vector<std::vector<std::string>> (*Serializer)();

class Table : public Renderer {
private:
  std::string tableName;
public:
  std::vector<std::string> headers;
  Serializer serializer;
  static Table TFlights;
  static Table TPassangers;
  static Table TPlanes;
  std::vector<std::string> readFile();
  void writeFile(std::vector<std::vector<std::string>>);
  void parse(std::vector<std::string>, void (*)(std::vector<std::string>, bool));
  void render();
  Table(std::string, std::vector<std::vector<std::string>>(*)());
};

#endif
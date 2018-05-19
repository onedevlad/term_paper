#ifndef TABLE_H
#define TABLE_H

class Table {
public:
  std::vector<std::string> headers;
  static std::vector<std::string> readFile(std::string);
  static void parse(std::vector<std::string>, void (*)(std::vector<std::string>), void (*)(int, std::vector<std::string>));
};

#endif
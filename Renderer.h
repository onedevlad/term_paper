#include <string>
#include <vector>

#ifndef RENDERER_H
#define RENDERER_H

class Renderer {
  private:
    int colsCount;
    int maxColWidth;
    int tableWidth;
    void analyse(std::vector<std::vector<std::string>> table);
    std::string padCenter(int, const std::string&);
    std::string getRowSeparator(bool);
    void render(std::vector<std::vector<std::string>>);
  public:
    Renderer(std::vector<std::vector<std::string>>);
};

#endif
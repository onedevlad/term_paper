#include <string>
#include <vector>

#ifndef RENDERER_H
#define RENDERER_H

class Renderer {
  private:
    int colsCount=0;
    int maxColWidth=0;
    int tableWidth=0;
    std::string padCenter(int, const std::string&);
    std::string getRowSeparator(bool);
    void analyseTable(std::vector<std::vector<std::string>>);
  public:
    void renderTable(std::vector<std::vector<std::string>>);
};

#endif
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
  public:
    void analyseTable(std::vector<std::vector<std::string>>);
    void analyseLine(std::vector<std::string>);
    std::string getRowSeparator(bool);
    void renderTable(std::vector<std::vector<std::string>>);
};

#endif
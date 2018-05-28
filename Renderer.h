#ifndef RENDERER_H
#define RENDERER_H

#include <string>
#include <vector>

using namespace std;

class Renderer {
  private:
    vector<vector<string>> table;
    int colsCount=0;
    int maxColWidth=0;
    int tableWidth=0;
    string padCenter(int, const string&);
    string getRowSeparator(bool);
    void analyse();
  public:
    void render();
    Renderer(vector<vector<string>>);
    Renderer(vector<string>, vector<vector<string>>);
};

#endif
#include <iostream>
#include <vector>
#include <string>

#include "Renderer.h"

using namespace std;


string Renderer::padCenter(int width, const string& str) {
  int len = str.length();
  if(width < len) return str;

  int diff = width - len;
  int padL = diff/2;
  int padR = diff - padL;
  return string(padL, ' ') + str + string(padR, ' ');
}

void Renderer::analyseTable(vector<vector<string>> table) {
  maxColWidth = table[0][0].length();
  colsCount = table[0].size();

  for(int i=0; i<table.size(); i++) {
    if(table[i].size() > colsCount) colsCount = table[i].size();

    for(int j=0; j<table[i].size(); j++) {
      if(table[i][j].length() > maxColWidth) maxColWidth = table[i][j].length();
    }
  }
  maxColWidth += 2; //To allow printing 2 spaces around longest line

  tableWidth = colsCount * maxColWidth + colsCount + 1;
}

string Renderer::getRowSeparator(bool outermostRow) {
  char cornerChar = outermostRow ? '+' : '|';
  return cornerChar + string(tableWidth - 2, '-') + cornerChar;
}

void Renderer::renderTable(vector<vector<string>> table) {
  analyseTable(table);

  cout << getRowSeparator(true);
  cout << endl;

  for(int i=0; i<table.size(); i++) {
    cout << '|';

    for(int j=0; j<table[i].size(); j++) {
      cout << padCenter(maxColWidth, table[i][j]) << '|';
    }

    bool lastRow = i == table.size()-1;
    cout << endl;
    cout << getRowSeparator(lastRow);
    cout << endl;
  }
}
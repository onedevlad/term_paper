#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Utils.h"

using namespace std;


string Utils::enterPrompt = "Please, enter ";

string Utils::trim(const string& str) {
  size_t first = str.find_first_not_of(' ');
  if (string::npos == first) return str;
  size_t last = str.find_last_not_of(' ');
  return str.substr(first, (last - first + 1));
}

string Utils::replaceChar(string str, char from, char to) {
  for(string::iterator it = str.begin(); it != str.end(); it++)
    if(*it == from) *it = to;
  return str;
}

bool Utils::isNumber(const string& s) {
  string::const_iterator it = s.begin();
  while (it != s.end() && isdigit(*it)) ++it;
  return !s.empty() && it == s.end();
}

bool Utils::contains(string str, string substr) {
  return str.find(substr) != string::npos;
}

bool Utils::contains(string str, char ch) {
  return str.find(ch) != string::npos;
}

string Utils::slice(string str, int start, int end) {
  return str.substr(start, end-start);
}

int Utils::strToInt(string str) {
  if(isNumber(str)) return stol(str);
  return -1;
}

int Utils::askForInt(string item, int minBound, int maxBound) {
  int enteredInt;

  enter:
    cout << Utils::enterPrompt << item << " ("<< minBound <<'-'<< maxBound << "): ";
    string userInput;
    getline(cin, userInput);

  enteredInt = Utils::strToInt(Utils::trim(userInput));
  if(enteredInt < minBound || enteredInt > maxBound) {
    cout << "NaN value provided. Try again." << endl;
    goto enter;
  }
  return enteredInt;
}

vector<string> Utils::strSplitBySpace(string str) {
  istringstream iss(str);
  vector<string> words;
  string word;
  while(getline(iss, word, ' ')) words.push_back(word);
  return words;
}

string Utils::askForStr(string item) {
  cout << Utils::enterPrompt << " " << item << ": ";
  string userInput;
  getline(cin, userInput);
  return Utils::trim(userInput);
}

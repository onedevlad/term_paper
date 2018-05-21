#include <iostream>
#include <string>
#include <vector>

#include "Utils.h"

using namespace std;


string Utils::enterPrompt = "Please, enter";

string Utils::trim(const string& str) {
  size_t first = str.find_first_not_of(' ');
  if (string::npos == first) return str;
  size_t last = str.find_last_not_of(' ');
  return str.substr(first, (last - first + 1));
}

bool Utils::isNumber(const string& s) {
  string::const_iterator it = s.begin();
  while (it != s.end() && isdigit(*it)) ++it;
  return !s.empty() && it == s.end();
}

int Utils::strToInt(string str) {
  if(isNumber(str)) return stol(str);
  return -1;
}

int Utils::askForInt(string item, int minBound, int maxBound) {
  int enteredInt;

  enter:
    cout << Utils::enterPrompt << ' ' << item << " ("<< minBound <<'-'<< maxBound << "): ";
    string userInput;
    getline(cin, userInput);

  enteredInt = Utils::strToInt(Utils::trim(userInput));
  if(enteredInt < minBound || enteredInt > maxBound) {
    cout << "Invalid data provided. Try again." << endl;
    goto enter;
  }
  return enteredInt;
}

string Utils::askForStr(string item) {
  cout << Utils::enterPrompt << " " << item << ": ";
  string userInput;
  getline(cin, userInput);
  return Utils::trim(userInput);
}

void Utils::setHeaders(vector<string>* originalHeaders, vector<string>* updatedHeaders) {
  originalHeaders->clear();
  originalHeaders->insert(originalHeaders->end(), updatedHeaders->begin(), updatedHeaders->end());
}

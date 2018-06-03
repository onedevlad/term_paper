#ifndef ENTRY_H
#define ENTRY_H

#include <string>

#include <typeinfo>

#include "ExpressionBuilder.h"
#include "Table.h"
#include "Vector.hpp"

using namespace std;


class Entry {
  protected:
    template<class T> static vector<T> getMatchingEntries(string const&, vector<T>&);
    template<class T> static vector<vector<string>> findEntries(string const&, vector<T>&);
    template<class T> static vector<vector<string>> serializeEntries(Table&, vector<T>&);
    template<class T> static void removeEntries(string const&, vector<T>&);
    template<class T> static void entriesFactory(vector<T>&, vector<string>, bool);
    template<class T> static vector<vector<string>> updateEntries(string const&, vector<string>, vector<T>&);
};

template<class T>
vector<T> Entry::getMatchingEntries(string const& query, vector<T>& entries) {
  vector<T> result;

  for(int i=0; i<entries.size(); i++) {
    vector<string> line = entries[i].serializeLn();
    ExpressionBuilder expression = ExpressionBuilder(line);
    bool lineMatches = expression.parse(query);
    if(lineMatches) result.push_back(entries[i]);
  }

  return result;
}

template<class T>
vector<vector<string>> Entry::findEntries(string const& query, vector<T>& entries) {
  vector<vector<string>> result;
  vector<T> matchingEntries = getMatchingEntries(query, entries);

  for(int i=0; i<matchingEntries.size(); i++)
    result.push_back(matchingEntries[i].serializeLn());
   return result;
}

template<class T>
vector<vector<string>> Entry::serializeEntries(Table& parent, vector<T>& entries) {
  vector<vector<string>> result;
  result.push_back(parent.getHeaders());

  for(int i=0; i<entries.size(); i++) {
    result.push_back(entries[i].serializeLn());
  }

  return result;
}

template<class T>
void Entry::removeEntries(string const& query, vector<T>& entries) {
  for(int i=0; i<entries.size(); i++) {
    ExpressionBuilder expression = ExpressionBuilder(entries[i].serializeLn());
    bool lineMatches = expression.parse(query);
    if(lineMatches) entries.erase(i);
  }
  T::updateFS();
}

template<class T>
void Entry::entriesFactory(vector<T>& entries, vector<string> rawData, bool fsSync) {
  entries.push_back(T(rawData));
  if(fsSync) T::updateFS();
}

template<class T>
vector<vector<string>> Entry::updateEntries(string const& query, vector<string> fields, vector<T>& entries) {
  vector<vector<string>> result;
  vector<T> matchingEntries = getMatchingEntries(query, entries);

  for(int i=0; i<matchingEntries.size(); i++) {
    matchingEntries[i].setFields(fields);
    result.push_back(matchingEntries[i].serializeLn());
  }


  T::updateFS();
  return result;
}

#endif

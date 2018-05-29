#include <string>
#include <vector>
#include <iostream>

#include "ExpressionBuilder.h"
#include "Utils.h"

using namespace std;

string ExpressionBuilder::specialSymbols = "!=><~&|";

template <typename T> int polymorphicOperators(string opp, T const lOperand, T const rOperand) {
  if(opp == "==") return lOperand == rOperand;
  if(opp == "!=") return lOperand != rOperand;
  if(opp == "<=") return lOperand <= rOperand;
  if(opp == ">=") return lOperand >= rOperand;
  if(opp == "<" ) return lOperand  < rOperand;
  if(opp == ">" ) return lOperand  > rOperand;

  cout << "Warning: Syntax error near: " << opp << '.' << endl;

  return -1;
}

int ExpressionBuilder::executor(string opp, string lOperand, string rOperand) {
  int lSize = lOperand.size();
  int rSize = rOperand.size();

  if(opp == "&&") return lSize && rSize;
  if(opp == "||") return lSize || rSize;
  if(opp == "~" ) return Utils::contains(lOperand, rOperand);

  return polymorphicOperators(opp, lOperand, rOperand);
}

int ExpressionBuilder::executor(string opp, int lOperand, int rOperand) {
  if(opp == "&&") return lOperand && rOperand;
  if(opp == "||") return lOperand || rOperand;

  return polymorphicOperators(opp, lOperand, rOperand);
}


int ExpressionBuilder::getOperatorPriority(string x) {
  if(x == "==") return 1;
  if(x == "!=") return 1;
  if(x == "<" ) return 1;
  if(x == ">" ) return 1;
  if(x == "<=") return 1;
  if(x == ">=") return 1;
  if(x == "~" ) return 1;
  if(x == "&&") return 2;
  if(x == "||") return 3;

  cout << "Warning: Syntax error near " << x << '.' << endl;
  return -1;
}


int ExpressionBuilder::typeResolver(string opp, string lOperand, string rOperand) {
  int lInt = Utils::strToInt(lOperand);
  int rInt = Utils::strToInt(rOperand);

  bool isLeftInt = lInt != -1;
  bool isRightInt = rInt != -1;

  if(isLeftInt && isRightInt) return executor(opp, lInt, rInt);
  return executor(opp, lOperand, rOperand);
}

int ExpressionBuilder::interpolationResolver(string opp, string _lOperand, string _rOperand) {
  string lOperand = _lOperand;
  string rOperand = _rOperand;
  int lInt = Utils::strToInt(_lOperand.substr(1, _lOperand.length()-1));
  int rInt = Utils::strToInt(_rOperand.substr(1, _rOperand.length()-1));

  bool lIntInRange = lInt >= 0 && lInt < substitutions.size();
  bool rIntInRange = rInt >= 0 && rInt < substitutions.size();


  if(_lOperand[0] == '$' && lIntInRange) lOperand = substitutions[lInt];
  if(_rOperand[0] == '$' && rIntInRange) rOperand = substitutions[rInt];

  return typeResolver(opp, lOperand, rOperand);
}

int ExpressionBuilder::priorityResolver(string query) {
  int queryEnd = query.length();
  bool hasSpecialSymbols = false;
  int urgentOperatorPriority = 100;
  vector<int> urgentOperatorPos {-1, -1};
  vector<vector<int>> allCmdsPos;

  string currOperator;
  int currOperatorStartPos = 0;

  for(int i=0; i<queryEnd; i++) {
    if(Utils::contains(specialSymbols, query[i])) {
      currOperator += query[i];
      hasSpecialSymbols = true;
    } else {
      if(currOperator.length()) {
        int priority = getOperatorPriority(currOperator);

        if(priority == -1) return false;

        if(priority < urgentOperatorPriority) {
          urgentOperatorPriority = priority;
          urgentOperatorPos[0] = currOperatorStartPos;
          urgentOperatorPos[1] = i-1;
        }
        vector<int> tmp = {currOperatorStartPos, i-1};
        allCmdsPos.push_back(tmp);
      }
      currOperator.clear();
      currOperatorStartPos = i+1;
    }
  }


  if(hasSpecialSymbols) {
    int prevOperatorEnd = -1;
    int nextOperatorStart = queryEnd;

    for(int i=0; i<allCmdsPos.size(); i++) {
      int currOperatorStart = allCmdsPos[i][0];
      int currOperatorEnd = allCmdsPos[i][1];

      int urgentOperatorStart = urgentOperatorPos[0];
      int urgentOperatorEnd = urgentOperatorPos[1];

      if(
        currOperatorStart == urgentOperatorStart &&
        currOperatorEnd == urgentOperatorEnd
      ) continue; // Skip the most urgent operator

      // Defining the rightmost operator before the most urgent one
      if(currOperatorEnd > prevOperatorEnd && currOperatorEnd < urgentOperatorStart)
        prevOperatorEnd = currOperatorEnd;

      // Defining the leftmost operator after the most urgent one
      if(currOperatorStart < nextOperatorStart && currOperatorStart > urgentOperatorEnd)
        nextOperatorStart = currOperatorStart;
    }

    string lOperand = Utils::slice(query, prevOperatorEnd+1, urgentOperatorPos[0]);
    string opp = Utils::slice(query, urgentOperatorPos[0], urgentOperatorPos[1]+1);
    string rOperand = Utils::slice(query, urgentOperatorPos[1]+1, nextOperatorStart);

    string cmdBefore = Utils::slice(query, 0, prevOperatorEnd+1);
    string cmdAfter = Utils::slice(query, nextOperatorStart, queryEnd);

    return priorityResolver(cmdBefore + to_string(interpolationResolver(opp, lOperand, rOperand)) + cmdAfter);
  } else {
    int queryInt = Utils::strToInt(query);
    if(queryInt < 1) return 0;
    else return queryInt;
  }
}

int ExpressionBuilder::parenthesisResolver(string query) {
  int queryEnd = query.length();
  vector<int> openParenthesis;
  int currentLvl = -1;

  int deepestLvl = currentLvl;
  int deepestCmdPos[2];

  if(Utils::contains(query, "(")) {
    // There is at least one pair of brackets
    for(int i=0; i<query.length(); i++) {
      if(query[i] == '(') {
        currentLvl++;
        openParenthesis.push_back(i);
      }
      if(query[i] == ')') {
        if(currentLvl > deepestLvl) {
          deepestCmdPos[0] = openParenthesis.back();
          openParenthesis.pop_back();
          deepestCmdPos[1] = i;
          deepestLvl = currentLvl;
        }
        currentLvl--;
      }
    }

    string cmdBefore = Utils::slice(query, 0, deepestCmdPos[0]);
    string cmd = Utils::slice(query, deepestCmdPos[0]+1, deepestCmdPos[1]);
    string cmdAfter = Utils::slice(query, deepestCmdPos[1]+1, queryEnd);

    return parenthesisResolver(cmdBefore + to_string(priorityResolver(cmd)) + cmdAfter);
  }
  else
    // Linear query here
    return priorityResolver(query);
}

bool ExpressionBuilder::parse(string str) {
  // Remove all whitespaces
  string query;
  for(int i=0; i<str.length(); i++)
    if(str[i] != ' ') query.push_back(str[i]);

  // -1 - An error occured
  //  0 - False
  //  1 - True
  return parenthesisResolver(query) > 0;
}

ExpressionBuilder::ExpressionBuilder(vector<string> _substitutions) {
  substitutions = _substitutions;
}
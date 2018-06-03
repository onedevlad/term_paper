#ifndef EXPRESSIONBUILDER_H
#define EXPRESSIONBUILDER_H

#include <string>
#include "Vector.hpp"

using namespace std;

class ExpressionBuilder {
  private:
    static string specialSymbols;
    vector<string> substitutions;
    int getOperatorPriority(string);

    int executor(string, string, string);
    int executor(string, int, int);

    int typeResolver(string, string, string);
    int interpolationResolver(string, string, string);
    int priorityResolver(string);
    int parenthesisResolver(string);
  public:
    bool parse(string);
    ExpressionBuilder(vector<string>);
};

#endif
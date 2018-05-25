#include <vector>
#include <string>

#ifndef EXPRESSIONBUILDER_H
#define EXPRESSIONBUILDER_H

class ExpressionBuilder {
  private:
    static std::string specialSymbols;
    std::vector<std::string> substitutions;
    int getOperatorPriority(std::string);

    int executor(std::string, std::string, std::string);
    int executor(std::string, int, int);

    int typeResolver(std::string, std::string, std::string);
    int interpolationResolver(std::string, std::string, std::string);
    int priorityResolver(std::string);
    int parenthesisResolver(std::string);
  public:
    bool parse(std::string);
    ExpressionBuilder(std::vector<std::string>);
};

#endif
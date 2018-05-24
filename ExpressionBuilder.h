#include <vector>
#include <string>

#ifndef EXPRESSIONBUILDER_H
#define EXPRESSIONBUILDER_H

class ExpressionBuilder {
  private:
    static std::string specialSymbols;
    std::vector<std::string> substitutions;
    int getOperatorPriority(std::string);

    bool executor(std::string, std::string, std::string);
    bool executor(std::string, int, int);

    bool typeResolver(std::string, std::string, std::string);
    bool priorityResolver(std::string);
    bool parenthesisResolver(std::string);
  public:
    bool interpolationResolver(std::string, std::string, std::string);
    bool parse(std::string);
    ExpressionBuilder(std::vector<std::string>);
};

#endif
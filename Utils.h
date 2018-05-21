#include <string>
#include <vector>

#ifndef UTILS_H
#define UTILS_H

class Utils {
  public:
    static std::string enterPrompt;
    static std::string trim(const std::string&);
    static bool isNumber(const std::string&);
    static int strToInt(std::string);
    static int askForInt(std::string, int, int);
    static std::string askForStr(std::string);
    static void setHeaders(std::vector<std::string>*, std::vector<std::string>*);
    static void help();
};

#endif
#ifndef UTILS_H
#define UTILS_H

class Utils {
  public:
    static std::string enterPrompt;
    static std::string trim(const std::string&);
    static bool isNumber(const std::string&);
    static bool contains(std::string, std::string);
    static int strToInt(std::string);
    static int askForInt(std::string, int, int);
    static std::string askForStr(std::string);
};

#endif
#ifndef UTILS_H
#define UTILS_H

class Utils {
  public:
    static std::string enterPrompt;
    static std::string trim(const std::string&);
    static std::string replaceChar(std::string, char, char);
    static std::string slice(std::string, int, int);
    static bool isNumber(const std::string&);
    static bool contains(std::string, std::string);
    static bool contains(std::string, char);
    static int strToInt(std::string);
    static int askForInt(std::string, int, int);
    static std::string askForStr(std::string);
};

#endif
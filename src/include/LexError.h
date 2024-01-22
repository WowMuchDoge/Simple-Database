#pragma once

#include <string>

class LexError {
    private:
        std::string str;

#ifdef _WIN32
    std::string msg, s1, l1, l2, l3, s2;
#endif
    public:
        LexError(std::string message, int lineNumber, int sIndex, int eIndex, std::string line);
        std::string getMessage();
};
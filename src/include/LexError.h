#pragma once

#include <string>

class LexError {
    private:
        int line;
        std::string str;
        int chr;
    public:
        LexError(std::string message, int lineNumber, int sIndex, int eIndex, std::string line);
        std::string getMessage();
};
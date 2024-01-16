#pragma once

#include <vector>

#include "Token.h"

class ParseError {
    private:
        std::string str;
    public:
        ParseError(Token token, std::string message, std::vector<std::string> lines, int startIndex, int endIndex);
        std::string getMessage();
        int sIndex;
        int eIndex;
};
#pragma once

#include <vector>

#include "Token.h"

class ParseError {
    private:
        std::string str;
    public:
        ParseError(Token token, std::string message, std::string line);
        std::string getMessage();
};
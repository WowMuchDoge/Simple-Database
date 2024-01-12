#pragma once

#include <string>

#include "TokenType.h"

class Token {
    public:
        TokenType type;
        std::string value;

        Token(std::string str, TokenType typ) : value(str), type(typ) {}
};
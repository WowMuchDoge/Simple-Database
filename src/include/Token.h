#pragma once

#include <string>

#include "TokenType.h"

class Token {
    public:
        TokenType type;
        std::string value;
        int line;
        int offset;

        Token(std::string str, TokenType typ, int ln, int offst) : value(str), type(typ), line(ln), offset(offst) {}
};
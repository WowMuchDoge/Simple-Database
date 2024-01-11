#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "TokenType.h"
#include "Token.h"

class Scanner {
    private:
        std::string source;
        int current;
        int start;

        std::vector<Token> tokens;

    public:
        Scanner(std::string src) : source(src) {}

        std::vector<Token> scanTokens();
};
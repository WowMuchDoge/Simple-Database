#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "TokenType.h"
#include "Token.h"

class Scanner {
    private:
        std::string source;
        int current;
        int start;

        std::vector<Token> tokens;

        std::unordered_map<std::string, TokenType> keywords;

        char advance();
        char peek();
        char previous();
        bool isAtEnd();

        void addToken(TokenType type);
        void addToken(std::string val);

        bool isAlpha();
        bool isDigit();

        void number();
        void identifier();

    public:
        Scanner(std::string src) : source(src), current(0), start(0) {
            keywords["INT"] = INT;
            keywords["BOOL"] = BOOL;
            keywords["DOUBLE"] = DOUBLE;
            keywords["CHAR"] = CHAR;
            keywords["STRING"] = STRING;
            keywords["ADD_COLUMN"] = ADD_COLUMN;
            keywords["ADD_ROW"] = ADD_ROW;
        }

        std::vector<Token> scanTokens();
};
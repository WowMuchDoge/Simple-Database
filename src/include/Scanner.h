#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include "TokenType.h"
#include "Token.h"

class Scanner {
    private:
        std::string source;
        int current;
        int start;

        std::vector<Token> tokens;

        std::map<std::string, TokenType> keywords;

        bool isAtEnd();


        bool isAlpha(char c);
        bool isDigit(char c);

        std::vector<std::string> lines;
    public:
        Scanner(std::string srce) : source(srce), current(0), start(0) {
            keywords["INT"] = INT;
            keywords["BOOL"] = BOOL;
            keywords["DOUBLE"] = DOUBLE;
            keywords["STRING"] = STRING;
            keywords["ADD_COLUMN"] = ADD_COLUMN;
            keywords["ADD_ROW"] = ADD_ROW;
            keywords["TRUE"] = TRUE;
            keywords["FALSE"] = FALSE;
            keywords["GET_ELEMENT"] = GET_ELEMENT;
            keywords["REMOVE_COLUMN"] = REMOVE_COLUMN;
            keywords["REMOVE_ROW"] = REMOVE_ROW;
            keywords["EDIT_ROW"] = EDIT_ROW;
            keywords["EDIT_ELEMENT"] = EDIT_ELEMENT;
        }

        std::vector<Token> scanTokens(int line);

        void setText(std::string txt);
};
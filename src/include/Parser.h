#pragma once

#include <iostream>
#include <vector>

#include "Token.h"
#include "TableHead.h"

class Parser {
    private:
        TableHead* head;
        std::vector<Token> tokens;
        int start;
        int current;

        Token advance();
        Token peek();
        Token previous();

        bool isAtEnd();

        void addColumn();
        void getElement();
        void addRow();
        void editRow();
        void editElement();
        void editColName();

        void removeColumn();
        void removeRow();
    public:
        Parser(std::vector<Token> tkns, TableHead *h) : tokens(tkns), current(0), head(h) {}
        
        void parse();
        void setInput(std::vector<Token> tkns);
};
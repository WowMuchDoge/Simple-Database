#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "Token.h"
#include "TableHead.h"
#include "ColumnHead.h"
#include "BaseColumn.h"
#include "Token.h"
#include "TokenType.h"
#include "ParseError.h"

class ErrorScan {
    public:
        ErrorScan(std::vector<Token> tkns, TableHead* hd, std::string ln);
        void checkTokens();
    private:
        std::vector<Token> tokens;
        TableHead* head;
        int current = 0;

        Token advance();
        Token peek();
        Token previous();
        
        bool isAtEnd();

        void addRow();
        void addColumn();
        void getElement();

        void editRow();
        void editElement();
        void removeColumn();
        void removeRow();
        void editColName();

        void consume(TokenType type, std::string msg);

        std::string line;
};
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

class ErrorScan {
    public:
        ErrorScan(std::vector<Token> tkns, TableHead* hd);
        void checkTokens();
    private:
        std::vector<Token> tokens;
        TableHead* head;
        int current = 0;
};
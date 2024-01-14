#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "BaseColumn.h"
#include "ColumnHead.h"
#include "TokenType.h"

class TableHead {
    private:
        int rowCount;

    public:
        TableHead() :  rowCount(0) {
            columns.push_back(new ColumnHead<int>("id"));
        }

        void addColumn(TokenType type, std::string name);
        void addRow();
        void clearRows();

        BaseColumn* getColumn(int col);
        std::string getColumnType(int col);

        ColumnHead<int>* getIntColumn(int col);
        ColumnHead<std::string>* getStringColumn(int col);
        ColumnHead<double>* getDoubleColumn(int col);
        ColumnHead<char>* getCharColumn(int col);
        ColumnHead<bool>* getBoolColumn(int col);

        std::vector<BaseColumn*> columns;
};
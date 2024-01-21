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
        TableHead() :  rowCount(0) {}

        void addColumn(TokenType type, std::string name);
        void addRow();
        void clearRows();

        BaseColumn* getColumn(int col);
        BaseColumn* getColumn(std::string colName);
        std::string getColumnType(int col);

        ColumnHead<int>* getIntColumn(int col);
        ColumnHead<std::string>* getStringColumn(int col);
        ColumnHead<double>* getDoubleColumn(int col);
        ColumnHead<char>* getCharColumn(int col);
        ColumnHead<bool>* getBoolColumn(int col);

        void writeToFile(std::string fileName);
        std::vector<BaseColumn*> columns;
};
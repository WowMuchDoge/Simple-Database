#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>

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

        void writeToFile(std::string fileName);
        std::vector<std::unique_ptr<BaseColumn>> columns;
};
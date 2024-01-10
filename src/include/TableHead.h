#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "BaseColumn.h"
#include "ColumnHead.h"

class TableHead {
    private:
        ColumnHead<int> head;

        std::vector<BaseColumn*> columns;
        int rowCount;

    public:
        TableHead() : head(ColumnHead<int>("id")), rowCount(0) {}

        void addColumn(std::string type, std::string name);
        void addRow();
        void clearRows();

        BaseColumn* getColumn(int col);
        std::string getColumnType(int col);

        ColumnHead<int>* getIntColumn(int col);
        ColumnHead<const char*>* getStringColumn(int col);
        ColumnHead<double>* getDoubleColumn(int col);
        ColumnHead<char>* getCharColumn(int col);
        ColumnHead<bool>* getBoolColumn(int col);
};
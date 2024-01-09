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

    public:
        TableHead() : head(ColumnHead<int>("id")) {}

        void addColumn(std::string type, std::string name);
        void addRow();
        void* getElement(int col, int row);

        BaseColumn* getColumn(int col);
        std::string getColumnType(int col);
};
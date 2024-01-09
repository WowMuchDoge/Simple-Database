#include <iostream>
#include <string>

#include "../include/TableHead.h"

void TableHead::addColumn(std::string type, std::string name) {
    if (type == "INT") {
        columns.push_back(new ColumnHead<int>(name));
    } else if (type == "STRING") {
        columns.push_back(new ColumnHead<std::string>(name));
    } else if (type == "DOUBLE") {
        columns.push_back(new ColumnHead<double>(name));
    } else if (type == "CHAR") {
        columns.push_back(new ColumnHead<char>(name));
    } else if (type == "BOOL") {
        columns.push_back(new ColumnHead<bool>(name));
    } else {
        exit(1);
    }
}

void TableHead::addRow() {
    for (BaseColumn* col : columns) {
        col->addEmptyElement();
    }
}
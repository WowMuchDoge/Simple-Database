#include <iostream>
#include <string>

#include "../include/TableHead.h"
#include "../include/BaseColumn.h"

void TableHead::addColumn(std::string type, std::string name) {
    if (type == "INT") {
        columns.push_back(new ColumnHead<int>(name));
    } else if (type == "STRING") {
        columns.push_back(new ColumnHead<char*>(name));
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

BaseColumn* TableHead::getColumn(int col) {
    return columns[col];
}

void TableHead::addRow() {
    for (BaseColumn* col : columns) {
        col->addEmptyElement();
    }
    head.addElement(rowCount++);
}

void TableHead::clearRows() {
    for (BaseColumn* col : columns) {
        col->clearColumn();
    }
}

ColumnHead<int>* TableHead::getIntColumn(int col) {
    if (columns[col]->getTypeName() == "int") {
        return (ColumnHead<int>*)(columns[col]);
    } else {
        exit(1);
    }
}
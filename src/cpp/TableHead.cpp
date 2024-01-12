#include <iostream>
#include <string>

#include "../include/TableHead.h"
#include "../include/BaseColumn.h"
#include "../include/TokenType.h"

void TableHead::addColumn(TokenType type, std::string name) {
    if (type == INT) {
        columns.push_back(new ColumnHead<int>(name));
    } else if (type == STRING) {
        columns.push_back(new ColumnHead<char*>(name));
    } else if (type == DOUBLE) {
        columns.push_back(new ColumnHead<double>(name));
    } else if (type == CHAR) {
        columns.push_back(new ColumnHead<char>(name));
    } else if (type == BOOL) {
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

ColumnHead<const char*>* TableHead::getStringColumn(int col) {
    if (columns[col]->getTypeName() == "int") {
        return (ColumnHead<const char*>*)(columns[col]);
    } else {
        exit(1);
    }
}

ColumnHead<double>* TableHead::getDoubleColumn(int col) {
    if (columns[col]->getTypeName() == "int") {
        return (ColumnHead<double>*)(columns[col]);
    } else {
        exit(1);
    }
}

ColumnHead<char>* TableHead::getCharColumn(int col) {
    if (columns[col]->getTypeName() == "int") {
        return (ColumnHead<char>*)(columns[col]);
    } else {
        exit(1);
    }
}

ColumnHead<bool>* TableHead::getBoolColumn(int col) {
    if (columns[col]->getTypeName() == "int") {
        return (ColumnHead<bool>*)(columns[col]);
    } else {
        exit(1);
    }
}
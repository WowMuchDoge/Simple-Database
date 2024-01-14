#include <iostream>
#include <string>

#include "../include/TableHead.h"
#include "../include/BaseColumn.h"
#include "../include/TokenType.h"

void TableHead::addColumn(TokenType type, std::string name) {
    switch (type) {
        case INT: columns.push_back(new ColumnHead<int>(name)); break;
        case STRING: columns.push_back(new ColumnHead<std::string>(name)); break;
        case DOUBLE: columns.push_back(new ColumnHead<double>(name)); break;
        case BOOL: columns.push_back(new ColumnHead<bool>(name)); break;
        default:
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
    ((ColumnHead<int>*)(columns[0]))->addElement(rowCount++);
}

void TableHead::clearRows() {
    for (BaseColumn* col : columns) {
        col->clearColumn();
    }
}

ColumnHead<int>* TableHead::getIntColumn(int col) {
    if (columns[col]->getTypeName() == "i") {
        return (ColumnHead<int>*)(columns[col]);
    } else {
        exit(1);
    }
}

ColumnHead<std::string>* TableHead::getStringColumn(int col) {
    if (columns[col]->getTypeName() == "NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE") {
        return (ColumnHead<std::string>*)(columns[col]);
    } else {
        exit(1);
    }
}

ColumnHead<double>* TableHead::getDoubleColumn(int col) {
    if (columns[col]->getTypeName() == "d") {
        return (ColumnHead<double>*)(columns[col]);
    } else {
        exit(1);
    }
}

ColumnHead<bool>* TableHead::getBoolColumn(int col) {
    if (columns[col]->getTypeName() == "b") {
        return (ColumnHead<bool>*)(columns[col]);
    } else {
        exit(1);
    }
}

BaseColumn* TableHead::getColumn(std::string colName) {
    for (BaseColumn* column : columns) {
        if (column->getName() == colName) {
            return column;
        }
    }
    exit(1);
}
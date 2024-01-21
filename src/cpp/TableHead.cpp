#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "../include/Constants.h"
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
            exit(UNKOWN_TYPE);
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
        return NULL;
    }
}

ColumnHead<std::string>* TableHead::getStringColumn(int col) {
    if (columns[col]->getTypeName() == "NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE") {
        return (ColumnHead<std::string>*)(columns[col]);
    } else {
        return NULL;
    }
}

ColumnHead<double>* TableHead::getDoubleColumn(int col) {
    if (columns[col]->getTypeName() == "d") {
        return (ColumnHead<double>*)(columns[col]);
    } else {
        return NULL;
    }
}

ColumnHead<bool>* TableHead::getBoolColumn(int col) {
    if (columns[col]->getTypeName() == "b") {
        return (ColumnHead<bool>*)(columns[col]);
    } else {
        return NULL;
    }
}

BaseColumn* TableHead::getColumn(std::string colName) {
    for (BaseColumn* column : columns) {
        if (column->getName() == colName) {
            return column;
        }
    }
    return NULL;
}

void TableHead::writeToFile(std::string fileName) {
    std::ofstream file(fileName);
    if (columns.size() > 0) {
        for (BaseColumn* column : columns) {
                if (column->getTypeName() == "i") {
                    file << "ADD_COLUMN(INT " << column->getName() << ")";
                } else if (column->getTypeName() == "NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE") {
                    file << "ADD_COLUMN(STRING " << column->getName() << ")";
                } else if (column->getTypeName() == "d") {
                    file << "ADD_COLUMN(DOUBLE " << column->getName() << ")";
                } else if (column->getTypeName() == "b") {
                    file << "ADD_COLUMN(BOOL " << column->getName() << ")";
                } else {
                    file.close();
                    exit(UNKOWN_TYPE);
                }
            file << " ";
        }
        file << '\n';
        int j = 0;
        for (int i = 0; i < columns[0]->rowLen(); i++) {
            file << "ADD_ROW(";
            j = 0;
            for (BaseColumn* column : columns) {
                if (column->getTypeName() == "i") {
                    file << ((ColumnHead<int>*)column)->getElement(i) << (j == columns.size() - 1 ? "" : " ");
                } else if (column->getTypeName() == "NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE") {
                    file << ((ColumnHead<std::string>*)column)->getElement(i) << (j == columns.size() - 1 ? "" : " ");
                } else if (column->getTypeName() == "d") {
                    file << ((ColumnHead<double>*)column)->getElement(i) << (j == columns.size() - 1 ? "" : " ");
                } else if (column->getTypeName() == "b") {
                    if (((ColumnHead<bool>*)column)->getElement(i) == true) {
                        file << "TRUE" << (j == columns.size() - 1 ? "" : " ");
                    } else if (((ColumnHead<bool>*)column)->getElement(i) == false) {
                        file << "FALSE" << (j == columns.size() - 1 ? "" : " ");
                    }
                } else {
                    file.close();
                    exit(UNKOWN_TYPE);
                }
                j++;
            }
            file << ")\n";
        }
    }
    file.close();
}
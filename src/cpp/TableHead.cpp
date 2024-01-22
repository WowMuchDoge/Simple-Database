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
        case INT: columns.push_back(std::make_unique<ColumnHead<int>>(name)); break;
        case STRING: columns.push_back(std::make_unique<ColumnHead<std::string>>(name)); break;
        case DOUBLE: columns.push_back(std::make_unique<ColumnHead<double>>(name)); break;
        case BOOL: columns.push_back(std::make_unique<ColumnHead<bool>>(name)); break;
        default:
            exit(UNKOWN_TYPE);
    }
}

BaseColumn* TableHead::getColumn(int col) {
    return columns[col].get();
}

BaseColumn* TableHead::getColumn(std::string colName) {
    for (int i = 0; i < columns.size(); i++) {
        if (columns[i]->getName() == colName) {
            return columns[i].get();
        }
    }
    return NULL;
}

void TableHead::addRow() {
    for (int i = 0; i < columns.size(); i++) {
        columns[i]->addEmptyElement();
    }
    ((ColumnHead<int>*)(columns[0].get()))->addElement(rowCount++);
}

void TableHead::clearRows() {
    for (int i = 0; i < columns.size(); i++) {
        columns[i]->clearColumn();
    }
}

void TableHead::writeToFile(std::string fileName) {
    std::ofstream file(fileName);
    if (columns.size() > 0) {
        for (int i = 0; i < columns.size(); i++) {
                if (columns[i]->getTypeName() == "i") {
                    file << "ADD_COLUMN(INT " << columns[i]->getName() << ")";
                } else if (columns[i]->getTypeName() == "NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE") {
                    file << "ADD_COLUMN(STRING " << columns[i]->getName() << ")";
                } else if (columns[i]->getTypeName() == "d") {
                    file << "ADD_COLUMN(DOUBLE " << columns[i]->getName() << ")";
                } else if (columns[i]->getTypeName() == "b") {
                    file << "ADD_COLUMN(BOOL " << columns[i]->getName() << ")";
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
            for (int j = 0; j < columns.size(); j++) {
                if (columns[j]->getTypeName() == "i") {
                    file << ((ColumnHead<int>*)columns[j].get())->getElement(i) << (j == columns.size() - 1 ? "" : " ");
                } else if (columns[j]->getTypeName() == "NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE") {
                    file << ((ColumnHead<std::string>*)columns[j].get())->getElement(i) << (j == columns.size() - 1 ? "" : " ");
                } else if (columns[j]->getTypeName() == "d") {
                    file << ((ColumnHead<double>*)columns[j].get())->getElement(i) << (j == columns.size() - 1 ? "" : " ");
                } else if (columns[j]->getTypeName() == "b") {
                    if (((ColumnHead<bool>*)columns[j].get())->getElement(i) == true) {
                        file << "TRUE" << (j == columns.size() - 1 ? "" : " ");
                    } else if (((ColumnHead<bool>*)columns[j].get())->getElement(i) == false) {
                        file << "FALSE" << (j == columns.size() - 1 ? "" : " ");
                    }
                } else {
                    file.close();
                    exit(UNKOWN_TYPE);
                }
            }
            file << ")\n";
        }
    }
    file.close();
}
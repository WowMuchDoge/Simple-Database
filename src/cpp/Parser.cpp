#include <iostream>
#include <string>

#include "../include/Parser.h"

Token Parser::peek() {
    return tokens[current];
}

bool Parser::isAtEnd() {
    return peek().type == END_OF_TEXT;
}

Token Parser::previous() {
    return tokens[current - 1];
}

Token Parser::advance() {
    if (!isAtEnd()) current++;
    return previous();
}

void Parser::addColumn() {
    advance(); // Add error handling to ensure that this consumes a parenthesis
    TokenType t1 = advance().type;
    std::string v2 = advance().value;
    head->addColumn(t1, v2);
    advance();
}

void Parser::addRow() {
    advance(); // Add error handling to ensure that this consumes a parenthesis
    Token tkn = peek();
    int i = 1;
    TokenType type;
    while ((tkn = advance()).type != RIGHT_PAREN) {
        if (head->columns[i]->getTypeName() == "i") {
            ((ColumnHead<int>*)(head->columns[i]))->addElement(std::stoi(tkn.value));
        } else if (head->columns[i]->getTypeName() == "NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE") {
            ((ColumnHead<std::string>*)(head->columns[i]))->addElement(tkn.value);
        } else if (head->columns[i]->getTypeName() == "d") {
            ((ColumnHead<double>*)(head->columns[i]))->addElement(std::stod(tkn.value));
        } else if (head->columns[i]->getTypeName() == "b") {
            if (tkn.type == TRUE) {
                ((ColumnHead<bool>*)(head->columns[i]))->addElement(true);
            } else if (tkn.type == FALSE) {
                ((ColumnHead<bool>*)(head->columns[i]))->addElement(false);
            } else {
                exit(1);
            }
        }
        i++;
    }
    ((ColumnHead<int>*)(head->columns[0]))->addElement(((ColumnHead<int>*)(head->columns[0]))->getElements().size());
}

void Parser::getElement() {
    advance(); // Add error handling to ensure that this consumes a parenthesis
    int col = std::stoi(advance().value);
    int row = std::stoi(advance().value);

    head->columns[col]->printElement(row);

    advance();
}

void Parser::removeColumn() {
    advance(); // Add error handling to ensure that this consumes a parenthesis

    int col = std::stoi(advance().value);
    head->columns.erase(head->columns.begin() + col);

    advance();
}

void Parser::removeRow() {
    advance(); // Add error handling to ensure that this consumes a parenthesis
    int row = std::stoi(advance().value);

    for (BaseColumn* column : head->columns) {
        column->removeElement(row);
    }

    int len  = ((ColumnHead<int>*)(head->columns[0]))->getElements().size();
    for (int i = 0; i < len; i++) {
        ((ColumnHead<int>*)(head->columns[0]))->editElement(i, i);
    }

    advance();
}

void Parser::editRow() {
    advance(); // Add error handling to ensure that this consumes a parenthesis
    int index = std::stoi(advance().value);
    Token tkn = peek();
    int i = 1;
    TokenType type;
    while ((tkn = advance()).type != RIGHT_PAREN) {
        if (head->columns[i]->getTypeName() == "i") {
            ((ColumnHead<int>*)(head->columns[i]))->editElement(std::stoi(tkn.value), index);
        } else if (head->columns[i]->getTypeName() == "NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE") {
            ((ColumnHead<std::string>*)(head->columns[i]))->editElement(tkn.value, index);
        } else if (head->columns[i]->getTypeName() == "d") {
            ((ColumnHead<double>*)(head->columns[i]))->editElement(std::stod(tkn.value), index);
        } else if (head->columns[i]->getTypeName() == "b") {
            if (tkn.type == TRUE) {
                ((ColumnHead<bool>*)(head->columns[i]))->editElement(true, index);
            } else if (tkn.type == FALSE) {
                ((ColumnHead<bool>*)(head->columns[i]))->editElement(false, index);
            } else {
                exit(1);
            }
        }
        i++;
    }
    ((ColumnHead<int>*)(head->columns[0]))->addElement(((ColumnHead<int>*)(head->columns[0]))->getElements().size());
}

void Parser::parse() {
    while (!isAtEnd()) {
        switch(advance().type) {
            case ADD_COLUMN: addColumn(); break;
            case ADD_ROW: addRow(); break;
            case GET_ELEMENT: getElement(); break;
            case REMOVE_COLUMN: removeColumn(); break;
            case REMOVE_ROW: removeRow(); break;
            case EDIT_ROW: editRow(); break;
            default:
                exit(1);
                break;
        }
    }
}
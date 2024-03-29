#include "../include/ErrorScan.h"

#include <string>

ErrorScan::ErrorScan(std::vector<Token> tkns, TableHead* hd, std::string ln) : tokens(tkns), head(hd), line(ln) {}

static std::string getTypeString(TokenType type) {
    if (type == INT_TYPE) return "INT";
    else if (type == LITERAL) return "STRING";
    else if (type == TRUE || true == FALSE) return "BOOL";
    else if (type == DOUBLE_TYPE) return "DOUBLE";
    else return "UNKOWN_TYPE";
}

void ErrorScan::addColumn() {
    consume(LEFT_PAREN, "Expected '(', got '" + peek().value + "' instead.");

    if ((advance().type != STRING) && (previous().type != INT) && (previous().type != DOUBLE) && (previous().type != BOOL)) {
        throw ParseError(previous(), "Expected a type, got '" + previous().value + "' instead.", line);
    }
    if ((advance().type != LITERAL)) {
        throw ParseError(previous(), "Expected a column name, got '" + previous().value + "' instead.", line);
    } else if (head->getColumn(previous().value) != NULL) {
        throw ParseError(previous(), "Column name '" + previous().value.substr(1, previous().value.size() - 2) + "' is already taken.", line);
    }

    consume(RIGHT_PAREN, "Expected ')', got '" + peek().value + "' instead.");
}

void ErrorScan::addRow() {
    consume(LEFT_PAREN, "Expected '(', got '" + peek().value + "' instead.");

    if (peek().type == RIGHT_PAREN) {
        throw ParseError(previous(), "Method ADD_ROW() cannot have empty argument list.", line);
    }

    Token tkn = previous();
    int i = 0;
    while ((tkn = advance()).type != RIGHT_PAREN) {
        if (i >= head->columns.size()) {
            throw ParseError(tkn, "Expected ')'.", line);
        }
        if (head->columns[i]->getTypeName() == "i") {
            if (tkn.type != INT_TYPE) {
                throw ParseError(tkn, "Expected type 'INT', got '" + getTypeString(tkn.type) + "' instead.", line);
            }
        } else if (head->columns[i]->getTypeName() == "d") {
            if (tkn.type != DOUBLE_TYPE) {
                throw ParseError(tkn, "Expected type 'DOUBLE', got '" +getTypeString(tkn.type) + "' instead.", line);
            }
        } else if (head->columns[i]->getTypeName() == "NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE") {
            if (tkn.type != LITERAL) {
                throw ParseError(tkn, "Expected type 'STRING', got '" + getTypeString(tkn.type) + "' instead.", line);
            }        
        } else if (head->columns[i]->getTypeName() == "b") {
            if (tkn.type != TRUE && tkn.type != FALSE) {
                throw ParseError(tkn, "Expected type 'DOUBLE', got '" + getTypeString(tkn.type) + "' instead.", line);
            }        
        }
        i++;
    }
    if (i != head->columns.size()) {
        throw ParseError(tkn, "Too few arguments in row call.", line);
    }
}

void ErrorScan::getElement() {
    consume(LEFT_PAREN, "Expected '(', got '" + peek().value + "' instead.");
    if (advance().type != LITERAL) {
        throw ParseError(previous(), "Expected a name, got '" + getTypeString(previous().type) + "' instead.", line);
    } else {
        if (head->getColumn(previous().value) == NULL) {
            throw ParseError(previous(), "Column '" + previous().value + "' not in table.", line);
        }
    }
    if (advance().type != INT_TYPE) {
        throw ParseError(previous(), "Expected an index, got '" + getTypeString(previous().type) + "' instead.", line);
    } else {
        if (std::stoi(previous().value) >= head->columns[0]->rowLen()) {
            throw ParseError(previous(), "Index '" + previous().value + "' out of range.", line);
        }
    }
    consume(RIGHT_PAREN, "Expected ')', got '" + previous().value + "' instead.");
}

void ErrorScan::editRow() {
    consume(LEFT_PAREN, "Expected '(', got '" + peek().value + "' instead.");

    if (advance().type != INT_TYPE) {
        throw ParseError(previous(), "Expected index, got '" + previous().value + "' instead.", line);
    }
    if (std::stoi(previous().value) >= head->columns[0]->rowLen()) {
        throw ParseError(previous(), "Index '" + previous().value + "' out of range.", line);
    }

    Token tkn = previous();
    int i = 0;
    while ((tkn = advance()).type != RIGHT_PAREN) {
        if (i >= head->columns.size()) {
            throw ParseError(tkn, "Expected ')'.", line);
        }
        if (head->columns[i]->getTypeName() == "i") {
            if (tkn.type != INT_TYPE) {
                throw ParseError(tkn, "Expected type 'INT', got '" + getTypeString(tkn.type) + "' instead.", line);
            }
        } else if (head->columns[i]->getTypeName() == "d") {
            if (tkn.type != DOUBLE_TYPE) {
                throw ParseError(tkn, "Expected type 'DOUBLE', got '" + getTypeString(tkn.type) + "' instead.", line);
            }
        } else if (head->columns[i]->getTypeName() == "NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE") {
            if (tkn.type != LITERAL) {
                throw ParseError(tkn, "Expected type 'STRING', got '" + getTypeString(tkn.type) + "' instead.", line);
            }        
        } else if (head->columns[i]->getTypeName() == "b") {
            if (tkn.type != BOOL) {
                throw ParseError(tkn, "Expected type 'DOUBLE', got '" + getTypeString(tkn.type) + "' instead.", line);
            }        
        }
        i++;
    }
    if (i != head->columns.size()) {
        throw ParseError(tkn, "Too few arguments in row call.", line);
    }
}

void ErrorScan::removeColumn() {
    consume(LEFT_PAREN, "Expected '(', got '" + peek().value + "' instead.");

    if (advance().type != LITERAL) {
        throw ParseError(previous(), "Expected a name, got '" + previous().value + "' instead.", line);
    } else if (head->getColumn(previous().value) == NULL) {
        throw ParseError(previous(), "Column '" + previous().value + "' not in table.", line);
    }

    consume(RIGHT_PAREN, "Expected ')', got '" + peek().value + "' instead.");
}

void ErrorScan::removeRow() {
    consume(LEFT_PAREN, "Expected '(', got '" + peek().value + "' instead.");

    if (advance().type != INT_TYPE) {
        throw ParseError(previous(), "Expected index, got '" + previous().value + "' instead.", line);
    }
    if (std::stoi(previous().value) >= head->columns[0]->rowLen()) {
        throw ParseError(previous(), "Index '" + previous().value + "' out of range.", line);
    }

    consume(RIGHT_PAREN, "Expected ')', got '" + peek().value + "' instead.");
}

void ErrorScan::editElement() {
    consume(LEFT_PAREN, "Expected '(', got '" + peek().value + "' instead.");

    std::string col;
    int row;

    BaseColumn* bCol;

    if (advance().type != LITERAL) {
        throw ParseError(previous(), "Expected a name, got '" + previous().value + "' instead.", line);
    } else if (head->getColumn(previous().value) == NULL) {
        throw ParseError(previous(), "Column '" + previous().value + "' not in table.", line);
    } else {
        bCol = head->getColumn(previous().value);
    }

    if (advance().type != INT_TYPE) {
        throw ParseError(previous(), "Expected index, got '" + previous().value + "' instead.", line);
    } else if (std::stoi(previous().value) >= head->columns[0]->rowLen()) {
        throw ParseError(previous(), "Row index '" + previous().value + "' out of range.", line);
    } else {
        row = std::stoi(previous().value);
    }

    if (bCol->getTypeName() == "i") {
        if (advance().type != INT_TYPE) {
            throw ParseError(previous(), "Expected type 'INT', got '" + getTypeString(previous().type) + "' instead.", line);
        }
    } else if (bCol->getTypeName() == "d") {
        if (advance().type != DOUBLE_TYPE) {
            throw ParseError(previous(), "Expected type 'DOUBLE', got '" + getTypeString(previous().type) + "' instead.", line);
        }
    } else if (bCol->getTypeName() == "NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE") {
        if (advance().type != LITERAL) {
            throw ParseError(previous(), "Expected type 'STRING', got '" + getTypeString(previous().type) + "' instead.", line);
        }        
    } else if (bCol->getTypeName() == "b") {
        if (advance().type != BOOL) {
            throw ParseError(previous(), "Expected type 'DOUBLE', got '" + getTypeString(previous().type) + "' instead.", line);
        }        
    }
    consume(RIGHT_PAREN, "Expected ')', got '" + peek().value + "' instead.");    
}

void ErrorScan::editColName() {
    consume(LEFT_PAREN, "Expected '(', got '" + peek().value + "' instead.");

    if (advance().type != LITERAL) {
        throw ParseError(previous(), "Expected a name, got '" + previous().value + "' instead.", line);
    } else if (head->getColumn(previous().value) == NULL) {
        throw ParseError(previous(), "Column '" + previous().value + "' not in table.", line);
    }

    if (advance().type != LITERAL) {
        throw ParseError(previous(), "Expected a name, got '" + previous().value + "' instead.", line);
    }

    consume(RIGHT_PAREN, "Expected ')', got '" + peek().value + "' instead.");    
}

void ErrorScan::checkTokens() {
    current = 0;
    while (!isAtEnd()) {
        switch(advance().type) {
            case ADD_COLUMN: addColumn(); break;
            case ADD_ROW: addRow(); break;
            case GET_ELEMENT: getElement(); break;
            case EDIT_ROW: editRow(); break;
            case REMOVE_COLUMN: removeColumn(); break;
            case REMOVE_ROW: removeRow(); break;
            case EDIT_ELEMENT: editElement(); break;
            case EDIT_COLNAME: editColName(); break;
            default:
                throw ParseError(previous(), "Expected method, got '" + previous().value + "' instead.", line);
        }
    }
}

Token ErrorScan::advance() {
    if (!isAtEnd()) current++;

    return previous();
}
Token ErrorScan::peek() {
    return tokens[current];
}
Token ErrorScan::previous() {
    return tokens[current - 1];
}
bool ErrorScan::isAtEnd() {
    return current == tokens.size() - 1;
}

void ErrorScan::consume(TokenType type, std::string msg) {
    if (advance().type == type) return;

    throw ParseError(previous(), msg, line);
}
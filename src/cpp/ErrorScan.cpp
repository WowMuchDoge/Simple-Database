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
        throw ParseError(previous(), "Expected a type, got '" + BOLD + previous().value + WHITE + "' instead.", line, current - previous().value.size(), current);
    }
    if ((advance().type != LITERAL)) {
        throw ParseError(previous(), "Expected a column name, got '" + BOLD + previous().value + WHITE + "' instead.", line, current - previous().value.size(), current);
    } else if (head->getColumn(previous().value) != NULL) {
        throw ParseError(previous(), "Column name '" + BOLD + previous().value.substr(1, previous().value.size() - 2) + WHITE + "' is already taken.", line, current - previous().value.size(), current);
    }

    consume(RIGHT_PAREN, "Expected ')', got '" + peek().value + "' instead.");
}

void ErrorScan::addRow() {
    consume(LEFT_PAREN, "Expected '(', got '" + peek().value + "' instead.");

    if (peek().type == RIGHT_PAREN) {
        throw ParseError(previous(), "Method ADD_ROW() cannot have empty argument list.", line, current - previous().value.size(), current);
    }

    Token tkn = previous();
    int i = 0;
    while ((tkn = advance()).type != RIGHT_PAREN) {
        if (i >= head->columns.size()) {
            throw ParseError(tkn, "Expected ')'.", line, current - tkn.value.size(), current);
        }
        if (head->columns[i]->getTypeName() == "i") {
            if (tkn.type != INT_TYPE) {
                throw ParseError(tkn, "Expected type 'INT', got '" + BOLD + getTypeString(tkn.type) + BOLD + "' instead.", line, current - tkn.value.size(), current);
            }
        } else if (head->columns[i]->getTypeName() == "d") {
            if (tkn.type != DOUBLE_TYPE) {
                throw ParseError(tkn, "Expected type 'DOUBLE', got '" + BOLD +getTypeString(tkn.type) + WHITE + "' instead.", line, current - tkn.value.size(), current);
            }
        } else if (head->columns[i]->getTypeName() == "NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE") {
            if (tkn.type != LITERAL) {
                throw ParseError(tkn, "Expected type 'STRING', got '" + BOLD + getTypeString(tkn.type) + WHITE + "' instead.", line, current - tkn.value.size(), current);
            }        
        } else if (head->columns[i]->getTypeName() == "b") {
            if (tkn.type != TRUE && tkn.type != FALSE) {
                throw ParseError(tkn, "Expected type 'DOUBLE', got '" + BOLD + getTypeString(tkn.type) + WHITE + "' instead.", line, current - tkn.value.size(), current);
            }        
        }
        i++;
    }
    if (i != head->columns.size()) {
        throw ParseError(tkn, "Too few arguments in row call.", line, current - tkn.value.size(), current);
    }
}

void ErrorScan::getElement() {
    consume(LEFT_PAREN, "Expected '(', got '" + peek().value + "' instead.");
    if (advance().type != LITERAL) {
        throw ParseError(previous(), "Expected a name, got '" + BOLD + getTypeString(previous().type) + WHITE + "' instead.", line, current - previous().value.size(), current);
    } else {
        if (head->getColumn(previous().value) == NULL) {
            throw ParseError(previous(), "Column '" + BOLD + previous().value + WHITE + "' not in table.", line, current - previous().value.size(), current);
        }
    }
    if (advance().type != INT_TYPE) {
        throw ParseError(previous(), "Expected an index, got '" + BOLD + getTypeString(previous().type) + BOLD + "' instead.", line, current - previous().value.size(), current);
    } else {
        if (std::stoi(previous().value) >= head->columns[0]->rowLen()) {
            throw ParseError(previous(), "Index '" + BOLD + previous().value + WHITE + "' out of range.", line, current - previous().value.size(), current);
        }
    }
    consume(RIGHT_PAREN, "Expected ')', got '" + BOLD + previous().value + WHITE + "' instead.");
}

void ErrorScan::editRow() {
    consume(LEFT_PAREN, "Expected '(', got '" + BOLD + peek().value + WHITE + "' instead.");

    if (advance().type != INT_TYPE) {
        throw ParseError(previous(), "Expected index, got '" + BOLD + previous().value + WHITE + "' instead.", line, current - previous().value.size(), current);
    }
    if (std::stoi(previous().value) >= head->columns[0]->rowLen()) {
        throw ParseError(previous(), "Index '" + BOLD + previous().value + WHITE + "' out of range.", line, current - previous().value.size(), current);
    }

    Token tkn = previous();
    int i = 0;
    while ((tkn = advance()).type != RIGHT_PAREN) {
        if (i >= head->columns.size()) {
            throw ParseError(tkn, "Expected ')'.", line, current - tkn.value.size(), current);
        }
        if (head->columns[i]->getTypeName() == "i") {
            if (tkn.type != INT_TYPE) {
                throw ParseError(tkn, "Expected type 'INT', got '" + BOLD + getTypeString(tkn.type) + WHITE + "' instead.", line, current - tkn.value.size(), current);
            }
        } else if (head->columns[i]->getTypeName() == "d") {
            if (tkn.type != DOUBLE_TYPE) {
                throw ParseError(tkn, "Expected type 'DOUBLE', got '" + BOLD + getTypeString(tkn.type) + WHITE + "' instead.", line, current - tkn.value.size(), current);
            }
        } else if (head->columns[i]->getTypeName() == "NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE") {
            if (tkn.type != LITERAL) {
                throw ParseError(tkn, "Expected type 'STRING', got '" + BOLD + getTypeString(tkn.type) + WHITE + "' instead.", line, current - tkn.value.size(), current);
            }        
        } else if (head->columns[i]->getTypeName() == "b") {
            if (tkn.type != BOOL) {
                throw ParseError(tkn, "Expected type 'DOUBLE', got '" + BOLD + getTypeString(tkn.type) + WHITE + "' instead.", line, current - tkn.value.size(), current);
            }        
        }
        i++;
    }
    if (i != head->columns.size()) {
        throw ParseError(tkn, "Too few arguments in row call.", line, current - tkn.value.size(), current);
    }
}

void ErrorScan::removeColumn() {
    consume(LEFT_PAREN, "Expected '(', got '" + peek().value + "' instead.");

    if (advance().type != INT_TYPE) {
        throw ParseError(previous(), "Expected index, got '" + BOLD + previous().value + WHITE + "' instead.", line, current - previous().value.size(), current);
    }
    if (std::stoi(previous().value) >= head->columns.size()) {
        throw ParseError(previous(), "Index '" + BOLD + previous().value + WHITE + "' out of range.", line, current - previous().value.size(), current);
    }

    consume(RIGHT_PAREN, "Expected ')', got '" + BOLD + peek().value + WHITE + "' instead.");
}

void ErrorScan::removeRow() {
    consume(LEFT_PAREN, "Expected '(', got '" + BOLD + peek().value + WHITE + "' instead.");

    if (advance().type != INT_TYPE) {
        throw ParseError(previous(), "Expected index, got '" + BOLD + previous().value + WHITE + "' instead.", line, current - previous().value.size(), current);
    }
    if (std::stoi(previous().value) >= head->columns[0]->rowLen()) {
        throw ParseError(previous(), "Index '" + BOLD + previous().value + WHITE + "' out of range.", line, current - previous().value.size(), current);
    }

    consume(RIGHT_PAREN, "Expected ')', got '" + WHITE + peek().value + BOLD + "' instead.");
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
            default:
                throw ParseError(previous(), "Expected method, got '" + BOLD + previous().value + WHITE + "' instead.", line, current - previous().value.size(), current);
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

    throw ParseError(previous(), msg, line, current - previous().value.size(), current);
}
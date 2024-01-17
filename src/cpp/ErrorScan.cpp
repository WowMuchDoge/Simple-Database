#include "../include/ErrorScan.h"

ErrorScan::ErrorScan(std::vector<Token> tkns, TableHead* hd, std::vector<std::string> lns) : tokens(tkns), head(hd), lines(lns) {}

static std::string getTypeString(TokenType type) {
    if (type == INT_TYPE) return "INT";
    if (type == LITERAL) return "STRING";
    if (type == TRUE || true == FALSE) return "BOOL";
    if (type == DOUBLE_TYPE) return "DOUBLE";
}

void ErrorScan::addColumn() {
    consume(LEFT_PAREN, "Expected '(', got '" + peek().value + "' instead.");

    if ((advance().type != STRING) && (previous().type != INT) && (previous().type != DOUBLE) && (previous().type != BOOL)) {
        throw ParseError(previous(), "Expected a type, got '" + previous().value + "' instead.", lines, current - previous().value.size(), current);
    }
    if ((advance().type != LITERAL) && (previous().type != VALUE)) {
        throw ParseError(previous(), "Expected a value, got '" + previous().value + "' instead.", lines, current - previous().value.size(), current);
    }

    consume(RIGHT_PAREN, "Expected ')', got '" + peek().value + "' instead.");
}

void ErrorScan::addRow() {
    consume(LEFT_PAREN, "Expected '(', got '" + peek().value + "' instead.");

    Token tkn = previous();
    std::cout << "Columns index 0 type is " << head->columns[0]->getTypeName() << "Token type is " << tkn.type << '\n';
    int i = 0;
    while ((tkn = advance()).type != RIGHT_PAREN) {
        if (head->columns[i]->getTypeName() == "i") {
            if (tkn.type != INT_TYPE) {
                throw ParseError(tkn, "Expected type 'INT', got '" + getTypeString(tkn.type) + "'.", lines, current - tkn.value.size(), current);
            }
        } else if (head->columns[i]->getTypeName() == "d") {
            if (tkn.type != DOUBLE_TYPE) {
                throw ParseError(tkn, "Expected type 'DOUBLE', got '" + getTypeString(tkn.type) + "'.", lines, current - tkn.value.size(), current);
            }
        } else if (head->columns[i]->getTypeName() == "NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE") {
            if (tkn.type != LITERAL) {
                throw ParseError(tkn, "Expected type 'STRING', got '" + getTypeString(tkn.type) + "'.", lines, current - tkn.value.size(), current);
            }        
        } else if (head->columns[i]->getTypeName() == "b") {
            if (tkn.type != BOOL) {
                throw ParseError(tkn, "Expected type 'DOUBLE', got '" + getTypeString(tkn.type) + "'.", lines, current - tkn.value.size(), current);
            }        
        }
        i++;
    } 
}

void ErrorScan::checkTokens() {
    while (!isAtEnd()) {
        switch(advance().type) {
            case ADD_COLUMN: addColumn(); break;
            case ADD_ROW: addRow(); break;
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

    throw ParseError(previous(), msg, lines, current - previous().value.size(), current);
}
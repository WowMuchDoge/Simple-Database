#include "../include/ErrorScan.h"

ErrorScan::ErrorScan(std::vector<Token> tkns, TableHead* hd, std::vector<std::string> lns) : tokens(tkns), head(hd), lines(lns) {}

void ErrorScan::addColumn() {
    consume(LEFT_PAREN, "Expected '(', got '" + peek().value + "' instead.");

    if ((advance().type != STRING) && (previous().type != INT) && (previous().type != DOUBLE) && (previous().type != BOOL)) {
        throw ParseError(previous(), "Expected a type, got '" + previous().value + "' instead.", lines, current - previous().value.size(), current);
    }
    if ((advance().type != LITERAL) && (previous().type != VALUE)) {
        throw ParseError(previous(), "Expected a value, got '" + previous().value + "' instead.", lines, current - previous().value.size(), current);
    }

    consume(LEFT_PAREN, "Expected ')', got '" + peek().value + "' instead.");
}

void ErrorScan::addRow() {}

void ErrorScan::checkTokens() {
    while (!isAtEnd()) {
        switch(advance().type) {
            case ADD_COLUMN: addColumn();
            case ADD_ROW: addRow();
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
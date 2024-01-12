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
    advance(); // Add error handing to ensure this is a parenthesis
    if (peek().type != LITERAL) exit(1);
    head->addColumn(advance().type, advance().value);
    advance(); //Error handling here too
}

void Parser::parse() {
    switch(advance().type) {
        case ADD_COLUMN: addColumn();
        case ADD_ROW:
        case GET_ELEMENT:
        default:
            exit(1);
    }
}
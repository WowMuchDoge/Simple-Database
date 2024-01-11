#include "../include/Scanner.h"

bool Scanner::isAtEnd() {
    return source[current] == '\0';
}

char Scanner::previous() {
    return source[current - 1];
}

char Scanner::peek() {
    return source[current];
}

char Scanner::advance() {
    if (isAtEnd()) return previous();

    return source[current++];
}

void Scanner::addToken(TokenType type) {
    tokens.push_back(Token("", type));
    advance();
}

void Scanner::addToken(std::string str) {
    tokens.push_back(Token(str, VALUE));
}

bool Scanner::isAlpha() {
    return (peek() >= 'A' && peek() <= 'Z') || peek() == '_';
}

bool Scanner::isDigit() {
    return peek() >= '0' && peek() <= '9';
}

void Scanner::number() {
    while (isDigit()) advance();
    if (peek() == '.' && (source[current + 1] >= '0' && source[current + 1] < '9')) {
        advance();
        while (isDigit()) advance();
    }
    addToken(source.substr(start, current - start));
}

void Scanner::identifier() {
    while (isAlpha()) {
        advance();
    }
    auto pos = keywords.find(source.substr(start, current - start));

    if (pos == keywords.end()) {
        std::cout << "Unknown identifier: " << source.substr(start, current - start) << ".\n";
        exit(1);
    };

    addToken(pos->second);
}

std::vector<Token> Scanner::scanTokens() {
    while (!isAtEnd()) {
        start = current;
        char c = advance();
        switch(c) {
            case '(': addToken(LEFT_PAREN); break;
            case ')': addToken(RIGHT_PAREN); break;
            default:
                if (isDigit()) {
                    number();
                    break;
                } else if (isAlpha()) {
                    identifier();
                    break;
                } else {
                    advance();
                    break;
                }
        }
    }
    addToken(END_OF_TEXT);
    return tokens;
}
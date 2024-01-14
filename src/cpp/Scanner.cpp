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
}

void Scanner::addToken(std::string str) {
    tokens.push_back(Token(str, VALUE));
}

void Scanner::addToken(TokenType type, std::string str) {
    tokens.push_back(Token(str, type));
}

bool Scanner::isAlpha(char c) {
    return (c >= 'A' && c <= 'Z') || c == '_';
}

bool Scanner::isDigit(char c) {
    return c >= '0' && c <= '9';
}

void Scanner::number() {
    while (isDigit(peek())) advance();
    if (peek() == '.' && (source[current + 1] >= '0' && source[current + 1] < '9')) {
        advance();
        while (isDigit(peek())) advance();
    }
    addToken(source.substr(start, current - start));
}

void Scanner::identifier() {
    while (isAlpha(peek())) advance();
    auto pos = keywords.find(source.substr(start, current - start));

    if (pos == keywords.end()) {
        exit(1);
    };
    addToken(pos->second);
}

void Scanner::string() {
    advance();
    
    while (peek() != 39) {
        if (isAtEnd()) {
            exit(1);
        }
        advance();
    }
    addToken(VALUE, source.substr(start + 1, current - start - 1));
}

std::vector<Token> Scanner::scanTokens() {
    while (!isAtEnd()) {
        start = current;
        char c = advance();
        switch(c) {
            case '(': addToken(LEFT_PAREN); break;
            case ')': addToken(RIGHT_PAREN); break;
            case 39: string();
            default:
                if (isDigit(c)) {
                    number();
                    break;
                } else if (isAlpha(c)) {
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
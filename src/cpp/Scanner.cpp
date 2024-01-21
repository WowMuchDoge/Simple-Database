#include <iostream>
#include <sstream>

#include "../include/Scanner.h"
#include "../include/LexError.h"

bool Scanner::isAtEnd() {
    return source[current] == '\0';
}

bool Scanner::isAlpha(char c) {
    return (c >= 'A' && c <= 'Z') || 
           (c >= 'a' && c <= 'z') ||
            c == '_';
}

bool Scanner::isDigit(char c) {
    return (c >= '0' && c <= '9') || c == '-';
}

void Scanner::setText(std::string txt) {
    source = txt;
}



std::vector<Token> Scanner::scanTokens(std::string fileName, int rLine) {
    tokens.clear();
    int line = 1;
    bool doubleState = false;
    current = 0;
    char c = source[current];
    while (current < source.size()) {
        start = current;
        c = source[current];
        switch(c) {
            case '(': tokens.push_back(Token("(", LEFT_PAREN, rLine, current)); current++; break;
            case ')': tokens.push_back(Token(")", RIGHT_PAREN, rLine, current)); current++; break;
            case '\n': line++; current++; break;
            case ' ':
            case '\r':
            case '\t': current++; break;
            case '"':
                while (source[++current] != '"') {
                    if (source[current] == '\0') {
                        throw LexError("Unterminated string.", rLine, start, current - 1, source);
                    }
                }
                tokens.push_back(Token(source.substr(start, current - start + 1), LITERAL, rLine, start));
                current++;
                break;
            default:
                if (isAlpha(c)) {
                    while (isAlpha(source[++current]));
                    auto pos = keywords.find(source.substr(start, current - start));
                    if (pos == keywords.end()) {
                        throw LexError(("Unknown identifier '" + source.substr(start, current - start) + "'."), rLine, start, current - 1, source);
                        break;
                    }
                    tokens.push_back(Token(pos->first, pos->second, rLine, start));
                    break;
                } else if (isDigit(c)) {
                    while (isDigit(source[++current]));
                    if (source[current] == '.') {
                        while (isDigit(source[++current]));
                        doubleState = true;
                    }
                    tokens.push_back(Token(source.substr(start, current - start), (doubleState ? DOUBLE_TYPE : INT_TYPE), rLine, start));
                    break;
                } else {
                    throw LexError(("Unknown symbol '" + std::string(1, source[current]) + "'."), rLine, current, current, source);
                }
                break;
        }
    }
    tokens.push_back(Token("", END_OF_TEXT, rLine, current));
    return tokens;
}
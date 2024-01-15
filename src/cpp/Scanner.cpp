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
    return c >= '0' && c <= '9';
}

void Scanner::setText(std::string txt) {
    source = txt;
}

std::vector<Token> Scanner::scanTokens(std::string fileName) {
    std::vector<std::string> lines;
    std::istringstream src(source);
    std::string ln;
    while (getline(src, ln)) {
        lines.push_back(ln);
    }
    int line = 1;
    current = 0;
    char c = source[current];
    while (current < source.size()) {
        start = current;
        c = source[current];
        switch(c) {
            case '(': tokens.push_back(Token("", LEFT_PAREN)); current++; break;
            case ')': tokens.push_back(Token("", RIGHT_PAREN)); current++; break;
            case '\n': line++; current++;
            case '"':
                while (source[++current] != '"') {
                    if (source[current] == '\0') {
                        exit(1);
                    }
                }
                tokens.push_back(Token(source.substr(start + 1, current - start - 1), VALUE));
                current++;
                break;
            default:
                if (isAlpha(c)) {
                    while (isAlpha(source[++current]));
                    auto pos = keywords.find(source.substr(start, current - start));
                    if (pos == keywords.end()) {
                        throw LexError(("Unknown identifier '" + source.substr(start, current - start) + "'."), line, start, current - 1, lines[line - 1]);
                        break;
                    }
                    tokens.push_back(Token("", pos->second));
                    break;
                } else if (isDigit(c)) {
                    while (isDigit(source[++current]));
                    if (source[current] == '.') {
                        while (isDigit(source[++current]));
                    }
                    tokens.push_back(Token(source.substr(start, current - start), VALUE));
                    break;
                } else {
                    current++;
                    break;
                }
                break;
        }
    }
    tokens.push_back(Token("", END_OF_TEXT));
    return tokens;
}
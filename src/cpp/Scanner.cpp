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
    int line = 1;
    current = 0;
    char c = source[current];
    while (current < source.size()) {
        start = current;
        c = source[current];
        switch(c) {
            case '(': tokens.push_back(Token("(", LEFT_PAREN, line, current)); current++; break;
            case ')': tokens.push_back(Token(")", RIGHT_PAREN, line, current)); current++; break;
            case '\n': line++; current++;
            case ' ':
            case '\r':
            case '\t': current++; break;
            case '"':
                while (source[++current] != '"') {
                    if (source[current] == '\0') {
                        throw LexError("Unterminated string.", line, start, current - 1, lines[line - 1]);
                    }
                }
                tokens.push_back(Token(source.substr(start + 1, current - start - 1), VALUE, line, start));
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
                    tokens.push_back(Token(pos->first, pos->second, line, start));
                    break;
                } else if (isDigit(c)) {
                    while (isDigit(source[++current]));
                    if (source[current] == '.') {
                        while (isDigit(source[++current]));
                    }
                    tokens.push_back(Token(source.substr(start, current - start), VALUE, line, start));
                    break;
                } else {
                    throw LexError(("Unknown symbol '" + std::string(1, source[current]) + "'."), line, current, current, lines[line - 1]);
                }
                break;
        }
    }
    tokens.push_back(Token("", END_OF_TEXT, line, current));
    return tokens;
}

std::vector<std::string> Scanner::getLines() {
    return lines;
}

void Scanner::setLines() {
    lines.clear();
    std::istringstream src(source);
    std::string ln;
    while (getline(src, ln)) {
        lines.push_back(ln);
        std::cout << ln << '\n';
    }
}

std::vector<Token>* Scanner::getTokens() {
    return &tokens;
}
#include "../include/Scanner.h"

bool Scanner::isAtEnd() {
    return source[current] == '\0';
}

bool Scanner::isAlpha(char c) {
    return (c >= 'A' && c <= 'Z') || c == '_';
}

bool Scanner::isDigit(char c) {
    return c >= '0' && c <= '9';
}

void Scanner::setText(std::string txt) {
    source = txt;
}

std::vector<Token> Scanner::scanTokens() {
    char c = source[current];
    while (current < source.size()) {
        start = current;
        c = source[current];
        switch(c) {
            case '(': tokens.push_back(Token("", LEFT_PAREN)); current++; break;
            case ')': tokens.push_back(Token("", RIGHT_PAREN)); current++; break;
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
                        std::cout << "Unknown substring " << source.substr(start, current - start) << ".\n";
                        exit(1);
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
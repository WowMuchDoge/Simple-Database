#include  "../include/ParseError.h"

#include "../include/Constants.h"

#ifndef _WIN32
ParseError::ParseError(Token token, std::string message, std::string line) {
    std::string lNum = std::to_string(token.line);
    std::string s1 = "  ";
    std::string s2;
    std::string errLine = line.substr(0, token.offset) + RED + line.substr(token.offset, token.value.size()) + WHITE + line.substr(token.offset + token.value.size());
    int dif = 4 - lNum.size();
    s1 += lNum;
    for (int i = 0; i < dif; i++) {
        s1 += " ";
    }
    s1 += "|    ";

    s2 += "      |    ";
    for (int i = 0; i < token.offset; i++) {
        s2 += " ";
    }

    s2 += RED;
    s2 += "^";

    for (int i = 0; i < token.value.size() - 1; i++) {
        s2 += "~";
    }
    s2 += WHITE;

    str = RED + "\nParsing error: " + WHITE + message + "\n" + s1 + errLine + "\n" + s2 + '\n';
}
#endif

#ifdef _WIN32
ParseError::ParseError(Token token, std::string message, std::string line) {
    std::string lNum = std::to_string(token.line);
    std::string s1 = "  ";
    std::string s2;
    int dif = 4 - lNum.size();
    s1 += lNum;
    for (int i = 0; i < dif; i++) {
        s1 += " ";
    }
    s1 += "|    ";
    s2 += "      |    ";
    for (int i = 0; i < token.offset; i++) {
        s2 += " ";
    }

    s2 += "^";

    for (int i = 0; i < token.value.size() - 1; i++) {
        s2 += "~";
    }

    str = "\nParsing error: " + message + "\n" + s1 + line + "\n" + s2 + "\n";
}
#endif

std::string ParseError::getMessage() {
    return str;
}
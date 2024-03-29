#include "../include/LexError.h"

#include <iostream>
#include <string>
#ifdef _WIN32
#include "windows.h"
#endif
#include <fstream>

#include "../include/Constants.h"

#ifdef _WIN32
LexError::LexError(std::string message, int lineNumber, int sIndex, int eIndex, std::string line) {
    std::string lNum = std::to_string(lineNumber);
    std::string s1;
    std::string errPart = line.substr(0, sIndex) + line.substr(sIndex, eIndex - sIndex + 1) + line.substr(eIndex + 1);
    s1 += "  ";
    int dif = 5 - lNum.length();
    s1 += lNum;
    for (int i = 0; i < dif; i++) {
        s1 += " ";
    }
    std::string s2;
    s2 += "       |   ";
    for (int i = 0; i <= sIndex; i++) {
        s2.append(" ");
    }
    s2.append("^");
    for (int i = sIndex + 1; i <= eIndex; i++) {
        s2.append("~");
    }
    str = "\nLexical Error: " + message + "\n" + s1 + "|    " + errPart + "\n" + s2 + '\n';
}
#endif

#ifndef _WIN32
LexError::LexError(std::string message, int lineNumber, int sIndex, int eIndex, std::string line) {
    std::string lNum = std::to_string(lineNumber);
    std::string s1;
    std::string errPart = line.substr(0, sIndex) + RED + line.substr(sIndex, eIndex - sIndex + 1) + WHITE + line.substr(eIndex + 1);
    s1 += "  ";
    int dif = 5 - lNum.length();
    s1 += lNum;
    for (int i = 0; i < dif; i++) {
        s1 += " ";
    }
    std::string s2;
    s2 += "       |   ";
    for (int i = 0; i <= sIndex; i++) {
        s2.append(" ");
    }
    s2.append(RED + "^");
    for (int i = sIndex + 1; i <= eIndex; i++) {
        s2.append("~");
    }
    s2.append(WHITE);
    str = "\n" + RED + "Lexical Error: " + WHITE + message + "\n" + s1 + "|    " + errPart + "\n" + s2 + '\n';
}
#endif

std::string LexError::getMessage() {
    return str;
}
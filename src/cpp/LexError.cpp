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
    msg = message;
    std::string lNum = std::to_string(lineNumber);
    std::string errPart = line.substr(0, sIndex) + RED + line.substr(sIndex, eIndex - sIndex + 1) + WHITE + line.substr(eIndex + 1);
    l1 = line.substr(0, sIndex);
    l2 = line.substr(sIndex, eIndex - sIndex + 1);
    l3 = line.substr(eIndex + 1);
    s1 += "  ";
    int dif = 5 - lNum.length();
    s1 += lNum;
    for (int i = 0; i < dif; i++) {
        s1 += " ";
    }
    for (int i = 0; i <= sIndex; i++) {
        s2.append(" ");
    }
    s2.append("^");
    for (int i = sIndex + 1; i <= eIndex; i++) {
        s2.append("~");
    }

}

std::string LexError::getMessage() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 4);
    std::cout << "\nLexical Error: ";
    SetConsoleTextAttribute(hConsole, 7);
    std::cout << msg << "\n" << s1 << "|    " << l1;
    SetConsoleTextAttribute(hConsole, 4);
    std::cout << l2;
    SetConsoleTextAttribute(hConsole, 7);
    std::cout << l3 << "\n";
    SetConsoleTextAttribute(hConsole, 7);
    std::cout << "       |   ";
    SetConsoleTextAttribute(hConsole, 4);
    std::cout << s2 + '\n';
    SetConsoleTextAttribute(hConsole, 7);
    return "";
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

std::string LexError::getMessage() {
    return str;
}
#endif
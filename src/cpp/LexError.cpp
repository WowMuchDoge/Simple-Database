#include "../include/LexError.h"

#include <string>
#include <fstream>

LexError::LexError(std::string message, int lineNumber, int sIndex, int eIndex, std::string line) {
    std::string lNum = std::to_string(lineNumber);
    std::string s1;
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
    str = "\nLexical Error: " + message + "\n" + s1 + "|    " + line + "\n" + s2 + '\n';
}

std::string LexError::getMessage() {
    return str;
}
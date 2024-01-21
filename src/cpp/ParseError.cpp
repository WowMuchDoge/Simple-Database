#include  "../include/ParseError.h"

ParseError::ParseError(Token token, std::string message, std::string line, int startIndex, int endIndex) {
    std::string lNum = std::to_string(token.line);
    std::string s1 = "  ";
    std::string s2;
    int dif = 4 - lNum.size();
    s1 += lNum;
    for (int i = 0; i < dif; i++) {
        s1 += " ";
    }
    s1 += "|    ";

    for (int i = 0; i < token.offset + 11; i++) {
        s2 += " ";
    }

    s2 += "^";

    for (int i = 0; i < token.value.size() - 1; i++) {
        s2 += "~";
    }

    str = "\nParsing error: " + message + "\n" + s1 + line + "\n" + s2 + "\n";

    eIndex = endIndex;
    sIndex = startIndex;
}



std::string ParseError::getMessage() {
    return str;
}
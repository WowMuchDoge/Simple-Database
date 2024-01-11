#include <iostream>

#include "../include/ColumnHead.h"
#include "../include/TableHead.h"

#include "../include/Scanner.h"
#include "../include/Token.h"

int main() {
    Scanner scanner("ADD_ROW(TRUE FALSE)");

    std::vector<Token> tokens = scanner.scanTokens();

    for (Token token : tokens) {
        std::cout << token.type << ", " << token.value << '\n';
    }
}
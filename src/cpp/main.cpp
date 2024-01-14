#include <iostream>

#include "../include/ColumnHead.h"
#include "../include/TableHead.h"
#include "../include/Scanner.h"
#include "../include/Parser.h"
#include "../include/Token.h"

int main() {
    Scanner scanner("ADD_COLUMN(DOUBLE, 'xjfjkgf')  ADD_COLUMN(DOUBLE, 'asdf')  ADD_ROW(69.420, 2345.2)  ADD_ROW(692.410, 23439.1)  GET_ELEMENT('asdf', 1)");

    TableHead head;

    std::vector<Token> tokens = scanner.scanTokens();

    for (Token token : tokens) {
        std::cout << token.type << ", " << token.value << '\n';
    }

    Parser parser(tokens, &head);
    parser.parse();
}
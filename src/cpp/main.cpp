#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../include/ColumnHead.h"
#include "../include/TableHead.h"
#include "../include/Scanner.h"
#include "../include/Parser.h"
#include "../include/Token.h"
#include "../include/LexError.h"
#include "../include/ErrorScan.h"

std::string text = "";

std::vector<Token> t;
TableHead head;

Scanner scanner(text);
Parser parser(t, &head);

void run(std::string input) {
    scanner.setText(input);
    std::vector<Token> tokens;
    scanner.setLines();
    int sIndex = tokens.size();

    try {
        tokens = scanner.scanTokens("<stdin>");
    } catch (LexError error) {
        std::cout << error.getMessage();
        return;
    }

    int eIndex = tokens.size() - 1;

    for (Token token : tokens) {
        std::cout << token.value << '\n';
    }

    try {
        ErrorScan eScan(tokens, &head, scanner.getLines());
        eScan.checkTokens();
    } catch (ParseError error) {
        tokens.erase(tokens.begin() + sIndex, tokens.begin() + eIndex - 1);
        std::cout << error.getMessage();
        return;
    }

    parser.setInput(tokens);
    parser.parse();
}

void runCLI() {
    std::cout << "You have now entered command line mode\nType " << '"' << "help" << '"' << " for more information\n";
    while (true) {
        std::string txt;
        std::cout << ">>>";
        std::getline(std::cin, txt);
        if (txt == "help") {
            std::cout << "Help stuff\n";
        } else if (txt.substr(0, 3) == std::string("save").substr(0, 3)) {
            std::string filename = txt.substr(4, txt.size() - 1);
            head.writeToFile(filename);
        } else if (txt == "exit") {
            break;
        } else if (txt == "\0") {
            std::cout << '\n';
            break;
        } else {
            run(txt);
        }
    }
}

void runFile(char* filename) {
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        run(line);
    }

    file.close();
    head.writeToFile("database.txt");
}

int main(int argc, char** argv) {
    std::ifstream file("database.txt");
    std::string line;

    while (std::getline(file, line)) {
        text += line + '\n';
    }

    if (argc == 1) {
        runCLI();
    } else if (argc == 2) {
        runFile(argv[1]);
    } else {
        exit(1);
    }
}

// int main() {
//     LexError error("Unknown identifier 'ADS_COLUMN'", 1, 0, 9, "ADS_COLUMN(poggers 'double')");
//     Scanner scanner("sdifj(sjfd, sfkj)");
//     try {
//         std::vector<Token> tokens = scanner.scanTokens();
//     } catch (LexError error) {
//         std::cout << error.getMessage();
//         break;
//     }

//     std::cout << tokens[0].type << '\n';
// }
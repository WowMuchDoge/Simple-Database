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

bool hadError = false;

int rLine = 1;

void run(std::string input) {
    scanner.setText(input);
    std::vector<Token> tokens;
    scanner.setLines();
    int sIndex = tokens.size();

    try {
        tokens = scanner.scanTokens("<stdin>", rLine);
    } catch (LexError error) {
        std::cout << error.getMessage();
        hadError = true;
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
        hadError = true;
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
            std::cout << txt.size() << '\n';
            std::string filename = txt.substr(4, txt.size() - 1);
            if (txt.size() < 6) {
                std::cout << "Need file name to save to.\n";
                break;
            }
            head.writeToFile(filename + ".txt");
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

void runFile(int argc, char** args) {

    if (argc > 2) {
        std::cout << "Comand-line Error: Too many arguments provided.\n";
        exit(54);
    } else if (argc < 2) {
        std::cout << "Comand-line Error: Too few arguments provided.\n";
        exit(55);
    }

    std::ifstream file(args[1]);
    std::string line;
    std::string sLines;

    if (!file.is_open()) {
        std::cout << "Comand-line Error: File cannot open.\n";
        exit(56);
    }

    while (std::getline(file, line)) {
        run(line);
        rLine++;
    }

    std::cout << sLines;

    file.close();

    if (!hadError) {
        head.writeToFile(args[1]);
    }
}

int main(int argc, char** argv) {
    if (argc == 1) {
        runCLI();
    } else if (argc == 2) {
        runFile(argc, argv);
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
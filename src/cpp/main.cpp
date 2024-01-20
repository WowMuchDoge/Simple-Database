#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstring>
#include <memory>

#include "../include/ColumnHead.h"
#include "../include/TableHead.h"
#include "../include/Scanner.h"
#include "../include/Parser.h"
#include "../include/Token.h"
#include "../include/LexError.h"
#include "../include/ErrorScan.h"

void runFile(int argc, char** args);

std::vector<Token> tokens;
TableHead head;

Scanner scanner("");
Parser parser(tokens, &head);

bool hadError = false;
int rLine = 1;

void run(std::string input, std::string file) {
    scanner.setText(input);
    scanner.setLines();

    try {
        tokens = scanner.scanTokens("<stdin>", rLine);
    } catch (LexError error) {
        std::cout << "In file " << file;
        std::cout << error.getMessage();
        hadError = true;
        return;
    }

    int eIndex = tokens.size() - 1;

    for (Token token : tokens) {
        std::cout << token.value << '\n';
    }

    try {
        ErrorScan eScan(tokens, &head, input);
        eScan.checkTokens();
    } catch (ParseError error) {
        tokens.clear();
        std::cout << "In file " << file;
        std::cout << error.getMessage();
        hadError = true;
        return;
    }

    parser.setInput(tokens);
    tokens.clear();
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
            std::string filename = txt.substr(5, txt.size() - 2);
            if (txt.size() < 6) {
                std::cout << "Need file name to save to.\n";
                break;
            }
            head.writeToFile(filename + ".txt");
        } else if (txt.substr(0, 3) == std::string("load").substr(0, 3)) {
            std::cout << txt.size() << '\n';
            std::string filename = txt.substr(5, txt.size() - 2);
            if (txt.size() < 6) {
                std::cout << "Need file name to load from to.\n";
                break;
            }
            char* el1 = (char*)malloc(2 * sizeof(char));
            char* file = (char*)malloc(100 * sizeof(char));
            const char** list = (const char**)malloc(2 * sizeof(char*));
            list[0] = "";
            list[1] = filename.c_str();
            runFile(2, (char**)list);
        } else if (txt == "exit") {
            break;
        } else if (txt == "\0") {
            std::cout << '\n';
            break;
        } else {
            run(txt, "<stdin>");
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
        std::cout << "Comand-line Error: File '" + std::string(args[1]) + "' cannot open.\n" << std::strerror(errno) << std::endl;;
        file.close();
        exit(56);
    }

    while (std::getline(file, line)) {
        run(line, "'" + std::string(args[1]) + "'");
        rLine++;
    }

    file.close();

    std::cout << sLines;
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
// }scanner.scanTokens
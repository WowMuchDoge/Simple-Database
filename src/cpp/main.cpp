#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <memory>

#include "../include/Constants.h"
#include "../include/ColumnHead.h"
#include "../include/TableHead.h"
#include "../include/Scanner.h"
#include "../include/Parser.h"
#include "../include/Token.h"
#include "../include/LexError.h"
#include "../include/ErrorScan.h"

void runFile(int argc, char** args, std::unique_ptr<Scanner>& scanner, std::unique_ptr<Parser>& parser, std::unique_ptr<TableHead>& head);

std::vector<Token> tokens;

int rLine = 1;

void run(std::string input, std::string file, std::unique_ptr<Scanner>& scanner, std::unique_ptr<Parser>& parser, std::unique_ptr<TableHead>& head) {
    scanner->setText(input);

    try {
        tokens = scanner->scanTokens("<stdin>", rLine);
    } catch (LexError error) {
        std::cout << BOLD + "In file " << file;
        std::cout << error.getMessage();
        return;
    }

    int eIndex = tokens.size() - 1;

    try {
        ErrorScan eScan(tokens, head.get(), input);
        eScan.checkTokens();
    } catch (ParseError error) {
        tokens.clear();
        std::cout << BOLD + "In file " << file;
        std::cout << error.getMessage();
        return;
    }

    parser->setInput(tokens);
    tokens.clear();
    parser->parse();
}

void runCLI(std::unique_ptr<Scanner>& scanner, std::unique_ptr<Parser>& parser, std::unique_ptr<TableHead>& head) {
    std::cout << "You have now entered command line mode\nType " << '"' << "help" << '"' << " for more information\n";
    while (true) {
        std::string txt;
        std::cout << ">>>";
        std::getline(std::cin, txt);
        if (txt == "help") {
            std::cout << StringConstants::helpText;
        } else if (txt.substr(0, 4) == std::string("save").substr(0, 4)) {
            std::string filename = txt.substr(5, txt.size() - 2);
            if (txt.size() < 6) {
                std::cout << "Need file name to save to.\n";
                break;
            }
            head->writeToFile(filename);
        } else if (txt.substr(0, 4) == std::string("load").substr(0, 4)) {
            std::string filename = txt.substr(5, txt.size() - 2);
            if (txt.size() < 6) {
                std::cout << "Need file name to load from to.\n";
                break;
            }
            const char** list = (const char**)malloc(2 * sizeof(char*));
            list[0] = "";
            list[1] = filename.c_str();
            runFile(2, (char**)list, scanner, parser, head);
            free(list);
        } else if (txt == "exit") {
            break;
        } else if (txt == "\0") {
            std::cout << '\n';
            break;    
        } else {
            run(txt, "<stdin>", scanner, parser, head);
        }
    }
}

void runFile(int argc, char** args, std::unique_ptr<Scanner>& scanner, std::unique_ptr<Parser>& parser, std::unique_ptr<TableHead>& head) {
    std::ifstream file(args[1]);
    std::string line;
    std::string sLines;

    if (!file.is_open()) {
        std::cout << "Comand-line Error: Cannot open file '" + std::string(args[1]) + "'.\n" << std::strerror(errno) << std::endl;
        file.close();
        exit(FILE_NOT_OPEN);
    }

    while (std::getline(file, line)) {
        run(line, "'" + std::string(args[1]) + "'", scanner, parser, head);
        rLine++;
    }

    file.close();
}

int main(int argc, char** argv) {
    std::unique_ptr<TableHead> head = std::make_unique<TableHead>();
    std::unique_ptr<Scanner> scanner = std::make_unique<Scanner>("");
    std::unique_ptr<Parser> parser = std::make_unique<Parser>(tokens, head.get());
    if (argc == 1) {
        runCLI(scanner, parser, head);
    } else if (argc == 2) {
        runFile(argc, argv, scanner, parser, head);
    } else if (argc > 2) {
        std::cout << "Comand-line Error: Too many arguments provided.\n";
        exit(MANY_ARGS);
    }
}
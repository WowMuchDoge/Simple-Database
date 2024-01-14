#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../include/ColumnHead.h"
#include "../include/TableHead.h"
#include "../include/Scanner.h"
#include "../include/Parser.h"
#include "../include/Token.h"

std::string text = "";

std::vector<Token> t;
TableHead head;

Scanner scanner(text);
Parser parser(t, &head);

int commandsRun = 0;

void run(std::string input) {
    text.append(" " + input + " ");
    std::cout << text << '\n';
    scanner.setText(text);
    std::vector<Token> tokens = scanner.scanTokens();

    parser.setInput(tokens);
    parser.parse();
    commandsRun++;
}

void runCLI() {
    std::cout << "You have now entered command line mode\nType " << '"' << "help" << '"' << " for more information\n";
    while (true) {
        std::string txt;
        std::cout << ">>>";
        std::getline(std::cin, txt);
        if (txt == "help") {
            std::cout << "Help stuff\n";
        } else if (txt == "save") {
            head.writeToFile();
        } else {
            run(txt);
        }
    }
}

void runFile(char* filename) {

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
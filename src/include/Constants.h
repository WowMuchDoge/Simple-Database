#pragma once

#include <string>

#define FEW_ARGS 10
#define MANY_ARGS 11

#define UNKOWN_TYPE 20
#define UNKOWN_METHOD 21

#define OUT_OF_RANGE 30

#define FILE_NOT_OPEN 40

#define WHITE std::string("\e[0;37m")
#define RED std::string("\e[0;31m")
#define BOLD std::string("\e[1;37m")
#define BOLD_RED std::string("\e[1;31m")

namespace StringConstants {
    const std::string helpText = "\n                == COMMANDS ==\n\n"
    "save <filename>: Save current database state to a text file\n"
    "load <filename>: Load another database state\n"
    "exit: Exits out of the program\n\n"
    "            == DATABASE METHODS ==\n\n"
    "ADD_COLUMN(<type> " + std::string(1, '"') + "<name>" + std::string(1, '"') + "): Adds a column with the specified name\n\n"
    "ADD_ROW(<element>...): Add a row with n elements (amount and type of elements depend on the corresponding column)\n\n"
    "GET_ELEMENT(" + std::string(1, '"') + "<name>" + std::string(1, '"') + " <index>): Prints the element at column <name> and row <index>\n\n"
    "EDIT_ROW(<index> <element>...): Replace a row at row <index>\n\n"
    "REMOVE_COLUMN(<index>): Removes a column at index <index>\n\n"
    "REMOVE_ROW(<index>): Removes a column at index <index>\n\n\n"
    "                == TYPES ==\n\n\n"
    "INT: A 32 bit signed integer\n\n"
    "BOOL: A boolean value of TRUE or FALSE\n\n"
    "STRING: Maps to a C++ std::string\n\n"
    "DOUBLE: A 64 bit double precision float\n\n";
};
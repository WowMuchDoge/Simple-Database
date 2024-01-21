#include <string>

std::string helpText = "\n                == COMMANDS ==\n\n"
"save <filename>: Save current database state to a text file\n"
"load <filename>: Load another database state\n"
"exit: Exits out of the program\n\n"
"            == DATABASE METHODS ==\n\n"
"ADD_COLUMN(<type> " + std::string(1, '"') + "<name>" + std::string(1, '"') + "): Adds a column with the specified name\n"
"ADD_ROW(<element>...): Add a row with n elements (amount and type of elements depend on the corresponding column)\n"
"GET_ELEMENT(" + std::string(1, '"') + "<name>" + std::string(1, '"') + " <index>): Prints the element at column <name> and row <index>\n"
"EDIT_ROW(<index> <element>...): Replace a row at row <index>\n"
"REMOVE_COLUMN(<index>): Removes a column at index <index>\n"
"REMOVE_ROW(<index>): Removes a column at index <index>\n\n"
"                == TYPES ==\n\n"
"INT: A 32 bit signed integer\n"
"BOOL: A boolean value of TRUE or FALSE\n"
"STRING: Maps to a C++ std::string\n"
"DOUBLE: A 64 bit double precision float\n\n";
#include <iostream>
#include <string>

#include "../include/TableHead.h"

void TableHead::addColumn(std::string type) {
    if (type == "INT") {
        columns.push_back(new ColumnHead<int>(""));
    } else {
        exit(1);
    }
}

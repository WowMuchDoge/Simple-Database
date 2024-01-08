#include <iostream>

#include "../include/ColumnHead.h"

int main() {
    ColumnHead<int> head("id");
    head.setPointer(new ColumnHead<std::string>("string"));

    std::cout << head.getPointer() << '\n';
}
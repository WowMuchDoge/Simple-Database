#pragma once

#include <string>

typedef struct {
    void* arr;
    int count;
} ColumnInfo;

class BaseColumn {
    public:
        virtual ~BaseColumn() = default;
        virtual std::string getTypeName() const = 0;
};
#pragma once

#include <string>

class BaseColumn {
    public:
        virtual ~BaseColumn() = default;
        virtual std::string getTypeName() const = 0;
};
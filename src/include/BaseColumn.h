#pragma once

#include <string>

class BaseColumn {
    public:
        virtual ~BaseColumn() = default;
        virtual std::string getTypeName() const = 0;
        virtual void addEmptyElement() = 0;
        virtual void clearColumn() = 0;
        virtual void printElement(int index) = 0;
        virtual void removeElement(int index) = 0;
};
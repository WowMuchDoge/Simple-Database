#pragma once

#include <iostream>

#include "BaseColumn.h"

template<class T>
class ColumnHead : public BaseColumn {
    private:
        std::vector<T> elements;

        std::string name;

        void* reallocate(size_t oldCapacity, size_t newCapacity, T* elements) {
            if (newCapacity > 0) {
                void* result = realloc(elements, newCapacity);
                if (result == NULL) exit(1);
                return result;
            }

            free(elements);
            return NULL;
        }

    public:
        ColumnHead(std::string nm) : next(NULL), elements(NULL), elementsCapacity(0), count(0), name(nm) {}

        void addElement(T element) {
            elements.push_back(element);
        }

        void editElement(T val, int index) {
            if (index >= count) exit(1);

            elements[index] = val;
        }

        void insertElement(T val, int index) {
            elements.insert(elements.begin() + index, val);
        }

        void clearColumn() {
            elements.clear();
        }

        void popElement() {
            elements[--count] = NULL;
        }

        T getElement(int index) {
            if (index >= count) exit(1);

            return elements[index];
        }

        std::string getTypeName() const {
            return typeid(T).name();
        }
};
#pragma once

#include <iostream>
#include <vector>

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
        ColumnHead(std::string nm) : name(nm) {}

        void addElement(T element) {
            elements.push_back(element);
        }

        void editElement(T val, int index) {
            if (index >= elements.size()) exit(1);

            elements[index] = val;
        }

        void insertElement(T val, int index) {
            elements.insert(elements.begin() + index, val);
        }

        void clearColumn() {
            elements.clear();
        }

        void popElement() {
            elements.pop_back();
        }

        T getElement(int index) {
            if (index >= elements.size()) exit(1);

            return elements[index];
        }

        std::vector<T> getElements() {
            return elements;
        }

        std::string getTypeName() const {
            return typeid(T).name();
        }

        void addEmptyElement() override {
            T emptyElement;
            elements.push_back(emptyElement);
        }
};
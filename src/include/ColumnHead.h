#pragma once

#include <iostream>

#include "BaseColumn.h"

#define GROW_ARRAY(type, oldCapacity, newCapacity, elements) \
    (type*)reallocate(oldCapacity * sizeof(type), newCapacity * sizeof(type), elements)

#define GROW_CAPACITY(capacity) \
    (capacity < 4 ? 4 : (capacity) * 2)

typedef struct {
    void* arr;
    int count;
} ColumnInfo;

template<class T>
class ColumnHead : public BaseColumn {
    private:
        T* elements;
        int elementsCapacity;
        int count;
        BaseColumn* next;

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
            if (elementsCapacity < count + 1) {
                int oldCapacity = elementsCapacity;
                elementsCapacity = GROW_CAPACITY(elementsCapacity);
                elements = GROW_ARRAY(T, oldCapacity, elementsCapacity, elements);
            }

            elements[count] = element;
            count++;
        }

        void editElement(T val, int index) {
            if (index >= count) exit(1);

            elements[index] = val;
        }

        void insertElement(T val, int index) {

            int oldCapacity = elementsCapacity;
            elementsCapacity = GROW_CAPACITY(elementsCapacity);
            elements = GROW_ARRAY(T, oldCapacity, elementsCapacity, elements);

            if (index >= count || index < 0) exit(1);

            for (int i = count; i > index; i--) {
                elements[i] = elements[i - 1];
            }

            elements[index] = val;

            count++;
        }

        void clearColumn() {
            free(elements);
            count = 0;
            elementsCapacity = 0;
            elements = NULL;
        }

        void popElement() {
            elements[--count] = NULL;
        }

        T getElement(int index) {
            if (index >= count) exit(1);

            return elements[index];
        }

        ColumnInfo getArray() {
            ColumnInfo info;
            info.arr = elements;
            info.count = count;
            return info;
        }

        void setPointer(BaseColumn* col) {
            next = col;
        }

        BaseColumn* getPointer() {
            return next;
        }

        std::string getTypeName() const {
            return typeid(T).name();
        }
};
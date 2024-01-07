#pragma once

#include <iostream>

#define GROW_ARRAY(type, oldCapacity, newCapacity, elements) \
    (type*)reallocate(oldCapacity * sizeof(type), newCapacity * sizeof(type), elements)

#define GROW_CAPACITY(capacity) \
    (capacity < 4 ? 4 : (capacity) * 2) 

template<class T>
class ColumnHead {
    private:
        T* elements;
        int elementsCapacity;
        int count;
        ColumnHead* next;

        void* reallocate(size_t oldCapacity, size_t newCapacity, T* elements) {
            if (newCapacity > 0) {
                return realloc(elements, newCapacity);
            }

            free(elements);
            return NULL;
        }

    public:
        ColumnHead() : next(NULL), elements(NULL), elementsCapacity(0), count(0) {}

        void addElement(T element) {
            if (elementsCapacity < count + 1) {
                int oldCapacity = elementsCapacity;
                elementsCapacity = GROW_CAPACITY(elementsCapacity);
                elements = GROW_ARRAY(T, oldCapacity, elementsCapacity, elements);
            }

            elements[count] = element;
            count++;
        }

        T getElement(int index) {
            return elements[index];
        }
};
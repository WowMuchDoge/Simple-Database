#pragma once

#include <iostream>
#include <vector>

#include "Constants.h"
#include "BaseColumn.h"

template<class T>
class ColumnHead : public BaseColumn {
    private:
        std::vector<T> elements;

        std::string name;

    public:
        ColumnHead(std::string nm) : name(nm) {}

        void addElement(T element) {
            elements.push_back(element);
        }

        void editElement(T val, int index) {
            if (index >= elements.size()) exit(OUT_OF_RANGE);

            elements[index] = val;
        }

        void insertElement(T val, int index) {
            elements.insert(elements.begin() + index, val);
        }

        void clearColumn() override {
            elements.clear();
        }

        void popElement() {
            elements.pop_back();
        }

        T getElement(int index) {

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

        void printElement(int index) override {
            std::cout << elements[index] << '\n';
        }

        void removeElement(int index) override {
            elements.erase(elements.begin() + index);
        }

        std::string getName() override {
            return name;
        }

        int rowLen() override {
            return elements.size();
        }

        void setName(std::string n) override {
            name = n;
        }
};
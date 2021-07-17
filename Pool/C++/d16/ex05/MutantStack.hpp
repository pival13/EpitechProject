/*
** EPITECH PROJECT, 2020
** cpp_d16_2019 [WSL: Ubuntu]
** File description:
** MutantStack
*/

#pragma once

#include <stack>

template<class T>
class MutantStack : public std::stack<T> {
    private:
        class MutantStackNode {
            public:
                MutantStackNode(const T &value) : value(value) { next = nullptr; }

                int size() const { int i = 0; MutantStackNode tmp = *this; for (; tmp != nullptr; i++) tmp = tmp->next; return i; }

                MutantStackNode *next;
                T value;
        };

    public:
        MutantStack() { node = nullptr; }
        ~MutantStack() { while (node != nullptr) { auto tmp = node->next; delete node; node = tmp; } }

        void push(const T &a) { std::stack<T>::push(a); auto *tmp = new MutantStackNode(a); tmp->next = node; node = tmp; }
        void pop() { std::stack<T>::pop(); auto *tmp = node->next; delete node; node = tmp; }

        class iterator {
            public:
                iterator() : begin(nullptr), curr(nullptr) {}
                iterator(MutantStackNode *node, int pos) : begin(node), curr(node) { for (int i = 0; curr && i != pos; i++) curr = curr->next; }
                iterator(const iterator &it) : begin(it.begin), curr(it.curr) {}
                ~iterator() {}
            
                iterator &operator=(const iterator &it) { begin = it.begin; curr = it.curr; return *this; }
                T &operator*() { return curr->value; }
                T operator*() const { return curr->value; }
                T &operator->() { return curr->value; }
                T operator->() const { return curr->value; }
                bool operator==(const iterator &it) { return curr == it.curr; }
                bool operator!=(const iterator &it) { return !this->operator==(it); }
                iterator &operator++() { if (curr) curr = curr->next; return *this; }
                iterator &operator++(int) { return ++(*this); }
                iterator &operator--() { 
                    MutantStackNode *tmp = begin; 
                    while (tmp && tmp->next != curr) tmp = tmp->next;
                    if (tmp) curr = tmp; 
                    return *this; }
                iterator &operator--(int) { return --(*this); }

                MutantStackNode *begin;
                MutantStackNode *curr;
        };

        iterator begin() { iterator it(node, 0); return it; }
        iterator end() { return iterator(node, std::stack<T>::size()); }

    private:
        MutantStackNode *node;
};

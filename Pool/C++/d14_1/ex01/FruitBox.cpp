/*
** EPITECH PROJECT, 2020
** cpp_d14m_2019 [WSL: Ubuntu]
** File description:
** FruitBox
*/

#include "FruitBox.hpp"

FruitBox::FruitBox(const int size)
: first(nullptr), size(size)
{
}

FruitBox::~FruitBox()
{
    while (first != nullptr) {
        FruitNode *tmp = first;
        first = first->next;
        delete tmp;
    }
}

int FruitBox::nbFruits() const
{
    FruitNode *tmp = first;
    int a = 0;

    while (tmp != nullptr) {
        a++;
        tmp = tmp->next;
    }
    return a;
}

bool FruitBox::putFruit(Fruit *f)
{
    if (f == nullptr || nbFruits() >= size)
        return false;
    for (FruitNode *tmp = first; tmp != nullptr; tmp = tmp->next)
        if (tmp->value == f)
            return false;
    
    FruitNode *fn = new FruitNode;
    fn->value = f;
    fn->next = nullptr;
    if (!first)
        first = fn;
    else {
        FruitNode *tmp = first;
        while (tmp->next != nullptr)
            tmp = tmp->next;
        tmp->next = fn;
    }
    return true;
}

Fruit *FruitBox::pickFruit()
{
    FruitNode *tmp;

    if (!first || first->value == nullptr)
        return nullptr;
    
    Fruit *f = first->value;
    tmp = first;
    first = first->next;
    delete tmp;
    return f;
}

FruitNode *FruitBox::head() const { return first; }

/*
** EPITECH PROJECT, 2020
** cpp_d14m_2019 [WSL: Ubuntu]
** File description:
** FruitBox
*/

#pragma once

#include "FruitNode.hpp"

class FruitBox {
    public:
        FruitBox(const int size);
        ~FruitBox();

        int nbFruits() const;
        bool putFruit(Fruit *f);
        Fruit *pickFruit();
        FruitNode *head() const;

    protected:
    private:
        FruitNode *first;
        const int size;
};

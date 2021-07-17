/*
** EPITECH PROJECT, 2020
** cpp_d14m_2019 [WSL: Ubuntu]
** File description:
** LittleHand
*/

#include "LittleHand.hpp"

void LittleHand::sortFruitBox(FruitBox &unsorted, FruitBox &lemon, FruitBox &banana, FruitBox &lime)
{
    int i = unsorted.nbFruits();

    for (; i != 0; i--) {
        Fruit *f = unsorted.pickFruit();
        if (dynamic_cast<Lime *>(f)) {
            if (!lime.putFruit(f))
                unsorted.putFruit(f);
        } else if (dynamic_cast<Banana *>(f)) {
            if (!banana.putFruit(f))
                unsorted.putFruit(f);
        } else if (dynamic_cast<Lemon *>(f)) {
            if (!lemon.putFruit(f))
                unsorted.putFruit(f);
        } else
            unsorted.putFruit(f);
    }
}

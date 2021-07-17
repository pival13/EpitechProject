/*
** EPITECH PROJECT, 2020
** cpp_rush2_2019 [WSL: Ubuntu]
** File description:
** TableRand
*/

#include "TableRand.hpp"

TableRand::TableRand()
{
    int nb = random() % 10;
    int nb2;
    Object *obj;

    for (int i = 0; i != nb; i++) {
        nb2 = random() % 4;
        if (nb2 == 0) {
            obj = new Box();
            this->addBox(obj);
        } else if (nb2 == 1) {
            obj = new GiftPaper();
            this->addPaper(obj);
        } else {
            if (nb2 == 2)
                obj = new LittlePony("Twilight Sparkle");
            else
                obj = new Teddy("Winny L'Ourson");
            this->addToy(obj);
        }
    }
}

TableRand::~TableRand()
{
}
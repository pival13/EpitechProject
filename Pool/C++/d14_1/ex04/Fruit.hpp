/*
** EPITECH PROJECT, 2020
** cpp_d14m_2019 [WSL: Ubuntu]
** File description:
** Fruit
*/

#pragma once

#include <iostream>

class Fruit {
    public:
        Fruit(const Fruit &);
        virtual ~Fruit() {}

        virtual int getVitamins() const;
        virtual std::string getName() const;

        Fruit &operator=(const Fruit &);

        int _vitamins;

    protected:
        Fruit() = default;

        std::string _name;

    private:
};

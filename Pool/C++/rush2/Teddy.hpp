/*
** EPITECH PROJECT, 2020
** rush2 [WSL: Ubuntu]
** File description:
** Teddy
*/

#pragma once

#include "Toy.hpp"

class Teddy : virtual public Toy {
    public:
        Teddy(const std::string &title);
        ~Teddy();

        void isTaken() const;

    protected:
    private:
};

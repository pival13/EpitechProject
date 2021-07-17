/*
** EPITECH PROJECT, 2020
** cpp_d10_2019 [WSL: Ubuntu]
** File description:
** Ice
*/

#pragma once

#include "AMateria.hpp"

class Ice : public AMateria {
    public:
        Ice();
        ~Ice();

        AMateria *clone() const;
        void use(ICharacter &target);

    protected:
    private:
};

/*
** EPITECH PROJECT, 2020
** cpp_d10_2019 [WSL: Ubuntu]
** File description:
** Cure
*/

#pragma once

#include "AMateria.hpp"

class Cure : public AMateria {
    public:
        Cure();
        ~Cure();

        AMateria *clone() const;
        void use(ICharacter &);

    protected:
    private:
};

/*
** EPITECH PROJECT, 2020
** cpp_d10_2019 [WSL: Ubuntu]
** File description:
** Character
*/

#pragma once

#include "ICharacter.hpp"
#include <array>
#include <iostream>
#include "AMateria.hpp"

class Character : public ICharacter {
    public:
        Character(const std::string &name);
        Character(const Character &c);
        ~Character();

        const std::string &getName() const;
        AMateria *getMateria(int) const;

        void equip(AMateria* m);
        void unequip(int idx);
        void use(int idx, ICharacter& target);

        Character &operator=(const Character &);

    protected:
    private:
        const std::string _name;
        std::array<AMateria *, 4> _materia;
};

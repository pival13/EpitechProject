/*
** EPITECH PROJECT, 2020
** cpp_d10_2019 [WSL: Ubuntu]
** File description:
** AMateria
*/

#pragma once

#include <iostream>
#include "ICharacter.hpp"

class AMateria {
    public:
        AMateria(const std::string &type);
        AMateria(const AMateria &);
        virtual ~AMateria();

        const std::string &getType() const;
        unsigned int getXP() const;

        virtual AMateria *clone() const = 0;
        virtual void use(ICharacter &target);

        AMateria &operator=(AMateria &);

    protected:
        const std::string _type;
        unsigned int _xp;
 
    private:
};

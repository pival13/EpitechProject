/*
** EPITECH PROJECT, 2020
** cpp_d10_2019 [WSL: Ubuntu]
** File description:
** MateriaSource
*/

#pragma once

#include "IMateriaSource.hpp"
#include <array>
#include <map>

class MateriaSource : public IMateriaSource {
    public:
        MateriaSource();
        ~MateriaSource();

        AMateria * createMateria(std::string const & type);
        void learnMateria(AMateria *);

    protected:
    private:
        //std::array<AMateria *, 4> _materia;
        std::map<std::string, AMateria *> _template;
};

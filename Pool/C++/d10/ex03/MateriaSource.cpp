/*
** EPITECH PROJECT, 2020
** cpp_d10_2019 [WSL: Ubuntu]
** File description:
** MateriaSource
*/

#include "MateriaSource.hpp"

MateriaSource::MateriaSource()
: _template()
{
}

MateriaSource::~MateriaSource()
{
}

AMateria * MateriaSource::createMateria(std::string const &type)
{
    if (!_template.count(type))
        return nullptr;
    return _template[type]->clone();
}

void MateriaSource::learnMateria(AMateria *materia)
{
    if (materia == nullptr || _template.size() >= 4 || _template.count(materia->getType()))
        return;
    _template[materia->getType()] = materia;
}
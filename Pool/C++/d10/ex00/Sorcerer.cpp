/*
** EPITECH PROJECT, 2020
** cpp_d10_2019 [WSL: Ubuntu]
** File description:
** Sorcerer
*/

#include "Sorcerer.hpp"

Sorcerer::Sorcerer(const std::string &name, const std::string &title)
: name(name), title(title)
{
    std::cout << name << ", " << title << ", is born!" << std::endl;
}

Sorcerer::Sorcerer()
{
}

Sorcerer::~Sorcerer()
{
    std::cout << name << ", " << title << ", is dead. Consequences will never be the same!" << std::endl;
}

const std::string Sorcerer::getName() const { return name; }
const std::string Sorcerer::getTitle() const { return title; }

void Sorcerer::polymorph(const Victim &victim) const
{
    victim.getPolymorphed();
}

std::ostream &operator<<(std::ostream &os, const Sorcerer &s)
{
    os << "I am " << s.getName() << ", " << s.getTitle() << ", and I like ponies!\n";
    return os;
}
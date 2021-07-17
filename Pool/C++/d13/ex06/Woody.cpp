/*
** EPITECH PROJECT, 2020
** cpp_d13_2019 [WSL: Ubuntu]
** File description:
** Woody
*/

#include "Woody.hpp"

Woody::Woody(const std::string &name, const std::string &file)
: Toy(Toy::WOODY, name, file)
{
}

Woody::~Woody()
{
}

bool Woody::speak(const std::string &str)
{
    std::cout << "WOODY: ";
    return Toy::speak(str);
}
/*
** EPITECH PROJECT, 2020
** cpp_d13_2019 [WSL: Ubuntu]
** File description:
** Buzz
*/

#include "Buzz.hpp"

Buzz::Buzz(const std::string &name, const std::string &file)
: Toy(Toy::BUZZ, name, file)
{
}

Buzz::~Buzz()
{
}

bool Buzz::speak(const std::string &str)
{
    std::cout << "BUZZ: ";
    return Toy::speak(str);
}

bool Buzz::speak_es(const std::string &str)
{
    std::cout << "BUZZ: " << this->getName() << " senorita \"" << str << "\" senorita" << std::endl;
    return true;
}
/*
** EPITECH PROJECT, 2020
** cpp_d13_2019 [WSL: Ubuntu]
** File description:
** Toy
*/

#include "Toy.hpp"

Toy::Toy()
: _type(BASIC_TOY), _name("toy"), _pict()
{
}

Toy::Toy(const Toy &t)
: _type(t.getType()), _name(t.getName()), _pict()
{
    _pict.data = t.getAscii();
}

Toy::Toy(const ToyType type, const std::string &name, const std::string &file)
: _type(type), _name(name), _pict(file)
{
}

Toy::~Toy()
{
}

Toy &Toy::operator=(const Toy &t)
{
    _type = t.getType();
    _name = t.getName();
    _pict.data = t.getAscii();
    return *this;
}

Toy::ToyType Toy::getType() const { return _type; }
std::string Toy::getName() const { return _name; }
std::string Toy::getAscii() const { return _pict.data; }
void Toy::setName(const std::string &name) { _name = name; }
bool Toy::setAscii(const std::string &file) { return _pict.getPictureFromFile(file); }
        
Toy &Toy::operator<<(const std::string &str)
{
    _pict.data = str;
    return *this;
}

void Toy::speak(const std::string &str) const
{
    std::cout << _name << " \"" << str << "\"" << std::endl;
}

bool Toy::speak_es(const std::string &) const
{
    return false;
}

std::ostream &operator<<(std::ostream &os, const Toy &t)
{
    os << t.getName() << "\n" << t.getAscii() << std::endl;
    return os;
}
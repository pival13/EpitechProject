/*
** EPITECH PROJECT, 2020
** cpp_d13_2019 [WSL: Ubuntu]
** File description:
** Toy
*/

#include "Toy.hpp"

Toy::Toy()
: _type(BASIC_TOY), _name("toy"), _pict(), _error(Error::UNKNOWN)
{
}

Toy::Toy(const Toy &t)
: _type(t.getType()), _name(t.getName()), _pict(), _error(t.getLastError().type)
{
    _pict.data = t.getAscii();
}

Toy::Toy(const ToyType type, const std::string &name, const std::string &file)
: _type(type), _name(name), _pict(file), _error(Error::UNKNOWN)
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
    _error.type = t.getLastError().type;
    return *this;
}

Toy::ToyType Toy::getType() const { return _type; }
std::string Toy::getName() const { return _name; }
std::string Toy::getAscii() const { return _pict.data; }
Toy::Error Toy::getLastError() const { return _error; }
void Toy::setName(const std::string &name) { _name = name; }
bool Toy::setAscii(const std::string &file)
{
    bool ret = _pict.getPictureFromFile(file);
    if (!ret)
        _error = Error(Error::PICTURE);
    return ret; 
}
        
Toy &Toy::operator<<(const std::string &str)
{
    _pict.data = str;
    return *this;
}

void Toy::speak(const std::string &str) const
{
    std::cout << _name << " \"" << str << "\"" << std::endl;
}

bool Toy::speak_es(const std::string &)
{
    _error = Error(Error::SPEAK);
    return false;
}

Toy::Error::Error(ErrorType err)
: type(err)
{
}

Toy::Error::~Error()
{
}

std::string Toy::Error::what() const
{
    if (type == PICTURE)
        return "bad new illustration";
    else if (type == SPEAK)
        return "wrong mode";
    else
        return "";
}

std::string Toy::Error::where() const
{
    if (type == PICTURE)
        return "setAscii";
    else if (type == SPEAK)
        return "speak_es";
    else
        return "";
}

std::ostream &operator<<(std::ostream &os, const Toy &t)
{
    os << t.getName() << "\n" << t.getAscii() << std::endl;
    return os;
}
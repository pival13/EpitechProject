/*
** EPITECH PROJECT, 2020
** cpp_d08_2019 [WSL: Ubuntu]
** File description:
** Supply
*/

#include "Supply.hpp"

Supply::Supply(Types type, size_t amount, Droid **droids)
: Type(type), Amount(amount), Wrecks(droids), pos(0)
{
}

Supply::~Supply()
{
    if (Wrecks)
        for (size_t i = 0; i != Amount; i++)
            delete(Wrecks[i]);
}

std::ostream &operator<<(std::ostream &os, Supply &s)
{
    os << "Supply : " << s.Amount << ", ";
    if (s.Type == Supply::Types::Iron)
        os << "Iron";
    else if (s.Type == Supply::Types::Silicon)
        os << "Silicon";
    else if (s.Type == Supply::Types::Wreck) {
        os << "Wreck";
    for (size_t i = 0; i != s.Amount; i++)
        os << "\n" << *s.Wrecks[i];
    }
    return os;
}

Supply &Supply::operator!()
{
    if (Type == Types::Wreck)
        for (size_t i = 0; i != Amount; i++)
            if (Wrecks[i])
                delete(Wrecks[i]);
    Amount = 0;
    Wrecks = nullptr;
    return *this;
}

bool Supply::operator==(Supply const &s) const
{
    return Type == s.Type;
}

bool Supply::operator!=(Supply const &s) const
{
    return !operator==(s);
}

Supply &Supply::operator--()
{
    pos = (pos - 1 + Amount) % Amount;
    return *this;
}

Supply &Supply::operator++()
{
    pos = (pos + 1) % Amount;
    return *this;
}

Supply &Supply::operator--(int a)
{
    pos = (pos - a + Amount) % Amount;
    return *this;
}

Supply &Supply::operator++(int a)
{
    pos = (pos + a) % Amount;
    return *this;
}

Droid *&Supply::operator*()
{
    return Wrecks[pos];
}

Droid *Supply::operator*() const
{
    return Wrecks[pos];
}

Droid *&Supply::operator->()
{
    return Wrecks[pos];
}

Supply::operator size_t() const
{
    return Amount;
}
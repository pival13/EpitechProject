/*
** EPITECH PROJECT, 2020
** cpp_d08_2019 [WSL: Ubuntu]
** File description:
** DroidMemory
*/

#include "DroidMemory.hpp"

DroidMemory::DroidMemory()
: Exp(0), Fingerprint(random())
{
}

DroidMemory::~DroidMemory()
{
}

size_t DroidMemory::getFingerprint() const
{
    return Fingerprint;
}

size_t DroidMemory::getExp() const
{
    return Exp;
}

void DroidMemory::setFingerprint(size_t f)
{
    Fingerprint = f;
}

void DroidMemory::setExp(size_t exp)
{
    Exp = exp;
}

DroidMemory &DroidMemory::operator<<(DroidMemory const &d)
{
    this->Exp += d.getExp();
    this->Fingerprint ^= d.getFingerprint();

    return *this;
}

DroidMemory &DroidMemory::operator>>(DroidMemory &d) const
{
    return d.operator<<(*this);
}

DroidMemory &DroidMemory::operator+=(DroidMemory const &d)
{
    return operator<<(d);
}

DroidMemory &DroidMemory::operator+=(size_t const nb)
{
    this->Exp += nb;
    this->Fingerprint ^= nb;
    return *this;
}

DroidMemory operator+(DroidMemory const &d1, DroidMemory const &d2)
{
    DroidMemory d;
    d.setExp(d1.getExp() + d2.getExp());
    d.setFingerprint(d1.getFingerprint() ^ d2.getFingerprint());
    return d;
}

DroidMemory operator+(DroidMemory const &d1, size_t const &nb)
{
    DroidMemory d;
    d.setExp(d1.getExp() + nb);
    d.setFingerprint(d1.getFingerprint() ^ nb);
    return d;
}

bool DroidMemory::operator==(DroidMemory const& mem) const
{
    return Exp == mem.getExp() && Fingerprint == mem.getFingerprint(); 
}

bool DroidMemory::operator!=(DroidMemory const& mem) const { return !operator==(mem); }

bool DroidMemory::operator>(DroidMemory const& mem) const { return Exp > mem.getExp(); }

bool DroidMemory::operator>(size_t const mem) const { return Exp > mem; }

bool DroidMemory::operator<(DroidMemory const& mem) const { return Exp < mem.getExp(); }

bool DroidMemory::operator<(size_t const mem) const { return Exp < mem; }

bool DroidMemory::operator>=(DroidMemory const& mem) const { return Exp >= mem.getExp(); }

bool DroidMemory::operator>=(size_t const mem) const { return Exp >= mem; }

bool DroidMemory::operator<=(DroidMemory const& mem) const { return Exp <= mem.getExp(); }

bool DroidMemory::operator<=(size_t const mem) const { return Exp <= mem; }

std::ostream &operator<<(std::ostream &os, DroidMemory const &d)
{
    os << "DroidMemory '" << d.getFingerprint() << "', " << d.getExp();
    return os;
}
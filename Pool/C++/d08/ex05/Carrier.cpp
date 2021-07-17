/*
** EPITECH PROJECT, 2020
** cpp_d08_2019 [WSL: Ubuntu]
** File description:
** Carrier
*/

#include "Carrier.hpp"

Carrier::Carrier(const std::string &serial)
: Id(serial), Energy(300), Attack(100), Toughness(90), Speed(0)
{
    for (int i = 0; i != 5; i++)
        Droids[i] = nullptr;
}

Carrier::~Carrier()
{
    for (int i = 0; i != 5; i++)
        if (Droids[i])
            delete(Droids[i]);
}

void Carrier::setId(const std::string &serial) { Id = serial; }

void Carrier::setEnergy(const size_t energy) 
{ 
    Energy = energy; 
    if (Energy > 600) 
        Energy = 600; 
}

void Carrier::setSpeed(const size_t spped) { Speed = spped; }

std::string Carrier::getId() const { return Id; }

size_t Carrier::getEnergy() const { return Energy; }

size_t Carrier::getAttack() const { return Attack; }

size_t Carrier::getToughness() const { return Toughness; }

size_t Carrier::getSpeed() const { return Speed; }

Droid *&Carrier::operator[](const size_t pos)
{
    return Droids[pos];
}

Droid *Carrier::operator[](const size_t pos) const
{
    return Droids[pos];
}

Carrier &Carrier::operator<<(size_t &energy)
{
    if (Energy == 600)
        return *this;
    if (Energy + energy <= 600) {
        Energy += energy;
        energy = 0;
    } else {
        energy -= 600 - Energy;
        Energy = 600;
    }
    return *this;
}

Carrier &Carrier::operator<<(Droid *&droid)
{
    if (droid == nullptr)
        return *this;
    if (Speed == 0)
        Speed = 100;
    if (!Droids[0])
        Droids[0] = droid;
    else if (!Droids[1])
        Droids[1] = droid;
    else if (!Droids[2])
        Droids[2] = droid;
    else if (!Droids[3])
        Droids[3] = droid;
    else if (!Droids[4])
        Droids[4] = droid;
    else 
        return *this;
    Speed -= 10;
    droid = nullptr;
    return *this;
}

Carrier &Carrier::operator>>(Droid *&droid)
{
    Droid **d = nullptr;

    for (int i = 0; i != 5; i++)
    if (Droids[0])
        d = &Droids[0];
    else if (Droids[1])
        d = &Droids[1];
    else if (Droids[2])
        d = &Droids[2];
    else if (Droids[3])
        d = &Droids[3];
    else if (Droids[4])
        d = &Droids[4];
    else 
        return *this;
    droid = *d;
    *d = nullptr;
    Speed += 10;
    if (Speed == 100)
        Speed = 0;
    return *this;
}

bool Carrier::operator()(const int x, const int y)
{
    size_t nbDroid = (Droids[0] != nullptr) +
                     (Droids[1] != nullptr) +
                     (Droids[2] != nullptr) +
                     (Droids[3] != nullptr) +
                     (Droids[4] != nullptr); 
    size_t cost = (ABS(x) + ABS(y)) * (10 + nbDroid);

    if (cost > Energy || Speed == 0)
        return false;
    Energy -= cost;
    return true;
}

Carrier &Carrier::operator~()
{
    Speed = 0;

    for (int i = 0; i != 5; i++)
        if (Droids[i]) {
            if (Speed == 0)
                Speed = 100;
            Speed -= 10;
        }
    return *this;
}

std::ostream &operator<<(std::ostream &os, Carrier const &c)
{
    os << "Carrier '" << c.getId() << "' Droid(s) on-board:\n";
    for (int i = 0; i != 5; i++)
        if (c[i])
            os << "[" << i << "] : " << *c[i] << std::endl;
        else
            os << "[" << i << "] : Free\n";
    os << "Speed " << c.getSpeed() << ", Energy " << c.getEnergy();
    return os;
}
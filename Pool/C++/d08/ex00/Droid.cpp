/*
** EPITECH PROJECT, 2020
** cpp_d08_2019 [WSL: Ubuntu]
** File description:
** Droid
*/

#include "Droid.hpp"

Droid::Droid(const std::string &serial)
: Id(serial), Energy(50), Attack(25), Toughness(15)
{
    Status = new std::string("Standing by");
    std::cout << "Droid '" << serial << "' Activated\n";
}

Droid::Droid(const Droid &d1)
: Id(d1.getId()), Energy(d1.getEnergy()), Attack(d1.getAttack()), Toughness(d1.getToughness()), Status(new std::string(*d1.getStatus()))
{
    std::cout << "Droid '" << Id << "' Activated, Memory Dumped\n";
}

Droid::~Droid()
{
    std::cout << "Droid '" << Id << "' Destroyed\n";
    delete(Status);
}

void Droid::setId(const std::string &serial)
{
    Id = serial;
}

void Droid::setEnergy(size_t energy)
{
    Energy = energy;
    if (Energy > 100)
        Energy = 100;
}

void Droid::setStatus(std::string *status)
{
    if (status == nullptr)
        return;
    delete(Status);
    Status = status;
}

std::string Droid::getId() const
{
    return Id;
}

size_t Droid::getEnergy() const
{
    return Energy;
}

size_t Droid::getAttack() const
{
    return Attack;
}

size_t Droid::getToughness() const
{
    return Toughness;
}

std::string *Droid::getStatus() const
{
    return Status;
}


bool Droid::operator==(Droid const &d2) const
{
    return (Attack == d2.getAttack() &&
            Energy == d2.getEnergy() &&
            Id == d2.getId() &&
            ((Status && d2.getStatus() && 
                *Status == *d2.getStatus()) || 
                (!Status && !d2.getStatus())) &&
            Toughness == d2.getToughness());
}

bool Droid::operator!=(Droid const &d2) const
{
    return !(operator==(d2));
}

void Droid::operator<<(size_t &energy)
{
    if (Energy == 100)
        return;
    if (Energy + energy <= 100) {
        Energy += energy;
        energy = 0;
    } else {
        energy -= 100 - Energy;
        Energy = 100;
    }
}

std::ostream &operator<<(std::ostream &os, Droid const &d1)
{
    os << "Droid '" << d1.getId() << "', " << (d1.getStatus() ? *d1.getStatus() : "") << ", " << d1.getEnergy();
    return os;
}

Droid &Droid::operator=(Droid const &d1)
{
    Id = d1.getId();
    Energy = d1.getEnergy();
    delete(Status);
    Status = new std::string(*d1.getStatus());
    return *this;
}
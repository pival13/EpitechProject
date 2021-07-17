/*
** EPITECH PROJECT, 2020
** cpp_d08_2019 [WSL: Ubuntu]
** File description:
** DroidFactory
*/

#include "DroidFactory.hpp"

DroidFactory::DroidFactory(const size_t ratio)
: Iron(0), Silicone(0), Ratio(ratio), Exp(0)
{

}

DroidFactory::DroidFactory(const DroidFactory &factory)
: Iron(factory.getIron()), Silicone(factory.getSilicon()), Ratio(factory.getRatio()), Exp(factory.getExp())
{
}

DroidFactory::~DroidFactory()
{
}

size_t DroidFactory::getIron() const { return Iron; }

size_t DroidFactory::getSilicon() const { return Silicone; }

size_t DroidFactory::getRatio() const { return Ratio; }

size_t DroidFactory::getExp() const { return Exp; }

DroidFactory &DroidFactory::operator<<(Supply &s)
{
    if (s.Type == Supply::Types::Iron) {
        Iron += s.Amount;
        !s;
    } else if (s.Type == Supply::Types::Silicon) {
        Silicone += s.Amount;
        !s;
    } else {
        for (size_t i = 0; i != s.Amount; i++, ++s) {
            Silicone += 30;
            Iron += 80;
            if (s->BattleData->getExp() > Exp)
                Exp += (s->BattleData->getExp() - Exp) / Ratio;
        }
        !s;
    }
    return *this;
}

Droid *DroidFactory::operator>>(Droid *&droid) 
{
    Droid *d;

    if (Silicone < 50 && Iron < 100) {
        droid = nullptr;
        return nullptr;
    }
    Silicone -= 50;
    Iron -= 100;
    d = new Droid("");
    *d->BattleData += Exp - Exp/Ratio;
    droid = d;
    return d;
}

DroidFactory &operator>>(Supply &s, DroidFactory &d)
{
    d << s;
    return d;
}

DroidFactory &DroidFactory::operator++()
{
    Ratio++;
    return *this;
}

DroidFactory &DroidFactory::operator--()
{
    Ratio--;
    return *this;
}

DroidFactory &DroidFactory::operator++(int a)
{
    Ratio += a;
    return *this;
}

DroidFactory &DroidFactory::operator--(int a)
{
    Ratio -= a;
    return *this;
}

std::ostream &operator<<(std::ostream &os, DroidFactory &d)
{
    os << "DroidFactory status report :\n" << "Iron : " << d.getIron();
    os << "\nSilicon : " << d.getSilicon() << "\nExp : " << d.getExp();
    os << "\nEnd of status report.";
    return os;
}
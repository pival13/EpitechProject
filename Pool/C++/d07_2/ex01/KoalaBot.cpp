/*
** EPITECH PROJECT, 2020
** cpp_d07a_2019 [WSL: Ubuntu]
** File description:
** KoalaBot
*/

#include "KoalaBot.hpp"

KoalaBot::KoalaBot(const std::string &name) 
: string(name)
{
    /*_arm = new Arms();
    _leg = new Legs();
    _head = new Head();*/
    //informations();
}

KoalaBot::~KoalaBot()
{
}

void KoalaBot::setParts(const Arms &part)
{
    _arm._functional = part._functional;
    _arm._name = part._name;
}

void KoalaBot::setParts(const Legs &part)
{
    _leg._functional = part._functional;
    _leg._name = part._name;
}

void KoalaBot::setParts(const Head &part)
{
    _head._functional = part._functional;
    _head._name = part._name;
}

void KoalaBot::swapParts(Arms &part)
{
    part._functional = _arm._functional;
    part._name = _arm._name;
}

void KoalaBot::swapParts(Legs &part)
{
    part._functional = _leg._functional;
    part._name = _leg._name;
}

void KoalaBot::swapParts(Head &part)
{
    part._functional = _head._functional;
    part._name = _head._name;
}

bool KoalaBot::status() const
{
    if (_arm.isFunctional() && _leg.isFunctional() && _head.isFunctional())
        return true;
    return false;
}

void KoalaBot::informations() const
{
    std::cout << "[KoalaBot] " << string << std::endl;
    _arm.informations();
    _leg.informations();
    _head.informations();
}

int main ()
{
KoalaBot kb ;
Head h("Head");
kb.setParts(h);
std :: cout << std :: boolalpha << kb . status () << std :: endl ;
kb . informations () ;
return 0;
}

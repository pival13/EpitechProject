/*
** EPITECH PROJECT, 2020
** cpp_d07a_2019 [WSL: Ubuntu]
** File description:
** KreogCom
*/

#include "KreogCom.hpp"

KreogCom::KreogCom(int x, int y, int serial) : m_serial(serial), next(nullptr)
{
    pos[0] = x;
    pos[1] = y;
    std::cout << "KreogCom " << serial << " initialized\n";
}

KreogCom::~KreogCom()
{
    std::cout << "KreogCom " << m_serial << " shutting down\n";
}

void KreogCom::addCom(int x, int y, int serial)
{
    if (next) {
        KreogCom *tmp = next;
        next = new KreogCom(x, y, serial);
        next->next = tmp;
    } else
        next = new KreogCom(x, y, serial);
}

void KreogCom::removeCom()
{
    if (next) {
        KreogCom *tmp = next;
        next = next->next;
        delete(tmp);
    }
}

KreogCom *KreogCom::getCom()
{
    return next;
}

void KreogCom::ping() const
{
    std::cout << "KreogCom " << m_serial << " currently at " << pos[0] << " " << pos[1] << std::endl;
}

void KreogCom::locateSquad() const
{
    KreogCom *tmp = next;
    while (tmp) {
        tmp->ping();
        tmp = tmp->next;
    }
    ping();
}
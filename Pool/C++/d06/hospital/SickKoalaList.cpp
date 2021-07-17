/*
** EPITECH PROJECT, 2020
** cpp_d06_2019 [WSL: Ubuntu]
** File description:
** SickKoalaList
*/

#include "SickKoalaList.hpp"
#include <iostream>

SickKoalaList::SickKoalaList(SickKoala *value) : value(value), next(nullptr)
{
}

SickKoalaList::~SickKoalaList()
{
}

bool SickKoalaList::isEnd()
{
    if (next == nullptr)
        return true;
    return false;
}

void SickKoalaList::append(SickKoalaList *node)
{
    SickKoalaList *tmp = this;
    while (tmp->next != nullptr)
        tmp = tmp->next;
    tmp->next = node;
}

bool SickKoalaList::contain(SickKoalaList *node)
{
    SickKoalaList *tmp = this;

    while (tmp != nullptr)
        if (tmp == node)
            return true;
        else
            tmp = tmp->next;
    return false;
}

SickKoala *SickKoalaList::getFromName(std::string name)
{
    SickKoalaList *tmp = this;
    while (tmp != nullptr && (!tmp->value || tmp->value->getName() != name))
        tmp = tmp->next;
    if (tmp == nullptr)
        return nullptr;
    return tmp->value;
}

SickKoalaList *SickKoalaList::remove(SickKoalaList *node)
{
    SickKoalaList *tmp = this;
    SickKoalaList *tmp2 = this;

    if (this == node) {
        tmp = this->next;
        this->next = nullptr;
        return tmp;
    } else {
        while (tmp->next != nullptr && tmp->next != node)
            tmp = tmp->next;
        tmp2 = tmp->next;
        tmp->next = tmp->next->next;
        tmp2->next = nullptr;
    }
    return this;
}

SickKoalaList *SickKoalaList::removeFromName(std::string name)
{
    SickKoalaList *tmp = this;
    while (!tmp->value || tmp->value->getName() != name)
        tmp = tmp->next;
    return remove(tmp);
}

SickKoala *SickKoalaList::getContent()
{
    return this->value;
}

SickKoalaList *SickKoalaList::getNext()
{
    return this->next;
}

void SickKoalaList::dump()
{
    SickKoalaList *tmp = this;

    std::cout << "Patients: ";
    while (tmp != nullptr) {
        if (!tmp->value)
            std::cout << "nullptr";
        else
            std::cout << tmp->value->getName();
        tmp = tmp->next;
        if (tmp != nullptr)
            std::cout << ", ";
    }
    std::cout << "." << std::endl;
}
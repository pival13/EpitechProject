/*
** EPITECH PROJECT, 2020
** cpp_d06_2019 [WSL: Ubuntu]
** File description:
** KoalaNurseList
*/

#include "KoalaNurseList.hpp"
#include <iostream>

KoalaNurseList::KoalaNurseList(KoalaNurse *value) : value(value), next(nullptr)
{
}

KoalaNurseList::~KoalaNurseList()
{
}

bool KoalaNurseList::isEnd()
{
    if (next == nullptr)
        return true;
    return false;
}

void KoalaNurseList::append(KoalaNurseList *node)
{
    KoalaNurseList *tmp = this;
    while (tmp->next != nullptr)
        tmp = tmp->next;
    tmp->next = node;
}

bool KoalaNurseList::contain(KoalaNurseList *node)
{
    KoalaNurseList *tmp = this;

    while (tmp != nullptr)
        if (tmp == node)
            return true;
        else
            tmp = tmp->next;
    return false;
}

size_t KoalaNurseList::size()
{
    KoalaNurseList *tmp = this;
    size_t i = 0;

    for (; tmp != nullptr; i++)
        tmp = tmp->next;
    return i;
}

KoalaNurse *KoalaNurseList::getFromID(int id)
{
    KoalaNurseList *tmp = this;
    while (tmp != nullptr && (!tmp->value || tmp->value->getID() != id))
        tmp = tmp->next;
    if (tmp == nullptr)
        return nullptr;
    return tmp->value;
}

KoalaNurseList *KoalaNurseList::remove(KoalaNurseList *node)
{
    KoalaNurseList *tmp = this;
    KoalaNurseList *tmp2 = this;

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

KoalaNurseList *KoalaNurseList::removeFromID(int id)
{
    KoalaNurseList *tmp = this;
    while (!tmp->value || tmp->value->getID() != id)
        tmp = tmp->next;
    return remove(tmp);
}

KoalaNurse *KoalaNurseList::getContent()
{
    return this->value;
}

KoalaNurse *KoalaNurseList::getContent(int nb)
{
    KoalaNurseList *tmp = this;

    for (int i = 0; i != nb; i++)
        tmp = tmp->next;
    return tmp->value;
}

void KoalaNurseList::dump()
{
    KoalaNurseList *tmp = this;

    std::cout << "Nurses: ";
    while (tmp != nullptr) {
        if (!tmp->value)
            std::cout << "nullptr";
        else
            std::cout << tmp->value->getID();
        tmp = tmp->next;
        if (tmp != nullptr)
            std::cout << ", ";
    }
    std::cout << "." << std::endl;
}
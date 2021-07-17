/*
** EPITECH PROJECT, 2020
** cpp_d06_2019 [WSL: Ubuntu]
** File description:
** KoalaDoctorList
*/

#include "KoalaDoctorList.hpp"
#include <iostream>

KoalaDoctorList::KoalaDoctorList(KoalaDoctor *value) : value(value), next(nullptr)
{
}

KoalaDoctorList::~KoalaDoctorList()
{
}

bool KoalaDoctorList::isEnd()
{
    if (next == nullptr)
        return true;
    return false;
}

void KoalaDoctorList::append(KoalaDoctorList *node)
{
    KoalaDoctorList *tmp = this;
    while (tmp->next != nullptr)
        tmp = tmp->next;
    tmp->next = node;
}

bool KoalaDoctorList::contain(KoalaDoctorList *node)
{
    KoalaDoctorList *tmp = this;

    while (tmp != nullptr)
        if (tmp == node)
            return true;
        else
            tmp = tmp->next;
    return false;
}

size_t KoalaDoctorList::size()
{
    KoalaDoctorList *tmp = this;
    size_t i = 0;

    for (; tmp != nullptr; i++)
        tmp = tmp->next;
    return i;
}

KoalaDoctor *KoalaDoctorList::getFromName(std::string name)
{
    KoalaDoctorList *tmp = this;
    while (tmp != nullptr && (!tmp->value || tmp->value->getName() != name))
        tmp = tmp->next;
    if (tmp == nullptr)
        return nullptr;
    return tmp->value;
}

KoalaDoctorList *KoalaDoctorList::remove(KoalaDoctorList *node)
{
    KoalaDoctorList *tmp = this;
    KoalaDoctorList *tmp2 = this;

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

KoalaDoctorList *KoalaDoctorList::removeFromName(std::string name)
{
    KoalaDoctorList *tmp = this;
    while (!tmp->value || tmp->value->getName() != name)
        tmp = tmp->next;
    return remove(tmp);
}

KoalaDoctor *KoalaDoctorList::getContent()
{
    return this->value;
}

KoalaDoctor *KoalaDoctorList::getContent(int nb)
{
    KoalaDoctorList *tmp = this;

    for (int i = 0; i != nb; i++)
        tmp = tmp->next;
    return tmp->value;
}

void KoalaDoctorList::dump()
{
    KoalaDoctorList *tmp = this;

    std::cout << "Doctors: ";
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
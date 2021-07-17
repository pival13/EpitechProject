/*
** EPITECH PROJECT, 2020
** cpp_day06_2019 [WSL: Ubuntu]
** File description:
** KoalaDoctor
*/

#ifndef KOALADOCTOR_H
#define KOALADOCTOR_H

#include <string>
#include "SickKoala.hpp"

struct KoalaDoctor {
    KoalaDoctor(std::string);
    ~KoalaDoctor();

    void diagnose(SickKoala *);
    void timeCheck();
    std::string getName();

    std::string name;
    bool isWorking;
};

#endif
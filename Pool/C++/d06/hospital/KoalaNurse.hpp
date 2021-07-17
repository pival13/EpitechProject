/*
** EPITECH PROJECT, 2020
** cpp_day06_2019 [WSL: Ubuntu]
** File description:
** KoalaNurse
*/

#ifndef KOALANURSE_H
#define KOALANURSE_H

#include "SickKoala.hpp"
#include <string>

struct KoalaNurse {
    KoalaNurse(int);
    ~KoalaNurse();

    void giveDrug(std::string, SickKoala *);
    std::string readReport(std::string);
    void timeCheck();
    int getID();

    int ID;
    bool isWorking;
};

#endif
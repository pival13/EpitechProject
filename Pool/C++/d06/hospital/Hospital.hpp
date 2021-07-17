/*
** EPITECH PROJECT, 2020
** cpp_d06_2019 [WSL: Ubuntu]
** File description:
** Hospital
*/

#ifndef HOSPITAL_H
#define HOSPITAL_H

#include "SickKoalaList.hpp"
#include "KoalaDoctorList.hpp"
#include "KoalaNurseList.hpp"

struct Hospital {
    Hospital();
    ~Hospital();

    void addSick(SickKoalaList *);
    void addNurse(KoalaNurseList *);
    void addDoctor(KoalaDoctorList *);
    void run();

    SickKoalaList *sick;
    KoalaNurseList *nurse;
    KoalaDoctorList *doctor;
};

#endif
/*
** EPITECH PROJECT, 2020
** cpp_d06_2019 [WSL: Ubuntu]
** File description:
** Hospital
*/

#include "Hospital.hpp"
#include <iostream>

Hospital::Hospital()
{
    sick = nullptr;
    nurse = nullptr;
    doctor = nullptr;
}

Hospital::~Hospital()
{
}

void Hospital::addSick(SickKoalaList *sick)
{
    if (this->sick->contain(sick))
        return;
    if (this->sick == nullptr)
        this->sick = sick;
    else
        this->sick->append(sick);
    std::cout << "[HOSPITAL] Patient " + sick->getContent()->getName() + " just arrived!\n";
}

void Hospital::addNurse(KoalaNurseList *nurse)
{
    if (this->nurse->contain(nurse))
        return;
    if (this->nurse == nullptr)
        this->nurse = nurse;
    else
        this->nurse->append(nurse);
    std::cout << "[HOSPITAL] Nurse " << nurse->getContent()->getID() << " just arrived!\n";
    nurse->getContent()->timeCheck();
}

void Hospital::addDoctor(KoalaDoctorList *doctor)
{
    if (this->doctor->contain(doctor))
        return;
    if (this->doctor == nullptr)
        this->doctor = doctor;
    else
        this->doctor->append(doctor);
    std::cout << "[HOSPITAL] Doctor " + doctor->getContent()->getName() + " just arrived!\n";
    doctor->getContent()->timeCheck();
}

void Hospital::run()
{
    KoalaDoctorList *dr;
    KoalaNurseList *nur;

    std::cout << "[HOSPITAL] Work starting with:\n";
    doctor->dump();
    nurse->dump();
    sick->dump();
    std::cout << std::endl;
    for (size_t i = 0; sick != nullptr; i++) {
        dr = doctor;
        nur = nurse;
        for (size_t j = 0; j != i % doctor->size(); j++)
            dr = dr->next;
        for (size_t j = 0; j != i % nurse->size(); j++)
            nur = nur->next;
        dr->getContent()->diagnose(sick->getContent());
        nur->getContent()->giveDrug(nur->getContent()->readReport(sick->getContent()->getName() + ".report"),sick->getContent());
        sick = sick->remove(sick);
    }
    for (; nurse != nullptr; nurse = nurse->remove(nurse))
        nurse->getContent()->timeCheck();
    for (; doctor != nullptr; doctor = doctor->remove(doctor))
        doctor->getContent()->timeCheck();
}
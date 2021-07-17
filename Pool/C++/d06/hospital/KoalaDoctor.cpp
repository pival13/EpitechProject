/*
** EPITECH PROJECT, 2020
** cpp_day06_2019 [WSL: Ubuntu]
** File description:
** KoalaDoctor
*/

#include <fstream>
#include <iostream>
#include "KoalaDoctor.hpp"

KoalaDoctor::KoalaDoctor(std::string name) : name(name), isWorking(false)
{
    std::cout << "Dr." << name << ": I'm Dr." << name << "! How do you kreog?" << std::endl;
}

KoalaDoctor::~KoalaDoctor()
{
}

void KoalaDoctor::diagnose(SickKoala *patient)
{
    std::string drugs[5] = {
        "Mars", "Buronzand", "Viagra", "Extasy", "Eucalyptus leaf"
    };
    int nb = random() % 5;
    std::ofstream f(patient->getName() + ".report");

    std::cout << "Dr." << name << ": So what's goerking you Mr." << patient->getName() << "?" << std::endl;
    patient->poke();
    f << drugs[nb];
    f.close();
}

void KoalaDoctor::timeCheck()
{
    if (isWorking) {
        isWorking = false;
        std::cout << "Dr." << name << ": Time to go home to my eucalyptus forest!" << std::endl;
    } else {
        isWorking = true;
        std::cout << "Dr." << name << ": Time to get to work!" << std::endl;
    }
}

std::string KoalaDoctor::getName()
{
    return name;
}

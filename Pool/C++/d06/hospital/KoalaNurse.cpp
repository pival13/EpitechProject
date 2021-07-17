/*
** EPITECH PROJECT, 2020
** cpp_day06_2019 [WSL: Ubuntu]
** File description:
** KoalaNurse
*/

#include <iostream>
#include <fstream>
#include "KoalaNurse.hpp"
#include <regex>

KoalaNurse::KoalaNurse(int ID) : ID(ID), isWorking(false)
{
}

KoalaNurse::~KoalaNurse()
{
    std::cout << "Nurse " << ID << ": Finally some rest!" << std::endl;
}

void KoalaNurse::giveDrug(std::string drug, SickKoala *patient)
{
    patient->takeDrug(drug);
}

std::string KoalaNurse::readReport(std::string reportName)
{
    std::ifstream f(reportName.c_str());
    std::string s;
    std::smatch result;

    std::regex_search(reportName, result, std::regex("^(.*).report$"));
    if (!f.is_open())
        return "";
    if (result.size() == 0) {
        f.close();
        return "";
    }
    f >> s;
    std::cout << "Nurse " << ID << ": Kreog! Mr." << result[1] << " needs a " << s << "!" << std::endl;
    f.close();
    return s;
}

void KoalaNurse::timeCheck()
{
    if (isWorking) {
        isWorking = false;
        std::cout << "Nurse " << ID << ": Time to go home to my eucalyptus forest!" << std::endl;
    } else {
        isWorking = true;
        std::cout << "Nurse " << ID << ": Time to get to work!" << std::endl;
    }
}

int KoalaNurse::getID()
{
    return ID;
}
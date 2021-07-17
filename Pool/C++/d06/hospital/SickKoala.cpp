/*
** EPITECH PROJECT, 2020
** SickKoala.cpp
** File description:
** SickKoala
*/

#include "SickKoala.hpp"
#include <regex>
#include <iostream>

SickKoala::SickKoala(std::string string) : name(string)
{
}

SickKoala::~SickKoala()
{
    std::cout << "Mr." << name << ": Kreooogg!! I'm cuuuured!" << std::endl;
}

void SickKoala::poke()
{
    std::cout << "Mr." << this->name << ": Gooeeeeerrk!!" << std::endl;
}

bool SickKoala::takeDrug(std::string str)
{
    if (str == "Mars") {
        std::cout << "Mr." << this->name << ": Mars, and it kreogs!" << std::endl;
        return true;
    } else if (str == "Buronzand") {
        std::cout << "Mr." << this->name << ": And you'll sleep right away!" << std::endl;
        return true;
    } else {
        std::cout << "Mr." << this->name << ": Goerkreog!" << std::endl;
        return false;
    }
}

void SickKoala::overDrive(std::string str)
{
    std::regex re("Kreog!");

    std::cout << "Mr." << this->name << ": " << std::regex_replace(str, re, "1337!") << std::endl;
}

std::string SickKoala::getName()
{
    return name;
}

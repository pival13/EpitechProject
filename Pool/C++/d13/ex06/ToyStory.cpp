/*
** EPITECH PROJECT, 2020
** cpp_d13_2019 [WSL: Ubuntu]
** File description:
** ToyStory
*/

#include "ToyStory.hpp"
#include <regex>

ToyStory::ToyStory()
{
}

ToyStory::~ToyStory()
{
}

static void aSimpleStory(const std::string &str, Toy &toy, bool (Toy::*funct)(const std::string &), bool &b)
{
    std::smatch match;

    if (std::regex_search(str, match, std::regex("^picture:(.*)$"))) {
        b = !b;
        toy.setAscii(match[1].str());
        if (toy.getAscii() != "ERROR")
            std::cout << toy.getAscii() << std::endl;
    } else {
        (toy.*funct)(str);
    }
    if (toy.getLastError().type != Toy::Error::UNKNOWN) {
        std::cout << toy.getLastError().where() << ": " << toy.getLastError().what() << std::endl;
        exit(0);
    }
}

void ToyStory::tellMeAStory(const std::string &file, 
                        Toy &a, bool (Toy::*f1)(const std::string &), 
                        Toy &b, bool (Toy::*f2)(const std::string &))
{
    std::cout << a.getAscii() << "\n" << b.getAscii() << std::endl;
    std::ifstream f(file);
    if (!f.is_open()) {
        std::cout << "Bad Story" << std::endl;
        return;
    }

    std::string str;
    bool unit = true;
    while (!f.eof()) {
        std::getline(f, str);
        aSimpleStory(str, (unit ? a : b), (unit ? f1 : f2) ,unit);
        unit = !unit;
    }
}
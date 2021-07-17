/*
** EPITECH PROJECT, 2020
** cpp_d13_2019 [WSL: Ubuntu]
** File description:
** Picture
*/

#include "Picture.hpp"

Picture::Picture()
: data("")
{
}

Picture::Picture(const std::string &file)
{
    getPictureFromFile(file);
}

Picture::~Picture()
{
}

bool Picture::getPictureFromFile(const std::string &file)
{
    std::ifstream f(file);

    if (!f.is_open()) {
        data = "ERROR";
        return false;
    }
    std::getline(f, data, '\0');
    return true;
}
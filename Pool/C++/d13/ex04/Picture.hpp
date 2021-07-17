/*
** EPITECH PROJECT, 2020
** cpp_d13_2019 [WSL: Ubuntu]
** File description:
** Picture
*/

#pragma once

#include <iostream>
#include <fstream>

class Picture {
    public:
        Picture();
        Picture(const std::string &file);
        ~Picture();

        bool getPictureFromFile(const std::string &file);

        std::string data;

    protected:
    private:
};

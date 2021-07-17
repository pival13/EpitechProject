/*
** EPITECH PROJECT, 2020
** cpp_d13_2019 [WSL: Ubuntu]
** File description:
** Buzz
*/

#pragma once

#include "Toy.hpp"

class Buzz : public Toy {
    public:
        Buzz(const std::string &name, const std::string &file="buzz.txt");
        ~Buzz();

        void speak(const std::string &str) const;

    protected:
    private:
};

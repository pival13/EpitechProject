/*
** EPITECH PROJECT, 2020
** cpp_d13_2019 [WSL: Ubuntu]
** File description:
** Woody
*/

#pragma once

#include "Toy.hpp"

class Woody : public Toy {
    public:
        Woody(const std::string &name, const std::string &file="woody.txt");
        ~Woody();
        
        void speak(const std::string &str) const;

    protected:
    private:
};

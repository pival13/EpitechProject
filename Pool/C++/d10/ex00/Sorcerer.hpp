/*
** EPITECH PROJECT, 2020
** cpp_d10_2019 [WSL: Ubuntu]
** File description:
** Sorcerer
*/

#pragma once

#include "Victim.hpp"

class Sorcerer {
    public:
        Sorcerer(const std::string &name, const std::string &title);
        ~Sorcerer();

        const std::string getName() const;
        const std::string getTitle() const;

        void polymorph(const Victim &victim) const;

    protected:
        Sorcerer();

    private:
        const std::string name;
        const std::string title;
};

std::ostream &operator<<(std::ostream &os, const Sorcerer &);
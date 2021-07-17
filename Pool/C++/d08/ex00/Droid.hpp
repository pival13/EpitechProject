/*
** EPITECH PROJECT, 2020
** cpp_d08_2019 [WSL: Ubuntu]
** File description:
** Droid
*/

#pragma once

#include <iostream>
#include <fstream>

class Droid {
    public:
        Droid(const std::string &serial="");
        Droid(const Droid &d);
        ~Droid();

        void setId(const std::string &serial);
        void setEnergy(size_t energy);
        void setStatus(std::string *status);
        std::string getId() const;
        size_t getEnergy() const;
        size_t getAttack() const;
        size_t getToughness() const;
        std::string *getStatus() const;

        bool operator==(Droid const &d) const;
        bool operator!=(Droid const &d) const;
        void operator<<(size_t &energy);
        Droid &operator=(Droid const &d1);

    protected:
    private:
        std::string Id;
        size_t Energy;
        const size_t Attack;
        const size_t Toughness;
        std::string *Status;
};

std::ostream &operator<<(std::ostream &os, Droid const &d1);
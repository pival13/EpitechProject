/*
** EPITECH PROJECT, 2020
** cpp_d08_2019 [WSL: Ubuntu]
** File description:
** DroidMemory
*/

#pragma once

#include <iostream>

class DroidMemory {
    public:
        DroidMemory();
        ~DroidMemory();

        size_t getFingerprint() const;
        size_t getExp() const;
        void setFingerprint(size_t);
        void setExp(size_t);

        DroidMemory &operator<<(DroidMemory const&);
        DroidMemory &operator>>(DroidMemory &) const;
        DroidMemory &operator+=(DroidMemory const&);
        DroidMemory &operator+=(size_t const);

    protected:
    private:
        size_t Exp;
        size_t Fingerprint;
};

DroidMemory operator+(DroidMemory const &d1, DroidMemory const &d2);
DroidMemory operator+(DroidMemory const &d1, size_t const &nb);
std::ostream &operator<<(std::ostream &os, DroidMemory const &d);
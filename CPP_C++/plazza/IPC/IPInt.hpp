/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019 [WSL: Ubuntu]
** File description:
** IPInt
*/

#pragma once

#include "IPObject.hpp"
#include <algorithm>
#include <iostream>

class IPInt : public IPObject {
    public:
        IPInt(size_t a);
        IPInt(const IPDataType &data);
        ~IPInt() = default;

        inline IPInt operator=(size_t a) { _a = a; return *this; }
        operator size_t() const;

        void pack();
        void unpack();

    private:
        size_t _a;
};

std::ostream &operator<<(std::ostream &os, const IPInt &a);
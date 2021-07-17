/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019 [WSL: Ubuntu]
** File description:
** IPString
*/

#pragma once

#include "IPObject.hpp"
#include <algorithm>
#include <iostream>

class IPString : public IPObject {
    public:
        IPString(const std::string &s);
        IPString(const IPDataType &data);
        ~IPString() = default;

        inline IPString operator=(const std::string &s) { _s = s; return *this; }
        operator std::string() const;

        void pack();
        void unpack();

    private:
        std::string _s;
};

std::ostream &operator<<(std::ostream &os, const IPString &s);
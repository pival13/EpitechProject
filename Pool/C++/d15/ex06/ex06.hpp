/*
** EPITECH PROJECT, 2020
** cpp_d15_2019 [WSL: Ubuntu]
** File description:
** ex06
*/

#pragma once

#include <iostream>
#include <string>
#include <sstream>

template<typename T, typename U=T>
class Tuple {
    private:
        template<class V> std::string toStringVar(V) const { return "[???]"; }
        std::string toStringVar(int a) const { return "[int:" + std::to_string(a) + "]"; }
        std::string toStringVar(float a) const { std::ostringstream os; os<<a; return "[float:" + os.str() + "f]"; }
        std::string toStringVar(std::string a) const { return "[string:\"" + a + "\"]"; }

    public:
        std::string toString() const {
            std::string str = "[TUPLE ";
            str += toStringVar(a);
            str += " ";
            str += toStringVar(b);
            str += "]";
            return str;
        }

        T a;
        U b;
};
/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019 [WSL: Ubuntu]
** File description:
** my_except
*/

#pragma once

#include <iostream>

namespace nts {
    class my_except : public std::exception {
        public: 
            my_except(const std::string &str);
            ~my_except();
            virtual const char *what() const throw();
        private: std::string str;
    };
}
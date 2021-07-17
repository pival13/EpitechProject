/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019 [WSL: Ubuntu]
** File description:
** Terminal
*/

#pragma once

#include "ADisplayModule.hpp"
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

class Terminal : public ADisplayModule {
    public:
        Terminal(ArcadeContent &ac);
        ~Terminal();

        void updateEvent();
        void setTexture(const std::string & fileName);
        void display();
    
    private:
        struct termios oldTerm;
        struct termios newTerm;

        std::map<char, std::array<char, 4>> _symbs;
};

extern "C" Terminal *getDisplayModule(ArcadeContent &);
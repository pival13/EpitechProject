/*
** EPITECH PROJECT, 2020
** cpp_d07m_2019 [WSL: Ubuntu]
** File description:
** Exam
*/

#include "Exam.hpp"
#include <iostream>

Exam::Exam(bool *cheat) : _cheat(cheat)
{
}

Exam::~Exam()
{
}

bool Exam::cheat = false;

bool Exam::isCheating()
{
    return *_cheat;
}

void Exam::start(int nb)
{
    std::cout << "[The exam is starting]\n" <<
                 nb << " Klingon vessels appeared out of nowhere.\n" <<
                 "they are fully armed and shielded\n";
    if (isCheating())
        std::cout << "What the... someone changed the parameters of the exam !" << std::endl;
    else
        std::cout << "This exam is hard... you lost again." << std::endl;
}
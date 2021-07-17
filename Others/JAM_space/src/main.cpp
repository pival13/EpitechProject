/*
** EPITECH PROJECT, 2020
** main.cpp
** File description:
** main
*/

// Project includes
#include "MainWindow.hpp"

// C++ includes
#include <random>
#include <time.h>

using namespace Jam;

int main(int ac, char * argv[])
{
    srand(time(NULL));

    MainWindow window(ac, argv);

    return window.exec();
}
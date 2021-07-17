/*
** EPITECH PROJECT, 2020
** cpp_rush3_2019
** File description:
** main.cpp
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "Sfml/Graphic.hpp"
#include "Ncurses/TextualDisplay.hpp"

void display_help()
{
    std::cout << "USAGE" << std::endl << "\t./MyGKrellm -t -g" << std::endl;
    std::cout << "DESCRIPTION" << std::endl << "\t-t : Textual display (ncurses)" << std::endl;
    std::cout << "\t-g : Graphical display (SFML)" << std::endl;
    exit (0);
}

IMonitorDisplay *getWindow(const char *s)
{
    if (strcmp(s, "-g") == 0)
        return new TextualDisplay();//Graphic();
    else {
        return new TextualDisplay();
    }
}

int main(int ac, char **av)
{
    if (ac != 2 || (strcmp(av[1], "-g") != 0 && strcmp(av[1], "-t") != 0))
        display_help();

    IMonitorDisplay *window = getWindow(av[1]);
    clock_t time = clock() - 1000000;

    while (!window->isEnd()) {
        window->getEvents();
        if (clock() > time + 1000000) {
            time += 1000000;
            window->updateModules();
        }
        window->drawModules();
    }
    delete window;
    return 0;
}
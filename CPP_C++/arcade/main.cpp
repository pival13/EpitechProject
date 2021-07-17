/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019 [WSL: Ubuntu]
** File description:
** main
*/

#include <iostream>
#include "Arcade.hpp"

int main(int n, char **arg)
{
    if (n != 2) {
        std::cout << "Usage:\n\t./arcade lib_graphic" << std::endl;
        exit(84);
    }
    try {
        Arcade arcade(arg[1], "./lib_arcade_MainMenu.so");
        arcade.play();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        std::exit(84);
    }
}

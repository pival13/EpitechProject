/*
** EPITECH PROJECT, 2020
** MainWindow.hpp
** File description:
** main window
*/

#pragma once

// Project includes
#include "SfmlTools.hpp"
#include "TextureBase.hpp"

#include "Cursor.hpp"
#include "Background.hpp"

// Pages includes
#include "MainMenu.hpp"
#include "Game.hpp"
#include "Pause.hpp"

#include "Characters/Character.hpp"

// C++ includes
#include <iostream>
#include <unistd.h>
#include <vector>

#define WINDOW_WIDTH  1920
#define WINDOW_HEIGHT 1080

class Jam::MainWindow
{
public:
    MainWindow(int argc, const char * const * argv);
    ~MainWindow();

    int exec();

private:
    int create();
    void playMusic();

private:
    int _argc;
    const char * const * _argv;
    sf::RenderWindow _window;
    sf::Event _event;

    // Sprites & textures
    std::vector<std::unique_ptr<sf::Sprite>>  _sprites;
    std::vector<std::unique_ptr<sf::Music>> _musics;
    Jam::Cursor _cursor;
    Jam::Background _background;

    // Page Structures
    std::vector<std::unique_ptr<IPage>> _pages;
};
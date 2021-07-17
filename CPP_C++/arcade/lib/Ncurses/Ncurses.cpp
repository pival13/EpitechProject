/*
** EPITECH PROJECT, 2019
** Ncurses.cpp
** File description:
** Created by etienne,
*/

#include <iostream>
#include <curses.h>
#include <zconf.h>
#include "ParserArcadeFileTexture.hpp"
#include "Ncurses.hpp"

Ncurses::Ncurses(ArcadeContent &pArcadeContent)
: ADisplayModule(pArcadeContent)
{
    _input = 0;
    if (!(initscr()))
        std::cerr << "Cannot init term." << std::endl;
    start_color();
    curs_set(false);
    keypad(stdscr, true);
    nodelay(stdscr, true);
    noecho();
    srand(getpid());
}

Ncurses::~Ncurses()
{
    endwin();
}

void Ncurses::updateEvent()
{
    if (isKeyPressed()) {
        releasePressedKey();
        return;
    }

    _input = getch();
    if (_input == 'x' || _input == 'X')
        turnOff();
    else if (_input == KEY_UP || _input == 'z' || _input == 'Z')
        moveUp();
    else if (_input == KEY_LEFT || _input == 'q' || _input == 'Q')
        moveLeft();
    else if (_input == KEY_DOWN || _input == 's' || _input == 'S')
        moveDown();
    else if (_input == KEY_RIGHT || _input == 'd' || _input == 'D')
        moveRight();
    else if (_input == ' ')
        validate();
    else if (_input == 'b' || _input == 'B')
        cancel();
    else if (_input == 'r' || _input == 'R')
        restart();
    else if (_input == 'p' || _input == 'P')
        backToMenu();
    else if (_input == '1' || _input == '&')
        prevGraph();
    else if (_input == '2')
        nextGraph();
    else if (_input == '3' || _input == '"')
        prevGame();
    else if (_input == '4' || _input == '\'')
        nextGame();
    else if (isKeyPressed())
        releasePressedKey();
    else if (isKeyReleased())
        noEvent();
    _input = 0;
}

void Ncurses::setTexture(const std::string &pFilepath)
{
    clear();
    ParserArcadeFileTexture parser(pFilepath);
    std::vector<char> lChar = parser.getSymbols();
    int index = 1;

    _mNcursesPairs.clear();
    for (auto character : lChar)
    {
        std::array<size_t, 2> lColors = parser.getColor(character);
        _mNcursesPairs.insert(std::pair<char, NcursesPair>(character, NcursesPair(index, parser.getChar(character), lColors)));
        init_pair(index, lColors[0], lColors[1]);
        index++;
    }
}

void Ncurses::display()
{
    clear();
    for (size_t y = 0; y != getMapHeight(); y++) {
        for (size_t x = 0; x != getMapWidth(); x++) {
            if (_mNcursesPairs.count(getMapAt(x, y))) {
                auto arr = _mNcursesPairs.at(getMapAt(x, y));
                attron(COLOR_PAIR(arr.getIndex()));
                mvprintw(y, x * 2, &arr.getChars()[0]);
                mvprintw(y, x * 2 + 1, &arr.getChars()[1]);
                attroff(COLOR_PAIR(arr.getIndex()));
            } else {
                mvprintw(y, x*2, " ");
                char c = getMapAt(x, y);
                if (c == '\0')
                    mvprintw(y, x*2+1, " ");
                else
                    mvprintw(y, x*2+1, &c);
            }
        }
    }
    refresh();
}

Ncurses *getDisplayModule(ArcadeContent &ac)
{
    return new Ncurses(ac);
}
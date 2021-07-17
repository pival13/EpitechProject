/*
** EPITECH PROJECT, 2019
** Libcaca.cpp
** File description:
** Created by etienne,
*/

#include <iostream>
#include "Libcaca.hpp"

Libcaca::Libcaca(ArcadeContent &arcade) : ADisplayModule(arcade)
{
    _canvas = caca_create_canvas(1600, 960);
    _display = caca_create_display(_canvas);
    caca_set_display_title(_display, "Arcade");
    caca_set_display_time(_display, 20);

}

Libcaca::~Libcaca() {
    caca_free_display(_display);
}

void Libcaca::updateEvent() {
    caca_event_t	event;
    if (caca_get_event(_display, CACA_EVENT_KEY_PRESS, &event,0) == 1) {
        _input = caca_get_event_key_ch(&event);
        if (_input == 'x' || _input == 'X')
            turnOff();
        else if (_input == CACA_KEY_UP || _input == 'z' || _input == 'Z')
            moveUp();
        else if (_input == CACA_KEY_LEFT || _input == 'q' || _input == 'Q')
            moveLeft();
        else if (_input == CACA_KEY_DOWN || _input == 's' || _input == 'S')
            moveDown();
        else if (_input == CACA_KEY_RIGHT || _input == 'd' || _input == 'D')
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
    }
    _input = 0;
}

void Libcaca::setTexture(const std::string &fileName) {
    caca_clear_canvas(_canvas);
    ParserArcadeFileTexture parser(fileName);
    std::vector<char> lChar = parser.getSymbols();
    int index = 1;

    _mCacaPairs.clear();
    for (auto character : lChar)
    {
        std::array<size_t, 2> lColors = parser.getColor(character);
        _mCacaPairs.insert(std::pair<char, CacaPair>(character, CacaPair(index, parser.getChar(character), lColors)));
        index++;
    }
}

void Libcaca::display() {
    caca_clear_canvas(_canvas);
    for (size_t y = 0; y != getMapHeight(); y++) {
        for (size_t x = 0; x != getMapWidth(); x++) {
            if (_mCacaPairs.count(getMapAt(x, y))) {
                auto arr = _mCacaPairs.at(getMapAt(x, y));
                caca_set_color_ansi(_canvas, arr.getColors()[0], arr.getColors()[1]);
                caca_put_char(_canvas, x * 2, y, arr.getChars()[0]);
                caca_put_char(_canvas, x * 2 + 1, y, arr.getChars()[1]);
                caca_set_color_ansi(_canvas, CACA_WHITE, CACA_BLACK);
            } else {
                caca_put_char(_canvas, x*2, y, ' ');
                char c = getMapAt(x, y);
                if (c == '\0')
                    caca_put_char(_canvas, x*2+1, y, ' ');
                else
                    caca_put_char(_canvas, x*2+1, y,c);
            }
        }
    }
    caca_refresh_display(_display);
}

Libcaca *getDisplayModule(ArcadeContent &ac)
{
    return new Libcaca(ac);
}
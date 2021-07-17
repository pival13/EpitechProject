/*
** EPITECH PROJECT, 2019
** AaLib.cpp
** File description:
** Created by etienne,
*/

#include "AaLib.hpp"

AaLib::AaLib(ArcadeContent &arcade)
: ADisplayModule(arcade)
{
    _context = aa_autoinit(&aa_defparams);
    aa_autoinitkbd(_context, 0);
    aa_flush(_context);

}

AaLib::~AaLib() {
    aa_close(_context);
}

void AaLib::updateEvent() {
    if (isKeyPressed()) {
        releasePressedKey();
        return;
    }

    _input = aa_getkey(_context, 0);
    if (_input == 'x' || _input == 'X')
        turnOff();
    else if (_input == AA_UP || _input == 'z' || _input == 'Z')
        moveUp();
    else if (_input == AA_LEFT || _input == 'q' || _input == 'Q')
        moveLeft();
    else if (_input == AA_DOWN || _input == 's' || _input == 'S')
        moveDown();
    else if (_input == AA_RIGHT || _input == 'd' || _input == 'D')
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

void AaLib::setTexture(const std::string &fileName) {
    ParserArcadeFileTexture parser(fileName);
    std::vector<char> lChar = parser.getSymbols();
    int index = 1;

    _mAaPairs.clear();
    for (auto character : lChar)
    {
        std::array<size_t, 2> lColors = parser.getColor(character);
        _mAaPairs.insert(std::pair<char, AalibPair>(character, AalibPair(index, parser.getChar(character), lColors)));
        index++;
    }
}

void AaLib::display() {
    for (size_t y = 0; y != getMapHeight(); y++) {
        for (size_t x = 0; x != getMapWidth(); x++) {
            if (_mAaPairs.count(getMapAt(x, y))) {
                auto arr = _mAaPairs.at(getMapAt(x, y));
                aa_printf(_context, x * 2, y, AA_NORMAL, &arr.getChars()[0]);
                aa_printf(_context, x * 2 + 1, y, AA_NORMAL, &arr.getChars()[1]);
            } else {
                aa_printf(_context, x*2, y, AA_NORMAL, " ");
                char c = getMapAt(x, y);
                if (c == '\0')
                    aa_printf(_context, x*2+1, y, AA_NORMAL, " ");
                else
                    aa_printf(_context, x*2+1, y, AA_NORMAL, &c);
            }
        }
    }
    aa_flush(_context);
}

AaLib *getDisplayModule(ArcadeContent &ac)
{
    return new AaLib(ac);
}

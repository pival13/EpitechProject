/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019 [WSL: Ubuntu]
** File description:
** Terminal
*/

#include "Terminal.hpp"

Terminal::Terminal(ArcadeContent &ac)
: ADisplayModule(ac)
{
    if (tcgetattr(0, &newTerm) == -1 || tcgetattr(0, &oldTerm) == -1)
        throw std::runtime_error("Can't get attribute of terminal");
    newTerm.c_lflag &= ~ECHO;
    newTerm.c_lflag &= ~ICANON;
    newTerm.c_cc[VMIN] = 0;
    newTerm.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &newTerm) == -1)
        throw std::runtime_error("Can't set attribute to terminal");
    fcntl(0, F_SETFL, fcntl(0, F_GETFL, 0) | O_NONBLOCK);
}

Terminal::~Terminal()
{
    tcsetattr(0, TCSANOW, &oldTerm);
}

void Terminal::updateEvent()
{
    char input = 0;
    if (!read(0, &input, 1))
        return;
    if (input == 'x' || input == 'X')
        turnOff();
    else if (input == 'z' || input == 'Z')
        moveUp();
    else if (input == 'q' || input == 'Q')
        moveLeft();
    else if (input == 's' || input == 'S')
        moveDown();
    else if (input == 'd' || input == 'D')
        moveRight();
    else if (input == ' ')
        validate();
    else if (input == 'b' || input == 'B')
        cancel();
    else if (input == 'r' || input == 'R')
        restart();
    else if (input == 'p' || input == 'P')
        backToMenu();
    else if (input == '1' || input == '&')
        prevGraph();
    else if (input == '2')
        nextGraph();
    else if (input == '3' || input == '"')
        prevGame();
    else if (input == '4' || input == '\'')
        nextGame();
    else if (input == '\e') {
        if (!read(0, &input, 1))
            return;
        if (input == '\e')
            turnOff();
        else if (input == '[') {
            if (!read(0, &input, 1))
                return;
            if (input == 'A')
                moveUp();
            else if (input == 'B')
                moveDown();
            else if (input == 'C')
                moveRight();
            else if (input == 'D')
                moveLeft();
        }
    }
    else if (isKeyReleased())
        noEvent();
}

void Terminal::setTexture(const std::string &s)
{
    ParserArcadeFileTexture parser(s);
    std::vector<char> symbs = parser.getSymbols();

    _symbs.clear();
    for (char symb : symbs)
    {
        auto chars = parser.getChar(symb);
        auto colors = parser.getColor(symb);
        for (int i = 0; i != 2; i++)
            if (colors[i] == 0)
                colors[i] = 10*i + 30;
            else if (colors[i] == 8)
                colors[i] = 10*i + 90;
            else
                colors[i] += 10*i + 90;
        _symbs.insert(std::pair<char, std::array<char, 4>>(symb, {chars[0],chars[1],(char)colors[0],(char)colors[1]}));
    }
}

void Terminal::display()
{
    std::stringstream out;
    out << "\e[3J\e[H";
    for (size_t y = 0; y != getMapHeight(); y++) {
        for (size_t x = 0; x != getMapWidth(); x++)
            if (!_symbs.count(getMapAt(x, y))) {
                out << "\e[0m";
                if (getMapAt(x, y) == '\0')
                    out << "  ";
                else
                    out << " " << getMapAt(x, y);
            } else {
                auto arr = _symbs[getMapAt(x, y)];
                out << "\e[" << (int)arr[2] << ";" << (int)arr[3] << "m";
                out << arr[0] << arr[1];
            }
        out << "\e[0m\n";
    }
    std::cout << out.str();
}

Terminal *getDisplayModule(ArcadeContent &ac)
{
    return new Terminal(ac);
}
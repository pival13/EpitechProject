/*
** EPITECH PROJECT, 2019
** Xlib.cpp
** File description:
** Created by etienne,
*/

#include <iostream>
#include "Xlib.hpp"
#include "keycodeDefines.hpp"

Xlib::Xlib(ArcadeContent &arcade) : ADisplayModule(arcade)
{
    std::cerr << "Error: Xlib is not finished" << std::endl;
    _display = XOpenDisplay(0);
    _screen = DefaultScreen(_display);
    _root = RootWindow(_display, _screen);
    _visual = DefaultVisual(_display, _screen);
    _window = XCreateSimpleWindow(_display, _root, \
    10, 10, 1600, 960, 1, BlackPixel(_display, 0), WhitePixel(_display, 0));
    _gc = XCreateGC (_display, _window, 0, 0);

    //event activation
    XSelectInput(_display, _window, KeyPressMask | KeyReleaseMask );

    //display window
    XMapWindow(_display, _window);
    XFlush(_display);

    //disable error massage on window closure
    Atom WM_DELETE_WINDOW = XInternAtom(_display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(_display, _window, &WM_DELETE_WINDOW, 1);
    const char *fontname = "-adobe-courier-medium-r-*-*-14-*-*-*-*-*-*-*";
    _font = XLoadQueryFont (_display, fontname);
    if (!_font)
        std::cerr << "Font error" << std::endl;
    else
        XSetFont(_display, _gc, _font->fid);
}

Xlib::~Xlib() {
    XCloseDisplay(_display);
}

void Xlib::updateEvent() {
    XNextEvent(_display, &_event);

    if (_event.type == ClientMessage) {
        turnOff();
    } else if (_event.type == KeyPress) {
        if (_event.xkey.keycode == KC_X) {
            turnOff();
        } else if (_event.xkey.keycode == KC_Z || _event.xkey.keycode == KC_UP) {
            moveUp();
        } else if (_event.xkey.keycode == KC_Q || _event.xkey.keycode == KC_LEFT) {
            moveLeft();
        } else if (_event.xkey.keycode == KC_S || _event.xkey.keycode == KC_DOWN) {
            moveDown();
        } else if (_event.xkey.keycode == KC_D || _event.xkey.keycode == KC_RIGHT) {
            moveRight();
        } else if (_event.xkey.keycode == KC_SPACE) {
            validate();
        } else if (_event.xkey.keycode == KC_B) {
            cancel();
        } else if (_event.xkey.keycode == KC_R) {
            restart();
        } else if (_event.xkey.keycode == KC_P) {
            backToMenu();
        } else if (_event.xkey.keycode == KC_1) {
            prevGraph();
        } else if (_event.xkey.keycode == KC_2) {
            nextGraph();
        } else if (_event.xkey.keycode == KC_3) {
            prevGame();
        } else if (_event.xkey.keycode == KC_4) {
            nextGame();
        }
    } else if (_event.type == KeyRelease) {
            noEvent();
    }
}

void Xlib::setTexture(const std::string &pFilepath) {
    XClearWindow (_display, _window);
    ParserArcadeFileTexture parser(pFilepath);
    std::vector<char> lChar = parser.getSymbols();
    int index = 1;

    _mXlibPairs.clear();
    for (auto character : lChar)
    {
        std::array<size_t, 2> lColors = parser.getColor(character);
        _mXlibPairs.insert(std::pair<char, XlibPair>(character, XlibPair(index, parser.getChar(character), lColors)));
        index++;
    }
}

void Xlib::display() {
    XClearWindow (_display, _window);
    for (size_t y = 0; y != getMapHeight(); y++) {
        for (size_t x = 0; x != getMapWidth(); x++) {
            size_t new_x = x * 5;
            size_t new_y = y * 4;
            if (_mXlibPairs.count(getMapAt(x, y))) {
                auto arr = _mXlibPairs.at(getMapAt(x, y));
                XDrawString(_display, _window, _gc , new_x, new_y, &arr.getChars()[0], 1);
                XDrawString(_display, _window, _gc, new_x + 2, new_y, &arr.getChars()[1], 1);
            } else {
                XDrawString(_display, _window, _gc, new_x, new_y, " ", 1);
                char c = getMapAt(x, y);
                if (c == '\0')
                    XDrawString(_display, _window, _gc, new_x+2, new_y, " ", 1);
                else
                    XDrawString(_display, _window, _gc, new_x+2, new_y, &c, 1);
            }
        }
    }
    XFlush(_display);
}

Xlib *getDisplayModule(ArcadeContent &ac)
{
    return new Xlib(ac);
}

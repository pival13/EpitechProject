/*
** EPITECH PROJECT, 2019
** Xlib.hpp
** File description:
** Created by etienne,
*/

#ifndef OOP_ARCADE_2019_XLIB_HPP
#define OOP_ARCADE_2019_XLIB_HPP

#include "ADisplayModule.hpp"
#include <stdio.h>
#include <X11/Xlib.h>

class Xlib: public ADisplayModule {
public:
    class XlibPair {
    public:
        XlibPair(int pIndex, std::array<char, 2> pChars, std::array<size_t, 2> pColors)
                : _index(pIndex), _lChars(pChars), _lColors(pColors) {}
        ~XlibPair() = default;

        std::array<char, 2> getChars() const {return(_lChars);};
        std::array<size_t, 2> getColors() const {return(_lColors);};
        int getIndex() const {return (_index);}

    private:
        int _index;
        std::array<char, 2> _lChars;
        std::array<size_t, 2> _lColors;
    };

    Xlib(ArcadeContent &arcade);

    virtual ~Xlib();

    void setTexture(const std::string &fileName) override;
    void updateEvent() override;
    void display() override;

private:
    Display *_display;
    Window _window;
    Window _root;
    Visual *_visual;
    GC _gc;
    int _screen;
    XEvent _event;
    std::map<char, XlibPair> _mXlibPairs;
    XFontStruct *_font;
};

extern "C" Xlib *getDisplayModule(ArcadeContent &ac);


#endif //OOP_ARCADE_2019_XLIB_HPP

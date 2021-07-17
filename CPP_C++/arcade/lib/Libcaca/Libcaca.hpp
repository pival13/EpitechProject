/*
** EPITECH PROJECT, 2019
** Libcaca.hpp
** File description:
** Created by etienne,
*/

#ifndef OOP_ARCADE_2019_LIBCACA_HPP
#define OOP_ARCADE_2019_LIBCACA_HPP


#include "ADisplayModule.hpp"
#include <caca.h>


class Libcaca: public ADisplayModule {
public:
    class CacaPair {
    public:
        CacaPair(int pIndex, std::array<char, 2> pChars, std::array<size_t, 2> pColors)
                : _index(pIndex), _lChars(pChars), _lColors(pColors) {}
        ~CacaPair() = default;

        std::array<char, 2> getChars() const {return(_lChars);};
        std::array<size_t, 2> getColors() const {return(_lColors);};
        int getIndex() const {return (_index);}

    private:
        int _index;
        std::array<char, 2> _lChars;
        std::array<size_t, 2> _lColors;
    };

    Libcaca(ArcadeContent &arcade);
    virtual ~Libcaca();

    void updateEvent() override;
    void setTexture(const std::string &fileName) override;
    void display() override;

    caca_display_t *_display;
    caca_canvas_t *_canvas;
    caca_canvas_t *_map;
    size_t _width;
    size_t _height;
    int _input;
    std::map<char, CacaPair> _mCacaPairs;
};

extern "C" Libcaca *getDisplayModule(ArcadeContent &ac);

#endif //OOP_ARCADE_2019_LIBCACA_HPP

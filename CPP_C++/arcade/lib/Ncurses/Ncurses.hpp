/*
** EPITECH PROJECT, 2019
** Ncurses.hpp
** File description:
** Created by etienne,
*/

#ifndef OOP_ARCADE_2019_LIBNCURSES_HPP
#define OOP_ARCADE_2019_LIBNCURSES_HPP

#include "ADisplayModule.hpp"
#include <array>

class Ncurses: public ADisplayModule {
public:
    class NcursesPair {
    public:
        NcursesPair(int pIndex, std::array<char, 2> pChars, std::array<size_t, 2> pColors)
        : _index(pIndex), _lChars(pChars), _lColors(pColors) {}
        ~NcursesPair() = default;

        std::array<char, 2> getChars() const {return(_lChars);};
        std::array<size_t, 2> getColors() const {return(_lColors);};
        int getIndex() const {return (_index);}

    private:
        int _index;
        std::array<char, 2> _lChars;
        std::array<size_t, 2> _lColors;
    };

    Ncurses(ArcadeContent &pArcadeContent);
    ~Ncurses();

    void updateEvent() override ;
    void setTexture(const std::string & fileName) override ;
    void display() override;

    std::map<char, NcursesPair> getNcursesPairs() const {return (_mNcursesPairs);}
private:
    int _input;
    std::map<char, NcursesPair> _mNcursesPairs;
};



extern "C" Ncurses *getDisplayModule(ArcadeContent &);


#endif //OOP_ARCADE_2019_LIBNCURSES_HPP

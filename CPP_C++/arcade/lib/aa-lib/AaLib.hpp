/*
** EPITECH PROJECT, 2019
** AaLib.hpp
** File description:
** Created by etienne,
*/

#ifndef OOP_ARCADE_2019_AALIB_HPP
#define OOP_ARCADE_2019_AALIB_HPP


#include "ADisplayModule.hpp"
#include <aalib.h>

class AaLib: public ADisplayModule {
public:
    class AalibPair {
    public:
        AalibPair(int pIndex, std::array<char, 2> pChars, std::array<size_t, 2> pColors)
                : _index(pIndex), _lChars(pChars), _lColors(pColors) {}
        ~AalibPair() = default;

        std::array<char, 2> getChars() const {return(_lChars);};
        std::array<size_t, 2> getColors() const {return(_lColors);};
        int getIndex() const {return (_index);}

    private:
        int _index;
        std::array<char, 2> _lChars;
        std::array<size_t, 2> _lColors;
    };


    AaLib(ArcadeContent &arcade);
    virtual ~AaLib();

    void updateEvent() override;
    void setTexture(const std::string &fileName) override;
    void display() override;

private:
    aa_context *_context;
    int _input;
    std::map<char, AalibPair> _mAaPairs;
    std::map<char, std::array<char, 4>> _symbs;
};

extern "C" AaLib *getDisplayModule(ArcadeContent &);

#endif //OOP_ARCADE_2019_AALIB_HPP

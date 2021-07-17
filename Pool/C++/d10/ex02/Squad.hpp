/*
** EPITECH PROJECT, 2020
** cpp_d10_2019 [WSL: Ubuntu]
** File description:
** Squad
*/

#pragma once

#include "ISquad.hpp"
#include <iostream>
#include <vector>

class Squad : public ISquad {
    public:
        Squad();
        Squad(const Squad &);
        ~Squad();

        int getCount() const;
        ISpaceMarine *getUnit(int);
        ISpaceMarine *getUnit(int) const;
        int push(ISpaceMarine *);

        Squad &operator=(const Squad &);

    protected:
    private:
        std::vector<ISpaceMarine *> _units;
};

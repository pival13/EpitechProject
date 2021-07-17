/*
** EPITECH PROJECT, 2020
** cpp_d08_2019 [WSL: Ubuntu]
** File description:
** Supply
*/

#pragma once

#include "Droid.hpp"

class Supply {
    public:
        enum Types {
            Iron,
            Silicon,
            Wreck,
        };

        Supply(Types type, size_t amount, Droid **droids=nullptr);
        ~Supply();

        Supply &operator!();
        bool operator==(Supply const &) const;
        bool operator!=(Supply const &) const;
        Supply &operator--();
        Supply &operator++();
        Supply &operator--(int);
        Supply &operator++(int);
        Droid *&operator->();
        Droid *&operator*();
        Droid *operator*() const;
        operator size_t() const;

        Types Type;
        size_t Amount;
        Droid **Wrecks;

    protected:
    private:
        size_t pos;
};

std::ostream &operator<<(std::ostream &, Supply &);
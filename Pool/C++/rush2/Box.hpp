/*
** EPITECH PROJECT, 2020
** rush2 [WSL: Ubuntu]
** File description:
** Box
*/

#pragma once

#include "Wrap.hpp"

class Box : public Wrap {
    public:
        Box();
        ~Box();

        bool wrapMeThat(Object *&);
        Object *openMe();
        void closeMe();

    protected:
    private:
        bool _isOpen;
};

/*
** EPITECH PROJECT, 2020
** rush2 [WSL: Ubuntu]
** File description:
** LittlePony
*/

#pragma once

#include "Toy.hpp"

class LittlePony : public Toy {
    public:
        LittlePony(const std::string &title);
        ~LittlePony();

        void isTaken() const;

    protected:
    private:
};

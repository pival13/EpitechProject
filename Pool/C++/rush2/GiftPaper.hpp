/*
** EPITECH PROJECT, 2020
** rush2 [WSL: Ubuntu]
** File description:
** GiftPaper
*/

#pragma once

#include "Wrap.hpp"
#include "Box.hpp"
#include "GiftPaper.hpp"
#include "LittlePony.hpp"
#include "Teddy.hpp"

class GiftPaper : public Wrap {
    public:
        GiftPaper();
        ~GiftPaper() override;

        bool wrapMeThat(Object *&);

    protected:
    private:
};

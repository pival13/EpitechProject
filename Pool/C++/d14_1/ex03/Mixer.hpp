/*
** EPITECH PROJECT, 2020
** cpp_d14m_2019 [WSL: Ubuntu]
** File description:
** Mixer
*/

#pragma once

#include "FruitBox.hpp"
#include "MixerBase.hpp"

class Mixer : public MixerBase {
    public:
        Mixer();
        ~Mixer();

        int mix(FruitBox &fruits) const;
        void plug();

    protected:
    private:
};

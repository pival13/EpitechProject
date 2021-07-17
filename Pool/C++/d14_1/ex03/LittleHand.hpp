/*
** EPITECH PROJECT, 2020
** cpp_d14m_2019 [WSL: Ubuntu]
** File description:
** LittleHand
*/

#pragma once

#include "Mixer.hpp"
#include "Lime.hpp"
#include "Banana.hpp"
#include "Coconut.hpp"

class LittleHand {
	public:
        static void sortFruitBox(FruitBox &unsorted, FruitBox &lemon, FruitBox &banana, FruitBox &lime);
		static FruitBox * const *organizeCoconut(Coconut const * const *coconuts);
		static void plugMixer(MixerBase &mixer);

	protected:
	private:
};

/*
** EPITECH PROJECT, 2020
** cpp_d10_2019 [WSL: Ubuntu]
** File description:
** KoalaSteroid
*/

#pragma once

#include "IAsteroid.hpp"

class KoalaSteroid : public IAsteroid {
	public:
		KoalaSteroid();
		~KoalaSteroid();

        std::string beMined(StripMiner *) const;
        std::string beMined(DeepCoreMiner *) const;
        std::string getName() const;

	protected:
	private:
};

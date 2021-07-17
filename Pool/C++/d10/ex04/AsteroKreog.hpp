/*
** EPITECH PROJECT, 2020
** cpp_d10_2019 [WSL: Ubuntu]
** File description:
** AsteroKreog
*/

#pragma once

#include "IAsteroid.hpp"

class AsteroKreog : public IAsteroid {
	public:
		AsteroKreog();
		~AsteroKreog();

        std::string beMined(StripMiner *) const;
        std::string beMined(DeepCoreMiner *) const;
        std::string getName() const;

	protected:
	private:
};

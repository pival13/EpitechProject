/*
** EPITECH PROJECT, 2020
** cpp_d10_2019 [WSL: Ubuntu]
** File description:
** IAsteroid
*/

#pragma once

#include <iostream>

class StripMiner;
class DeepCoreMiner;

class IAsteroid {
	public:
		virtual ~IAsteroid() {}
        virtual std::string beMined(StripMiner *) const = 0;
        virtual std::string beMined(DeepCoreMiner *) const = 0;
        virtual std::string getName() const = 0;

	protected:
	private:
};

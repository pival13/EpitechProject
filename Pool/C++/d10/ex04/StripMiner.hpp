/*
** EPITECH PROJECT, 2020
** cpp_d10_2019 [WSL: Ubuntu]
** File description:
** StripMiner
*/

#pragma once

#include "IMiningLaser.hpp"
#include "IAsteroid.hpp"
#include <iostream>

class StripMiner : public IMiningLaser {
	public:
		StripMiner();
		~StripMiner();

        void mine(IAsteroid *);

	protected:
	private:
};

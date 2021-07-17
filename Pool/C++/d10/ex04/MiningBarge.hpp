/*
** EPITECH PROJECT, 2020
** cpp_d10_2019 [WSL: Ubuntu]
** File description:
** MiningBarge
*/

#pragma once

#include "IAsteroid.hpp"
#include "IMiningLaser.hpp"
#include <array>

class MiningBarge {
	public:
		MiningBarge();
		~MiningBarge();

        void equip(IMiningLaser *laser);
        void mine(IAsteroid *asteroid) const;

	protected:
	private:
        std::array<IMiningLaser *, 4> _laser;
};

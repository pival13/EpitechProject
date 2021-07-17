/*
** EPITECH PROJECT, 2020
** cpp_d09_2019 [WSL: Ubuntu]
** File description:
** Paladin
*/

#pragma once

#include "Warrior.hpp"
#include "Priest.hpp"

class Paladin : public Warrior, public Priest {
	public:
		Paladin(const std::string &name, int level, const std::string &weapon="hammer");
		~Paladin();

        int CloseAttack();
        int RangeAttack();
        void Heal();
        void RestorePower();
        int Intercept();

	protected:

	private:
        const std::string Weapon;
};

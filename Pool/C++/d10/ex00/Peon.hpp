/*
** EPITECH PROJECT, 2020
** cpp_d10_2019 [WSL: Ubuntu]
** File description:
** Peon
*/

#pragma once

#include "Victim.hpp"

class Peon : virtual public Victim {
	public:
		Peon(const std::string &name);
		~Peon();

        void getPolymorphed() const override;

	protected:
	private:
};

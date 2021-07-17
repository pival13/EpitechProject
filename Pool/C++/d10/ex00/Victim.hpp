/*
** EPITECH PROJECT, 2020
** cpp_d10_2019 [WSL: Ubuntu]
** File description:
** Victim
*/

#pragma once

#include <iostream>

class Victim {
	public:
		Victim(const std::string &name);
		~Victim();

        const std::string getName() const;

        virtual void getPolymorphed() const;

	protected:
        const std::string _name;

	private:
};

std::ostream &operator<<(std::ostream &os, const Victim &);
/*
** EPITECH PROJECT, 2020
** cpp_d08_2019 [WSL: Ubuntu]
** File description:
** DroidFactory
*/

#pragma once

#include "Supply.hpp"

class DroidFactory {
	public:
		explicit DroidFactory(const size_t ratio=2);
		DroidFactory(const DroidFactory &);
		~DroidFactory();

        DroidFactory &operator<<(Supply &);
        Droid *operator>>(Droid *&);
        DroidFactory &operator++();
        DroidFactory &operator--();
        DroidFactory &operator++(int);
        DroidFactory &operator--(int);

        size_t getIron() const;
        size_t getSilicon() const;
        size_t getRatio() const;
        size_t getExp() const;

	protected:
	private:
        size_t Iron;
        size_t Silicone;
        size_t Ratio;
        size_t Exp;
};

DroidFactory &operator>>(Supply &, DroidFactory &);
//DroidFactory &operator>>(Supply &, DroidFactory &);
std::ostream &operator<<(std::ostream &, DroidFactory &);
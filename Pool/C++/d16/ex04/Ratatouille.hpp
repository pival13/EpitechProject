/*
** EPITECH PROJECT, 2020
** cpp_d16_2019 [WSL: Ubuntu]
** File description:
** Ratatouille
*/

#pragma once

#include <sstream>

class Ratatouille {
	public:
		Ratatouille();
        Ratatouille(const Ratatouille &other);
		~Ratatouille();

        Ratatouille &operator=(const Ratatouille &other);

        Ratatouille &addVegetable(unsigned char );
        Ratatouille &addCondiment(unsigned int);
        Ratatouille &addSpice(double);
        Ratatouille &addSauce(const std::string &);
        std::string kooc() const;

        std::ostringstream _recipe;
};

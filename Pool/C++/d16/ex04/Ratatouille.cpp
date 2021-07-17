/*
** EPITECH PROJECT, 2020
** cpp_d16_2019 [WSL: Ubuntu]
** File description:
** Ratatouille
*/

#include"Ratatouille.hpp"

Ratatouille::Ratatouille() {}
Ratatouille::Ratatouille(const Ratatouille &other) { *this = other; }
Ratatouille::~Ratatouille() {}

Ratatouille &Ratatouille::operator=(const Ratatouille &other) { _recipe.str(""); _recipe << other._recipe.str(); return *this; }

Ratatouille &Ratatouille::addVegetable(unsigned char veget) { _recipe << veget; return *this; }
Ratatouille &Ratatouille::addCondiment(unsigned int cond) { _recipe << cond; return *this; }
Ratatouille &Ratatouille::addSpice(double spice) { _recipe << spice; return *this; }
Ratatouille &Ratatouille::addSauce(const std::string &sauce) { _recipe << sauce; return *this; }
std::string Ratatouille::kooc() const { return _recipe.str(); }


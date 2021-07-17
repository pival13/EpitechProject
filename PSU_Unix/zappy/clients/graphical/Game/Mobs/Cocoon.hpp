/*
** By Kevin Pruvost, May 2020
** File description:
** Cocoon class.
*/

#pragma once

// Project includes
#include "Mob.hpp"

/**
 * @brief Keeps a cocoon informations, but most importantly, can be used for polymorphism with Mob or Object.
 */
class Cocoon : public Mob
{
public:
	Cocoon(int x, int y, int id, int pid);
	Cocoon(const sf::Vector2f & vec, int id, int pid);
	~Cocoon();

	bool operator==(const Cocoon & otherCocoon);

private:
	int playerId;
};
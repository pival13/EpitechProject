/*
** By Kevin Pruvost, June 2020
** File description:
** Target class.
*/

#pragma once

// Project includes
#include "Cocoon.hpp"
#include "Floor.hpp"

/**
 * @brief Used to determine which object the camera will focus.
 * (because pointers on vector elements are very dangerous)
 */
class Target
{
public:
	Target();
	Target(const Cocoon & cocoon);
	Target(const Mob & cocoon);
	Target(const Floor & cocoon);
	Target(const Object * cocoon);
	~Target();

	Target & operator=(const Cocoon & cocoon);
	Target & operator=(const Mob & mob);
	Target & operator=(const Floor & floor);
	Target & operator=(const Object * obj);

	bool operator==(const Cocoon & cocoon);
	bool operator==(const Mob & mob);
	bool operator==(const Floor & floor);

	Object * get(const KVector<Mob> & players, const KVector<Cocoon> & eggs, const KVector<Floor> & tiles);

public:
	Object::ObjectIdentity objectIdentity = Object::ObjectIdentity::Floor;
	int id = 0;
	sf::Vector2i pos = {0, 0};
};
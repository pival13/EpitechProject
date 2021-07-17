/*
** By Kevin Pruvost, June 2020
** File description:
** Incantation class.
*/

#pragma once

// Project includes
#include "Target.hpp"

/**
 * @brief Contains pointers to mobs of an incantation.
 */
class Incantation : virtual public KVector<Target>
{
public:
	Incantation(const Position & pos, const KVector<Target> & vec);
	Incantation(const Position & pos);
	~Incantation();
	using KVector<Target>::operator=;

	void startIncantation(const KVector<Mob> & players, const KVector<Cocoon> & eggs, const KVector<Floor> & tiles);
	void endIncantation(bool result, const KVector<Mob> & players, const KVector<Cocoon> & eggs, const KVector<Floor> & tiles);

public:
	Position position;

private:
	bool _state = false;
};
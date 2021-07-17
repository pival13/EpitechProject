/*
** By Kevin Pruvost, June 2020
** File description:
** Incantation class.
*/

#include "Incantation.hpp"

Incantation::Incantation(const Position & pos)
    : position { pos }
{
}

Incantation::Incantation(const Position & pos, const KVector<Target> & vec)
    : Incantation(pos)
{
    *this = vec;
}

Incantation::~Incantation()
{
}

void Incantation::startIncantation(const KVector<Mob> & players, const KVector<Cocoon> & eggs, const KVector<Floor> & tiles)
{
    if (_state)
        return;

    KVector<Mob *> results;

    for (auto & player : *this)
        results.push_back((Mob *)player.get(players, eggs, tiles));

    for (auto & player : results)
    {
        if (player)
            player->startElevation();
    }
    _state = true;
}

void Incantation::endIncantation(bool result, const KVector<Mob> & players, const KVector<Cocoon> & eggs, const KVector<Floor> & tiles)
{
    if (!_state)
        return;

    KVector<Mob *> results;

    for (auto & player : *this)
        results.push_back((Mob *)player.get(players, eggs, tiles));

    for (auto & player : results)
    {
        if (!player)
            continue;

        if (result)
            player->upLevel();
        player->stopElevation();
    }
    _state = false;
}
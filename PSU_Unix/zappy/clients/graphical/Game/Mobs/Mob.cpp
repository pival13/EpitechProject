/*
** By Kevin Pruvost, May 2020
** File description:
** Mob class.
*/

#include "Mob.hpp"

const std::map<int, Constants::TextureId> Mob::textureByLevel = {
	{0, Constants::TextureId::COCOON},
	{1, Constants::TextureId::LARVA},
	{2, Constants::TextureId::DRONE},
	{3, Constants::TextureId::ZERGLING},
	{4, Constants::TextureId::BANELING},
	{5, Constants::TextureId::ROACH},
	{6, Constants::TextureId::HYDRALISK},
	{7, Constants::TextureId::QUEEN},
	{8, Constants::TextureId::ULTRALISK}
};

Mob::Mob(int x, int y, int iD, int lvl)
    : Object(textureByLevel.at(lvl))
    , endMoveFunctionPointer { &Mob::endMoveToIdle }
{
    objectIdentity = ObjectIdentity::Mob;
    id = iD;
    level = lvl;
    pos.x = x;
    pos.y = y;
    animate(AnimateOptions::Loop, 1, 0);
}

Mob::Mob(const sf::Vector2f & vec, int iD, int lvl)
    : Mob(vec.x, vec.y, iD, lvl)
{
}

Mob::~Mob()
{
}

bool Mob::operator==(const Mob & otherMob)
{
    return id == otherMob.id;
}

Mob & Mob::operator=(const PlayerData & playerData)
{
    pos.x = playerData.position.x;
    pos.y = playerData.position.y;
    level = playerData.level;
    orientation = playerData.orientation;
    inventory = playerData.inventory;
    id = playerData.id;
    teamName = playerData.teamName;
    isIncanting = playerData.isIncanting;
    isIncantingToLvl = playerData.isIncantingToLvl;
    dead = playerData.dead;
    isLayingEgg = playerData.isLayingEgg;
    return *this;
}

Mob & Mob::operator=(const InventoryData & inventoryData)
{
    inventory = inventoryData;
    return *this;
}

void Mob::move(const sf::Vector2f & vec, float time)
{
    Mob::move(vec, time);
}

void Mob::move(float x, float y, float time)
{
    Object::move(x, y, time);
    setScale(((x < 0) ? -1 : 1), 1);
    if (!isExpulsed)
        animateQueue(AnimateOptions::EndsOnStopMoving | AnimateOptions::EndsOnFirstFrame, time / 2, 1);
    animateQueue(AnimateOptions::Loop, 1, 0);
}

void Mob::moveTo(const sf::Vector2f & vec, float time)
{
    Mob::moveTo(vec.x, vec.y, time);
}

void Mob::moveTo(float x, float y, float time)
{
    Object::moveTo(x, y, time);
    setScale(((x < getPosition().x) ? -1 : 1), 1);
    if (!isExpulsed)
        animateQueue(AnimateOptions::EndsOnStopMoving | AnimateOptions::EndsOnFirstFrame, time / 2, 1);
    animateQueue(AnimateOptions::Loop, 1, 0);
}

void Mob::startElevation()
{
    changeTexture(textureByLevel.at(0));
    animateQueue(AnimateOptions::EndsOnLastFrame, 0.4, 1);
    animateQueue(AnimateOptions::Loop, 1, 0);
    isElevating = true;
    isIncanting = true;
}

void Mob::stopElevation()
{
    animateQueue(AnimateOptions::EndsOnLastFrame, 0.4, 2);
    isElevating = false;
    isIncanting = false;
    endAnimationFunctionPointer = &Mob::stopElevationFP;
}

void Mob::stopElevationFP()
{
    changeTexture(textureByLevel.at(level));
    animate(AnimateOptions::Loop, 1, 0);
}

void Mob::endAnimationFunction()
{
    if (!endAnimationFunctionPointer)
        return;
    auto ptr = endAnimationFunctionPointer;
    endAnimationFunctionPointer = nullptr;
    (this->*ptr)();
}

void Mob::endMoveFunction()
{
    if (!endMoveFunctionPointer)
        return;
    (this->*endMoveFunctionPointer)();
}

void Mob::endMoveToIdle()
{
    animate(AnimateOptions::Loop, 1, 0);
}

void Mob::upLevel()
{
    ++level;
    if (level > 8)
        level = 8;
    changeTexture(textureByLevel.at(level));
}

void Mob::setLevel(int lvl)
{
    level = lvl;
    if (level > 8)
        level = 8;
    if (level < 0)
        level = 0;
    changeTexture(textureByLevel.at(level));
}


void Mob::adaptToOrientation(Orientation ori)
{
    int ori1 = ori - 1;
    int ori2 = ori + 1;

    if (ori1 < Orientation::NORTH)
        ori1 = Orientation::WEST;
    if (ori2 > Orientation::WEST)
        ori2 = Orientation::NORTH;

    if (ori1 == orientation)
        setScale(-1, 1);
    else if (ori2 == orientation)
        setScale(1, 1);
}
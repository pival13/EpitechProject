/*
** By Kevin Pruvost, May 2020
** File description:
** Mob class.
*/

#pragma once

// Project includes
#include "Object.hpp"
#include "PlayerData.hpp"
#include "InventoryData.hpp"

/**
 * @brief Contains a mob data and is aimed to be drawn.
 */
class Mob : public Object, virtual public PlayerData
{
public:
	Mob(int x, int y, int id, int lvl = 1);
	Mob(const sf::Vector2f & vec, int id, int lvl = 1);
	~Mob();

	bool operator==(const Mob & otherMob);

	/**
	 * @brief Takes the playerData and assimilates it.
	 * @param playerData
	 * @return Mob&
	 */
	Mob & operator=(const PlayerData & playerData);
	/**
	 * @brief Takes the inventoryData and assimilates it.
	 * @param inventoryData
	 * @return Mob&
	 */
	Mob & operator=(const InventoryData & inventoryData);

	void move(const sf::Vector2f & vec, float time = 0) override;
	void move(float x, float y, float time = 0) override;
	void moveTo(const sf::Vector2f & vec, float time = 0) override;
	void moveTo(float x, float y, float time = 0) override;

	/**
	 * @brief Override of Object::endAnimationFunction().
	 */
	void endAnimationFunction() override;
	/**
	 * @brief Override of Object::endMoveFunction().
	 */
	void endMoveFunction() override;

	/**
	 * @brief Function used to make the object idle when it finishes moving.
	 */
	void endMoveToIdle();

	/**
	 * @brief Starts the elevation, animating it and changing its attributes.
	 */
	void startElevation();
	/**
	 * @brief Ends the elevation.
	 */
	void stopElevation();
	/**
	 * @brief Aimed to be used as a function pointer to the end of the animation
	 * of the stopElevation() function.
	 */
	void stopElevationFP();

	/**
	 * @brief Changes the level up to one unit.
	 */
	void upLevel();

	/**
	 * @brief Sets the object level.
	 * @param lvl
	 */
	void setLevel(int lvl);

	/**
	 * @brief Changes the scale according to the orientation.
	 * @param orientation
	 */
	void adaptToOrientation(Orientation orientation);

public:
	bool isElevating = false;
	bool isExpulsed = false;

	std::string broadcastMessage;

	void (Mob::* endAnimationFunctionPointer)() = nullptr;
	void (Mob::* endMoveFunctionPointer)() = nullptr;

	static const std::map<int, Constants::TextureId> textureByLevel;
};
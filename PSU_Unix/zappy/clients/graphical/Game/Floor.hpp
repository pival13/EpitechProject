/*
** By Kevin Pruvost, May 2020
** File description:
** Floor class.
*/

#pragma once

// Project includes
#include "Object.hpp"
#include "InventoryData.hpp"

/**
 * @brief Contains a floor data and is aimed to be drawn by Game.
 */
class Floor : public Object
{
public:
	Floor(Constants::TextureId textureId, int x, int y);
	~Floor();

	void move(const sf::Vector2f & vec, float time = 0) override;
	void move(float x, float y, float time = 0) override;
	void moveTo(const sf::Vector2f & vec, float time = 0) override;
	void moveTo(float x, float y, float time = 0) override;

public:
	InventoryData inventory;
	KVector<Object> inventorySprites;
};
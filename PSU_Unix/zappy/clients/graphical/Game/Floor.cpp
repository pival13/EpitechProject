/*
** By Kevin Pruvost, May 2020
** File description:
** Floor class.
*/

#include "Floor.hpp"

Floor::Floor(Constants::TextureId textureId, int xx, int yy)
    : Object(textureId)
{
    objectIdentity = ObjectIdentity::Floor;
    pos.x = xx;
    pos.y = yy;
    inventorySprites.emplace_back(Constants::TextureId::FOOD);
    int x = inventorySprites.back().texture->getSize().x / 2 - texture->getSize().x / 2;
    int y = texture->getSize().y / 2 - inventorySprites.back().texture->getSize().y / 2;
    inventorySprites.back().setPosition(x, y);
    x += inventorySprites.back().texture->getSize().x;
    inventorySprites.emplace_back(Constants::TextureId::LINEMATE_TEXTURE);
    inventorySprites.back().setPosition(x, y);
    x += inventorySprites.back().texture->getSize().x;
    inventorySprites.emplace_back(Constants::TextureId::DERAUMERE_TEXTURE);
    inventorySprites.back().setPosition(x, y);
    x += inventorySprites.back().texture->getSize().x;
    inventorySprites.emplace_back(Constants::TextureId::SIBUR_TEXTURE);
    inventorySprites.back().setPosition(x, y);
    x += inventorySprites.back().texture->getSize().x;
    inventorySprites.emplace_back(Constants::TextureId::MENDIANE_TEXTURE);
    inventorySprites.back().setPosition(x, y);
    x += inventorySprites.back().texture->getSize().x;
    inventorySprites.emplace_back(Constants::TextureId::PHIRAS_TEXTURE);
    inventorySprites.back().setPosition(x, y);
    x += inventorySprites.back().texture->getSize().x;
    inventorySprites.emplace_back(Constants::TextureId::THYSTAME_TEXTURE);
    inventorySprites.back().setPosition(x, y);
    x += inventorySprites.back().texture->getSize().x;
}

Floor::~Floor()
{
}

void Floor::move(const sf::Vector2f & vec, float time) { move(vec.x, vec.y, time); }
void Floor::move(float x, float y, float time)
{
    Object::move(x, y, time);
    for (auto & obj : inventorySprites)
        obj.move(x, y, time);
}

void Floor::moveTo(const sf::Vector2f & vec, float time) { moveTo(vec.x, vec.y, time); }
void Floor::moveTo(float x, float y, float time)
{
    auto newX = x - getPosition().x;
    auto newY = y - getPosition().y;
    for (auto & obj : inventorySprites)
        obj.move(newX, newY, time);
    Object::moveTo(x, y, time);
}

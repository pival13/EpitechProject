/*
** By Kevin Pruvost, May 2020
** Game2.cpp
** File description:
** game 2
*/

#include "Game.hpp"

static std::mutex mutex;

void Game::buildTileMap()
{
    bool textureSwitch = true;

    for (int i = 0; i < _mapSize.x; ++i)
    {
        _tilesByPosition.emplace_back();
        for (int j = 0; j < _mapSize.y; ++j)
        {
            _tiles.emplace_back(((textureSwitch) ?
                Constants::TextureId::FLOOR1 : Constants::TextureId::FLOOR2),
            i, j);
            textureSwitch = !textureSwitch;
        }
        ((int)_mapSize.y % 2 == 0) ? textureSwitch = !textureSwitch : 0;
    }
    for (int i = 0; i < _mapSize.x; ++i)
    {
        for (int j = 0; j < _mapSize.y; ++j)
        {
            _tilesByPosition[i].push_back(std::ref(_tiles[i * _mapSize.y + j]));
        }
    }
    placeObjectsAfterRotation();
}

void Game::convertPositionWithRotation(sf::Vector2i & pos)
{
    bool invertX = (_angle / 90 % 2 == 1) ? true : false;
    bool invertY = (_angle / 180 % 2 == 1) ? true : false;

    if (invertX)
    {
//        pos.x = _mapSize.x - 1 - pos.x;
        auto temp = pos.x;
        pos.x = pos.y;
        pos.y = _mapSize.x - 1 - temp;
    }
    if (invertY)
    {
        pos.x = _mapSize.x - 1 - pos.x;
        pos.y = _mapSize.y - 1 - pos.y;
    }
}

void Game::convertPositionWithRotation(sf::Vector2f & pos)
{
    bool invertX = (_angle / 90 % 2 == 1) ? true : false;
    bool invertY = (_angle / 180 % 2 == 1) ? true : false;

    if (invertX)
    {
//        pos.x = _mapSize.x - 1 - pos.x;
        auto temp = pos.x;
        pos.x = pos.y;
        pos.y = _mapSize.x - 1 - temp;
    }
    if (invertY)
    {
        pos.x = _mapSize.x - 1 - pos.x;
        pos.y = _mapSize.y - 1 - pos.y;
    }
}

void Game::placeObjectsAfterRotation()
{
    for (auto & tile : _tiles)
    {
        auto pos = tile.pos;
        convertPositionWithRotation(pos);
        sf::Vector2f newPos = {(float)_tileWidth / 2, (float)_tileHeight / 2};
        newPos.x += pos.x * _tileWidth;
        newPos.y += pos.y * _tileHeight;
        tile.moveTo(newPos.x, newPos.y);
    }

    for (auto & player : _players)
    {
        auto pos = player.pos;
        convertPositionWithRotation(pos);
        sf::Vector2f newPos = {(float)_tileWidth / 2, (float)_tileHeight / 2};
        newPos.x += pos.x * _tileWidth;
        newPos.y += pos.y * _tileHeight;
        auto actualPos = player.getPosition();
        actualPos.x -= _tileWidth / 2;
        actualPos.y -= _tileHeight / 2;
        actualPos.x /= _tileWidth;
        actualPos.y /= _tileHeight;
        convertPositionWithRotation(actualPos);
        player.rotationMove(actualPos);
        player.moveTo(newPos.x, newPos.y, player.progressiveMoveTime);
        player.adaptToOrientation(_orientation);
    }
}

void Game::placeNewPlayer()
{
    auto & player = _players.back();
    auto pos = player.pos;
    convertPositionWithRotation(pos);
    sf::Vector2f newPos = {(float)_tileWidth / 2, (float)_tileHeight / 2};
    newPos.x += pos.x * _tileWidth;
    newPos.y += pos.y * _tileHeight;
    player.moveTo(newPos);
    player.adaptToOrientation(_orientation);
}

void Game::placeNewEgg()
{
    auto & player = _eggs.back();
    auto pos = player.pos;
    convertPositionWithRotation(pos);
    sf::Vector2f newPos = {(float)_tileWidth / 2, (float)_tileHeight / 2};
    newPos.x += pos.x * _tileWidth;
    newPos.y += pos.y * _tileHeight;
    player.moveTo(newPos);
}

void Game::placeCamera(ZappyRenderWindow & window)
{
    auto view = window.getView();
    auto center = view.getCenter();
    auto pos = _cameraPosition;

    if (!cameraTarget())
    {
        int rightLimit = _mapSize.x - ((window.getView().getSize().x / _tileWidth));
        int downLimit = _mapSize.y - ((window.getView().getSize().y / _tileHeight));
        if ((int)(window.getView().getSize().x / _tileWidth) * _tileWidth != window.getView().getSize().x)
            ++rightLimit;
        if ((int)(window.getView().getSize().y / _tileHeight) * _tileHeight != window.getView().getSize().y)
            ++downLimit;

        bool invertX = (_angle / 90 % 2 == 1) ? true : false;
        bool invertY = (_angle / 180 % 2 == 1) ? true : false;

        if (invertX)
        {
    //        pos.x = _mapSize.x - 1 - pos.x;
            auto temp = pos.x;
            pos.x = pos.y;
            pos.y = _mapSize.x - 1 - temp;
        }
        if (invertY)
        {
            pos.x = _mapSize.x - 1 - pos.x;
            pos.y = _mapSize.y - 1 - pos.y;
        }

        center.x = - (_tileWidth / 2) + (_tileWidth * (pos.x + 1));
        center.y = - (_tileHeight / 2) + (_tileHeight * (pos.y + 1));
    }
    else
    {
        gameMutex.lock(LINE());
        center.x = cameraTarget()->getPosition().x;
        center.y = cameraTarget()->getPosition().y;
        gameMutex.unlock();
    }

    view.setCenter(center);
    window.setView(view);
    _background.setPosition((int)center.x, (int)center.y);
}

void Game::moveCameraTo(ZappyRenderWindow & window, const sf::Vector2i & vec) { moveCameraTo(window, vec.x, vec.y); }
void Game::moveCameraTo(ZappyRenderWindow & window, int x, int y)
{
    _cameraPosition.x = x;
    _cameraPosition.y = y;
    placeCamera(window);
    _cursor.updatePosition(window);
}

void Game::moveCamera(ZappyRenderWindow & window, Direction direction)
{
    if (cameraTarget())
    {
        _cameraPosition.x = cameraTarget()->pos.x;
        _cameraPosition.y = cameraTarget()->pos.y;
    }

    auto directionFinale = _angle + (90 * (int)direction);

    if (directionFinale >= 360)
        directionFinale -= 360;

    if (_angle == 90)
    {
        if (directionFinale == 0)
            _cameraPosition.y -= 1;
        else if (directionFinale == 180)
            _cameraPosition.y += 1;
        else if (directionFinale == 270)
            _cameraPosition.x += 1;
        else if (directionFinale == 90)
            _cameraPosition.x -= 1;
    }
    else if (_angle == 180)
    {
        if (directionFinale == 0)
            _cameraPosition.y += 1;
        else if (directionFinale == 180)
            _cameraPosition.y -= 1;
        else if (directionFinale == 270)
            _cameraPosition.x -= 1;
        else if (directionFinale == 90)
            _cameraPosition.x += 1;
    }
    else if (_angle == 270)
    {
        if (directionFinale == 0)
            _cameraPosition.y -= 1;
        else if (directionFinale == 180)
            _cameraPosition.y += 1;
        else if (directionFinale == 270)
            _cameraPosition.x += 1;
        else if (directionFinale == 90)
            _cameraPosition.x -= 1;
    }
    else
    {
        if (directionFinale == 0)
            _cameraPosition.y += 1;
        else if (directionFinale == 180)
            _cameraPosition.y -= 1;
        else if (directionFinale == 270)
            _cameraPosition.x -= 1;
        else if (directionFinale == 90)
            _cameraPosition.x += 1;
    }

    if (_cameraPosition.y < 0) {
        _cameraPosition.y = _mapSize.y - 1;
    } else if (_cameraPosition.y >= _mapSize.y) {
        _cameraPosition.y = 0;
    } else if (_cameraPosition.x < 0) {
        _cameraPosition.x = _mapSize.x - 1;
    } else if (_cameraPosition.x >= _mapSize.x) {
        _cameraPosition.x = 0;
    }

    for (auto & tile : _tiles)
    {
        if (tile.pos.x == _cameraPosition.x && tile.pos.y == _cameraPosition.y)
        {
            focusCameraOn(&tile, window);
            break;
        }
    }
}

void Game::rotate(Direction direction, ZappyRenderWindow & window)
{
    if (direction == Direction::RIGHT)
    {
        _angle += 90;
        if (_angle >= 360)
            _angle -= 360;
    }
    else if (direction == Direction::LEFT)
    {
        _angle -= 90;
        if (_angle < 0)
            _angle += 360;
    }
    else
        return;

    if (_angle == 0)
        _orientation = PlayerData::Orientation::NORTH;
    else if (_angle == 90)
        _orientation = PlayerData::Orientation::EAST;
    else if (_angle == 180)
        _orientation = PlayerData::Orientation::SOUTH;
    else if (_angle == 270)
        _orientation = PlayerData::Orientation::WEST;
    _compass.goToVFrame((int)(_orientation) - 1);

    placeObjectsAfterRotation();
    placeCamera(window);
}

void Game::focusCameraOn(Object * object, ZappyRenderWindow & window)
{
    _cameraTarget = object;
    placeCamera(window);
    _cursor.updatePosition(window);

    updatePanelInfos();
}
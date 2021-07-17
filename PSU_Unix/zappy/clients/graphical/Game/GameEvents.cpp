/*
** By Kevin Pruvost, May 2020
** Game.cpp
** File description:
** game
*/

#include "Game.hpp"

static std::mutex mutex;

int Game::computeEvents(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client)
{
    static const std::map<Client::GraphEvent, void (Game::*)(ZappyRenderWindow &, sf::Event &, GraphicalClient &)> funcs = {
        {Client::GraphEvent::BCT, &Game::eventBct},
        {Client::GraphEvent::TNA, &Game::eventTna},
        {Client::GraphEvent::PNW, &Game::eventPnw},
        {Client::GraphEvent::PPO, &Game::eventPpo},
        {Client::GraphEvent::PLV, &Game::eventPlv},
        {Client::GraphEvent::PIN, &Game::eventPin},
        {Client::GraphEvent::PDR, &Game::eventPdr},
        {Client::GraphEvent::PGT, &Game::eventPgt},
        {Client::GraphEvent::SGT, &Game::eventSgt},
        {Client::GraphEvent::SST, &Game::eventSgt},
        {Client::GraphEvent::SEG, &Game::eventSeg},
        {Client::GraphEvent::SMG, &Game::eventSmg},
        {Client::GraphEvent::ENW, &Game::eventEnw},
        {Client::GraphEvent::EHT, &Game::eventEht},
        {Client::GraphEvent::EBO, &Game::eventEbo},
        {Client::GraphEvent::PFK, &Game::eventPfk},
        {Client::GraphEvent::PEX, &Game::eventPex},
        {Client::GraphEvent::PBC, &Game::eventPbc},
        {Client::GraphEvent::PIC, &Game::eventPic},
        {Client::GraphEvent::PIE, &Game::eventPie},
        {Client::GraphEvent::PDI, &Game::eventPdi},
        {Client::GraphEvent::EDI, &Game::eventEdi}
    };

    if (!client._graphEvents.empty())
    {
        if (client._graphEvents.size() != client._clientDatas.size())
        {
            //gameMutex.unlock();
            throw EXCEPTION("Graph Event Bug.");
        }
        while (!client._graphEvents.empty())
        {
        gameMutex.lock(LINE());
            auto graphEvent = client._graphEvents[0];

            try {
                if (funcs.find(graphEvent) != funcs.end())
                    (this->*funcs.at(graphEvent))(window, event, client);
            } catch (const std::exception & e) {
                std::cerr << "Crashed at event " << graphEvent << " : " << e.what() << std::endl;
                gameMutex.unlock();
                exit(EXIT_FAILURE);
            }
            client._graphEvents.eraseAt(0);
            client._clientDatas.eraseAt(0);
        gameMutex.unlock();
        }
    }
    return EXIT_SUCCESS;
}

void Game::eventBct(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client)
{
    auto & tile = _tilesByPosition.at(client._clientDatas[0].position.x).at(client._clientDatas[0].position.y).get();
    tile.inventory = client._tilesContent[tile.pos.x][tile.pos.y].inventory;
}

sf::Color Game::generateRandomSfColor()
{
    static KVector<sf::Color> colorsTaken;
    bool good = false;
    size_t loops = 0;

    while (1)
    {
        if (loops >= 100)
            throw EXCEPTION("Cannot find a new team color different enough from other teams.");
        ++loops;
        colorsTaken.emplace_back();
        auto random = rand() % 3;
        sf::Uint8 randomGap = rand() % 10;
        if (random == 0)
            colorsTaken.back().r = 255 - randomGap;
        else if (random == 1)
            colorsTaken.back().g = 255 - randomGap;
        else if (random == 2)
            colorsTaken.back().b = 255 - randomGap;
        if (rand() % 2 == 0)
        {
            if (random == 0)
            {
                colorsTaken.back().b = randomGap;
                colorsTaken.back().g = rand() % 256;
            }
            else if (random == 1)
            {
                colorsTaken.back().r = randomGap;
                colorsTaken.back().b = rand() % 256;
            }
            else if (random == 2)
            {
                colorsTaken.back().g = randomGap;
                colorsTaken.back().r = rand() % 256;
            }
        }
        else
        {
            if (random == 0)
            {
                colorsTaken.back().g = 0;
                colorsTaken.back().b = rand() % 256;
            }
            else if (random == 1)
            {
                colorsTaken.back().b = 0;
                colorsTaken.back().r = rand() % 256;
            }
            else if (random == 2)
            {
                colorsTaken.back().r = 0;
                colorsTaken.back().g = rand() % 256;
            }
        }
        for (size_t i = 0; i < colorsTaken.size(); ++i)
        {
            int gap = 0;
            if (i == colorsTaken.size() - 1)
                good = true;
            gap += abs(colorsTaken[i].r - colorsTaken.back().r);
            gap += abs(colorsTaken[i].g - colorsTaken.back().g);
            gap += abs(colorsTaken[i].b - colorsTaken.back().b);
            if (gap <= 150)
                break;
        }
        if (good)
            break;
        colorsTaken.removeLast();
    }
    return colorsTaken.back();
}

void Game::eventTna(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client)
{
    _teamsColor.insert({client._clientDatas[0].string, generateRandomSfColor()});
    addToBottomBar(client._clientDatas[0].string);
}

void Game::eventPnw(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client)
{
    auto data = client._clientDatas[0];
    _players.emplace_back(data.playerData.position.x, data.playerData.position.y,
                          data.playerData.id, data.playerData.level);
    _players.back().orientation = data.playerData.orientation;
    _players.back().level = data.playerData.level;
    _players.back().teamName = data.playerData.teamName;
    if (_teamsColor.find(data.playerData.teamName) != _teamsColor.end())
        _players.back().setColor(_teamsColor.at(data.playerData.teamName));
    placeNewPlayer();
    gameMutex.unlock();
    client.getPlayerInventory(data.playerData.id);
    gameMutex.lock(LINE());
    addToBottomBar(&_players.back());
}

void Game::eventSgt(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client)
{
    _timeUnit = client._clientDatas[0].integer;
    _timeText._textObjects[0].setString(STR(_timeUnit));
}

void Game::eventSeg(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client)
{
    _gameEnded = true;
    _winningTeam = client._clientDatas[0].string;
}

void Game::eventSmg(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client)
{
    _serverMsg += ((_serverMsg.empty()) ? "" : "\n") + client._clientDatas[0].string;
}

void Game::eventEnw(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client)
{
    int id = client._clientDatas[0].integer;
    std::string teamName;

    for (auto & player : _players)
    {
        if (player.id == id)
        {
            player.isLayingEgg = false;
            teamName = player.teamName;
            break;
        }
    }

    _eggs.emplace_back(client._clientDatas[0].playerData.position.x,
                       client._clientDatas[0].playerData.position.y,
                       client._clientDatas[0].playerData.id,
                       client._clientDatas[0].integer);

    _eggs.back().teamName = teamName;
    if (_teamsColor.find(teamName) != _teamsColor.end())
        _eggs.back().setColor(_teamsColor.at(teamName));
    placeNewEgg();
}

void Game::eventEht(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client)
{
    int id = client._clientDatas[0].integer;

    for (auto & egg : _eggs)
    {
        if (egg.id == id)
        {
            egg.animate(Object::AnimateOptions::EndsOnLastFrame, 0.5, 2);
            break;
        }
    }
}

void Game::eventEbo(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client)
{
    int id = client._clientDatas[0].integer;

    for (size_t i = 0; i < _eggs.size(); ++i)
    {
        if (_eggs[i].id == id)
        {
            _eggs[i].level = 1;
            _eggs[i].setVisible(false);
//            _players.emplace_back(_eggs[i]);
//            placeNewPlayer();
//            gameMutex.unlock();
//            client.getPlayerInventory(_players.back().id);
//            gameMutex.lock(LINE());
            break;
        }
    }
}

void Game::eventEdi(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client)
{
    int id = client._clientDatas[0].integer;

    for (size_t i = 0; i < _eggs.size(); ++i)
    {
        if (_eggs[i].id == id)
        {
            if (_cameraTarget == _eggs[i])
            {
                _cameraPosition.x = _eggs[i].pos.x;
                _cameraPosition.y = _eggs[i].pos.y;
                for (auto & tile : _tiles)
                {
                    if (tile.pos.x == _cameraPosition.x && tile.pos.y == _cameraPosition.y)
                    {
                        gameMutex.unlock();
                        focusCameraOn(&tile, window);
                        gameMutex.lock();
                        break;
                    }
                }
            }
            _eggs.removeAt(i);
            break;
        }
    }
}

void Game::eventPdr(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client)
{
    int id = client._clientDatas[0].integer;
    int x = -1;
    int y = -1;

//    if (client._clientDatas[0].dataSupp.size() != 1)
//        throw EXCEPTION("Pdr event bug.");

    for (auto & player : _players)
    {
        if (player.id == id)
        {
            x = player.pos.x;
            y = player.pos.y;
            if (client._clientDatas[0].dataSupp[0].integer > 6)
            {
                throw EXCEPTION("Wrong inventory index.");
                return;
            }
            --player.inventory[client._clientDatas[0].dataSupp[0].integer];
            gameMutex.unlock();
            client.getPlayerInventory(player.id);
            client.getTileContent(x, y);
            gameMutex.lock(LINE());
            break;
        }
    }

    for (auto & tile : _tiles)
    {
        if (tile.pos.x == x && tile.pos.y == y)
        {
            ++tile.inventory[client._clientDatas[0].dataSupp[0].integer];
            break;
        }
    }
}

void Game::eventPgt(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client)
{
    int id = client._clientDatas[0].integer;
    int x = -1;
    int y = -1;

    for (auto & player : _players)
    {
        if (player.id == id)
        {
            x = player.pos.x;
            y = player.pos.y;
            if (client._clientDatas[0].dataSupp[0].integer > 6)
            {
                throw EXCEPTION("Wrong inventory index.");
                return;
            }
            ++player.inventory[client._clientDatas[0].dataSupp[0].integer];
            gameMutex.unlock();
            client.getPlayerInventory(player.id);
            client.getTileContent(x, y);
            gameMutex.lock(LINE());
            break;
        }
    }

    for (auto & tile : _tiles)
    {
        if (tile.pos.x == x && tile.pos.y == y)
        {
            --tile.inventory[client._clientDatas[0].dataSupp[0].integer];
            break;
        }
    }
}

void Game::eventPfk(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client)
{
    int id = client._clientDatas[0].integer;

    for (auto & player : _players)
    {
        if (player.id == id)
        {
            player.isLayingEgg = true;
            break;
        }
    }
}

void Game::eventPpo(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client)
{
    if (client._clientDatas[0].boolean)
        return;

    auto & playerToCpy = client._clientDatas[0].playerData;

    for (auto & player : _players)
    {
        if (player.id == playerToCpy.id)
        {
            player.pos.x = playerToCpy.position.x;
            player.pos.y = playerToCpy.position.y;
            if (_cameraTarget == player)
                _cameraTarget = player;
            sf::Vector2f newPos = {(float)_tileWidth / 2, (float)_tileHeight / 2};
            auto pos = player.pos;
            convertPositionWithRotation(pos);
            newPos.x += pos.x * _tileWidth;
            newPos.y += pos.y * _tileHeight;
            player.moveTo(newPos, 1);
            player.orientation = playerToCpy.orientation;
            player.adaptToOrientation(_orientation);
            player.isExpulsed = false;
            break;
        }
    }
}

void Game::eventPlv(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client)
{
    if (!client._clientDatas[0].boolean)
        return;

    auto & playerToCpy = client._clientDatas[0].playerData;

    for (auto & player : _players)
    {
        if (player.id == playerToCpy.id)
        {
            player.setLevel(playerToCpy.level);
            refreshIcons(player.id, player.textureId);
            break;
        }
    }
}

void Game::eventPin(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client)
{
    if (!client._clientDatas[0].boolean)
        return;

    auto & playerToCpy = client._clientDatas[0].playerData;

    for (auto & player : _players)
    {
        if (player.id == playerToCpy.id)
        {
            player = playerToCpy.inventory;
            break;
        }
    }
}

void Game::eventPex(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client)
{
    int id = client._clientDatas[0].integer;

    for (auto & player : _players)
    {
        if (player.id == id)
        {
            player.isExpulsed = true;
            gameMutex.unlock();
            client.getPlayerPosition(player.id);
            gameMutex.lock(LINE());
            break;
        }
    }
}

void Game::eventPbc(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client)
{
    int id = client._clientDatas[0].integer;

    for (auto & player : _players)
    {
        if (player.id == id)
        {
            player.broadcastMessage = client._clientDatas[0].string;
            break;
        }
    }
}

void Game::eventPdi(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client)
{
    int id = client._clientDatas[0].integer;

    for (size_t i = 0; i < _players.size(); ++i)
    {
        if (_players[i].id == id)
        {
            if (_cameraTarget == _players[i])
            {
                _cameraPosition.x = _players[i].pos.x;
                _cameraPosition.y = _players[i].pos.y;
                for (auto & tile : _tiles)
                {
                    if (tile.pos.x == _cameraPosition.x && tile.pos.y == _cameraPosition.y)
                    {
                        gameMutex.unlock();
                        focusCameraOn(&tile, window);
                        gameMutex.lock();
                        break;
                    }
                }
                for (auto & incantation : _incantations)
                {
                    for (size_t j = 0; j < incantation.size(); ++j)
                    {
                        if (incantation[j] == _players[i])
                        {
                            incantation.removeAt(j);
                            break;
                        }
                    }
                }
            }
            removeFromBottomBar(&_players[i], window);
            _players.removeAt(i);
            break;
        }
    }
}

void Game::eventPic(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client)
{
    _incantations.emplace_back(client._clientDatas[0].position);

    for (const auto id : client._clientDatas[0].dataSupp)
    {
        for (auto & player : _players)
        {
            if (id.integer == player.id)
            {
                _incantations.back().push_back(Target(player));
                break;
            }
        }
    }
    _incantations.back().startIncantation(_players, _eggs, _tiles);
    for (auto & player : _incantations.back())
        refreshIcons(player.id, player.get(_players, _eggs, _tiles)->textureId);}

void Game::eventPie(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client)
{
    for (size_t i = 0; i < _incantations.size(); ++i)
    {
        if (_incantations[i].position == client._clientDatas[0].position)
        {
            _incantations[i].endIncantation(client._clientDatas[0].boolean, _players, _eggs, _tiles);
            for (auto & player : _incantations[i])
                refreshIcons(player.id, player.get(_players, _eggs, _tiles)->textureId);
            _incantations.removeAt(i);
            break;
        }
    }
}
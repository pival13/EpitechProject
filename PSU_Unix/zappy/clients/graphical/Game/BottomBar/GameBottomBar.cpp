/*
** By Kevin Pruvost, June 2020
** GameBottomBar
** File description:
** game
*/

#include "Game.hpp"

void Game::addToBottomBar(Mob * player)
{
    if (_playersButtons.find(player->teamName) == _playersButtons.end())
    {
        throw EXCEPTION("Trying to add player without team. (" + STR(player->id) + ":" + player->teamName + ")");
        return;
    }

    auto & array = _playersButtons.at(player->teamName);

    if (array.empty())
        array.emplace_back();
    else if (array.back().size() >= MAX_PLAYERS_LINE_SIZE)
        array.emplace_back();
    array.back().push_back(PlayerButton(player->id, player->textureId));

    checkForArrowsBottomBar();
    checkPlayerCount();
}

void Game::addToBottomBar(const std::string & teamName)
{
    if (_teamsColor.find(teamName) == _teamsColor.end())
    {
        throw EXCEPTION("No color associated to " + teamName);
        return;
    }

    if (_teamsButtons.empty())
    {
        _teamsButtons.emplace_back();
        _displayTarget.index = _teamsButtons.size() - 1;
        _displayTarget.teamName = "";
    }
    else if (_teamsButtons.back().size() >= MAX_TEAMS_LINE_SIZE)
        _teamsButtons.emplace_back();
    _teamsButtons.back().push_back(TeamButton(teamName, _teamsColor.at(teamName)));
    _playersButtons.insert({teamName, {}});

    checkForArrowsBottomBar();
    checkPlayerCount();
}

void Game::removeFromBottomBar(Mob * player, ZappyRenderWindow & window)
{
    bool found = false;
    for (auto & pair : _playersButtons)
    {
        for (auto & line : pair.second)
        {
            for (size_t i = 0; i < line.size(); ++i)
            {
                if (line[i]._playerId == player->id)
                {
                    found = true;
                    line.removeAt(i);
                    break;
                }
            }
            if (found)
                break;
        }
        if (found)
            break;
    }

    formatBottomBar();
}

void Game::removeFromBottomBar(const std::string & teamName)
{
    if (teamFocused == teamName)
        goToTeamsBar();

    bool found = false;
    for (auto & line : _teamsButtons)
    {
        for (size_t i = 0; i < line.size(); ++i)
        {
            if (line[i].getString() == teamName)
            {
                found = true;
                line.removeAt(i);
                break;
            }
        }
        if (found)
            break;
    }
    if (_playersButtons.find(teamName) != _playersButtons.end())
        _playersButtons.erase(teamName);

    formatBottomBar();
}

void Game::formatBottomBar()
{
    if (!_teamsButtons.empty())
    {
        for (size_t i = _teamsButtons.size() - 1; i > 0; --i)
        {
            if (_teamsButtons[i].empty())
            {
                if (_displayTarget.index == (int)i && _displayTarget.teamName.empty())
                    _displayTarget.index = i - 1;
                _teamsButtons.removeAt(i);
            }
            else
            {
                while (_teamsButtons[i - 1].size() < MAX_TEAMS_LINE_SIZE && !_teamsButtons[i].empty())
                {
                    _teamsButtons[i - 1].push_back(_teamsButtons[i].front());
                    _teamsButtons[i].removeAt(0);
                }
                if (_teamsButtons[i].empty())
                {
                    if (_displayTarget.index == (int)i && _displayTarget.teamName.empty())
                        _displayTarget.index = i - 1;
                    _teamsButtons.removeAt(i);
                }
            }
        }
    }

    for (auto & pair : _playersButtons)
    {
        auto & array = pair.second;

        if (array.empty())
            continue;
        for (size_t i = array.size() - 1; i > 0; --i)
        {
            if (array[i].empty())
            {
                if (_displayTarget.index == (int)i && _displayTarget.teamName == pair.first)
                    _displayTarget.index = i - 1;
                array.removeAt(i);
            }
            else
            {
                while (array[i - 1].size() < MAX_TEAMS_LINE_SIZE && !array[i].empty())
                {
                    array[i - 1].push_back(array[i].front());
                    array[i].removeAt(0);
                }
                if (array[i].empty())
                {
                    if (_displayTarget.index == (int)i && _displayTarget.teamName == pair.first)
                        _displayTarget.index = i - 1;
                    array.removeAt(i);
                }
            }
        }
    }

    checkForArrowsBottomBar();
    checkPlayerCount();
}

void Game::refreshBottomBar()
{
    for (auto & teamPair : _teamsColor)
    {
        auto & teamName = teamPair.first;

        if (_playersButtons.find(teamName) == _playersButtons.end())
        { // If team already exists.
            if (_teamsButtons.back().size() >= MAX_TEAMS_LINE_SIZE)
                _teamsButtons.emplace_back();
            _teamsButtons.back().push_back(TeamButton(teamName, teamPair.second));
            _playersButtons.insert({teamName, {}});

            for (auto & player : _players)
            {
                if (player.teamName == teamName)
                {
                    if (_playersButtons.at(teamName).size() >= MAX_PLAYERS_LINE_SIZE)
                        _playersButtons.at(teamName).emplace_back();
                    _playersButtons.at(teamName).back().push_back(PlayerButton(player.id, player.textureId));
                }
            }
        }
        else
        { // If team just appeared.
            auto & array = _playersButtons.at(teamName);

            for (auto & player : _players)
            {
                bool found = false;
                for (auto & line : array)
                {
                    for (auto & button : line)
                    {
                        if (button._playerId == player.id)
                        {
                            found = true;
                            break;
                        }
                    }
                    if (found)
                        break;
                }
                if (found)
                    continue;

                if (player.teamName == teamName)
                {
                    if (_playersButtons.at(teamName).size() >= MAX_PLAYERS_LINE_SIZE)
                        _playersButtons.at(teamName).emplace_back();
                    _playersButtons.at(teamName).back().push_back(PlayerButton(player.id, player.textureId));
                }
            }
        }
    }
    formatBottomBar();
}

void Game::resetBottomBar()
{
    _teamsButtons.clear();
    _playersButtons.clear();

    _teamsButtons.emplace_back();
    _displayTarget.teamName = "";
    _displayTarget.index = _teamsButtons.size() - 1;
    for (auto & teamPair : _teamsColor)
    {
        auto & teamName = teamPair.first;

        if (_teamsButtons.back().size() >= MAX_TEAMS_LINE_SIZE)
            _teamsButtons.emplace_back();
        _teamsButtons.back().push_back(TeamButton(teamName, teamPair.second));
        _playersButtons.insert({teamName, {}});
        for (auto & player : _players)
        {
            if (player.teamName == teamName)
            {
                if (_playersButtons.at(teamName).size() >= MAX_PLAYERS_LINE_SIZE)
                    _playersButtons.at(teamName).emplace_back();
                _playersButtons.at(teamName).back().push_back(PlayerButton(player.id, player.textureId));
            }
        }
    }
    checkPlayerCount();
}

bool Game::bottomBarInteractions(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client)
{
    if (_cursor.pointedObject == &_teamsButton)
    {
        goToTeamsBar();
        return true;
    }
    else if (_cursor.pointedObject == &_arrowUp)
    {
        moveDisplayBar(true);
        return true;
    }
    else if (_cursor.pointedObject == &_arrowDown)
    {
        moveDisplayBar(false);
        return true;
    }
    else if (!displayBar()->empty())
    {
        if (displayBarInteractions(window))
            return true;
    }
    return false;
}

bool Game::displayBarInteractions(ZappyRenderWindow & window)
{
    for (auto & button : *displayBar())
    {
        if (_cursor.pointedObject == &button)
        {
            if (button.buttonId == 'p')
            {
                Mob * playerPtr = nullptr;

                for (auto & player : _players)
                {
                    if (player.id == button._playerId)
                    {
                        playerPtr = &player;
                        break;
                    }
                }

                if (playerPtr)
                {
                    focusCameraOn(playerPtr, window);
                    checkCursorHighlight();
                }
            }
            else if (button.buttonId == 't')
            {
                teamFocused = button._textObjects[0].getString();
                if (_playersButtons.find(teamFocused) == _playersButtons.end())
                {
                    throw EXCEPTION("Couldn't find players of the team : " + teamFocused);
                    return false;
                }
                if (_playersButtons.at(teamFocused).empty())
                    _playersButtons.at(teamFocused).emplace_back();
                _displayTarget.index = 0;
                _displayTarget.teamName = teamFocused;
                _playersButton.setVisible(true);
                _arrowBetweenPlayersTeams.setVisible(true);
                checkPlayerCount();
            }
            return true;
        }
    }
    return false;
}

void Game::goToTeamsBar()
{
    teamFocused.clear();
    if (!_teamsButtons.empty())
    {
        _displayTarget.index = 0;
        _displayTarget.teamName = "";
    }
    _arrowBetweenPlayersTeams.setVisible(false);
    _playersButton.setVisible(false);
    checkPlayerCount();
}

void Game::checkForArrowsBottomBar()
{
    if (!displayBar())
        return;

    bool found = false;

    _arrowUp.setVisible(true);
    _arrowDown.setVisible(true);

    if (!_teamsButtons.empty())
    {
        if (_displayTarget.index == 0 && _displayTarget.teamName.empty())
        {
            _arrowUp.setVisible(false);
            found = true;
        }
        if (_displayTarget.index == (int)_teamsButtons.size() - 1 && _displayTarget.teamName.empty())
        {
            _arrowDown.setVisible(false);
            found = true;
        }
    }

    if (found)
        return;

    for (auto & pair : _playersButtons)
    {
        auto & array = pair.second;

        if (!array.empty())
        {
            if (_displayTarget.index == 0 && _displayTarget.teamName == pair.first)
            {
                _arrowUp.setVisible(false);
                found = true;
            }
            if (_displayTarget.index == (int)array.size() - 1 && _displayTarget.teamName == pair.first)
            {
                _arrowDown.setVisible(false);
                found = true;
            }
        }
        if (found)
            break;
    }
}

void Game::checkPlayerCount()
{
    _playersCountPerTeam.clear();

    size_t count = 0;

    for (auto & pair : _playersButtons)
    {
        _playersCountPerTeam.insert({pair.first, {}});
        auto & count = _playersCountPerTeam.at(pair.first);

        for (auto & line : pair.second)
            count += line.size();
    }

    if (!teamFocused.empty())
    {
        if (_playersCountPerTeam.find(teamFocused) == _playersCountPerTeam.end())
        {
            throw EXCEPTION("Player count non existent.");
            return;
        }
        count = _playersCountPerTeam.at(teamFocused);
        _playerCount.setString("Players count for team " + teamFocused + " : " + STR(count));
    }
    else
    {
        for (auto & pair : _playersCountPerTeam)
            count += pair.second;
        _playerCount.setString("Players count : " + STR(count));
    }
}

void Game::moveDisplayBar(bool up)
{
    if (teamFocused.empty())
    {
        for (size_t i = 0; i < _teamsButtons.size(); ++i)
        {
            if (displayBar() == &_teamsButtons[i])
            {
                if (up && i + 1 < _teamsButtons.size())
                {
                    _displayTarget = i + 1;
                    _displayTarget = "";
                    break;
                }
                if (!up && i > 0)
                {
                    _displayTarget = i - 1;
                    _displayTarget = "";
                    break;
                }
            }
        }
    }
    else
    {
        auto & array = _playersButtons.at(teamFocused);

        for (size_t i = 0; i < array.size(); ++i)
        {
            if (displayBar() == &array[i])
            {
                if (up && i + 1 < array.size())
                {
                    _displayTarget = i + 1;
                    _displayTarget = teamFocused;
                    break;
                }
                if (!up && i > 0)
                {
                    _displayTarget = i - 1;
                    _displayTarget = teamFocused;
                    break;
                }
            }
        }
    }
}

void Game::refreshIcons(int id, Constants::TextureId textureId)
{
    for (auto & pair : _playersButtons)
    {
        auto & array = pair.second;

        for (auto & line : array)
        {
            for (auto & button : line)
            {
                if (button._playerId == id)
                {
                    button.setIconTexture(textureId);
                    return;
                }
            }
        }
    }
}
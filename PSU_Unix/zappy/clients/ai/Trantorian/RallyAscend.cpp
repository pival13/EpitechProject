/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Ubuntu]
** File description:
** RallyAscend
*/

#include "../Trantorian.hpp"

void Trantorian::updateGoalRallyAscend()
{
    updateStockRallyAscend();
    prepareTalk("@"+std::to_string(_ascenderToRally)+", I will help you");
    _whatToSay = "@" + std::to_string(_ascenderToRally) + ", I come as soon as possible";
}

void Trantorian::updateStockRallyAscend()
{
    _targetObjects.clear();
    _optionalObjects.clear();
    _wantedObject.clear();

    for (size_t iK = 0; iK < _settings["collectable"].size(); iK++) {
        std::string key = _settings["collectable"][iK].get<std::string>();
        for (size_t i = 0; i != _settings["elevationPath"].size(); i++) {
            if (_settings["elevationPath"][i].contain(key))
                _optionalObjects[key] += _settings["elevationPath"][i][key].get<size_t>() * (i+1 > _currentLevel? 2: 1);
        }
        _optionalObjects[key] -= _optionalObjects[key] > _inventory[key]? _inventory[key]: _optionalObjects[key];
    }
    _optionalObjects["food"] = 30 - (_inventory["food"] > 30? 30: _inventory["food"]);
}

void Trantorian::actionCallbackRallyAscend(AI::FunctionsCode code, bool result)
{
    if (code == Talking || code == CheckingInventory)
        return;
    if (result == false) {
        prepareLook();
        return;   
    }
    if (code == TakingObject)
        updateStockRallyAscend();

    if (!_inIncantation && _inventory["food"] < std::ceil(getActionTime(Incantating)/_settings["timePerFood"].get<double>())+1) {
        prepareTalk("@"+std::to_string(_ascenderToRally)+", I can't help you anymore, sorry.");
        changeCircumstance(GatherObject);
    } else {
        size_t actionNeeded = actionToReach(_targetPos);
        if (actionNeeded == 0) {
            _whatToSay = "@" + std::to_string(_ascenderToRally) + ", here I am.";
            uint8_t n = rand();
            if ((n & 0b1) == 0) prepareLook();
            else if ((n & 0b10) == 0) prepareTurnRight();
            else prepareTurnLeft();
        } else if (actionNeeded > actionToReach(_targetPos, _pos, orientationToVector(0,1))) {
            prepareTurnRight();
        } else if (actionNeeded > actionToReach(_targetPos, _pos, orientationToVector(0,-1))) {
            prepareTurnLeft();
        } else if (!_world.count(_pos+orientationToVector())) {
            prepareLook();
        } else if (isObjectFront(_optionalObjects) && actionToReach(posClosestObject(_optionalObjects, true)) == 0) {
            prepareTake(_wantedObject);
        } else {
            prepareMove();
        }
    }
}

void Trantorian::messageReceivedRallyAscend(AI::Direction /*orig*/, const std::string &msg)
{
    size_t talker = std::stoul(msg);
    std::smatch m;

    if (talker == _ascenderToRally && (msg.find("Failed to level up") != std::string::npos || msg.find("I am now level ") != std::string::npos))
        changeCircumstance(GatherObject);
    if (msg.find(std::to_string(_ascenderToRally) + " is probably dead") != std::string::npos)
        changeCircumstance(GatherObject);
    if (msg.find("I don't need you") != std::string::npos || msg.find("Ascension give up") != std::string::npos)
        changeCircumstance(GatherObject);
    _targetPos = std::find_if(_otherPlayers.begin(), _otherPlayers.end(), [this](const OtherPlayer &pl) { return pl.number == _ascenderToRally; })->pos;
}
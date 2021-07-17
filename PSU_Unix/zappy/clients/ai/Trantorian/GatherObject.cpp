/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Ubuntu]
** File description:
** GatherObject
*/

#include "../Trantorian.hpp"

void Trantorian::updateGoalGatherObject()
{
    Json currentLevelObjectif = _settings["elevationPath"][_currentLevel-1];
    _targetObjects.clear();
    _optionalObjects.clear();
    _wantedObject.clear();

    for (size_t iK = 0; iK < _settings["collectable"].size(); iK++) {
        std::string key = _settings["collectable"][iK].get<std::string>();
        size_t needed = currentLevelObjectif.contain(key)? currentLevelObjectif[key].get<size_t>(): 0;
        size_t inventoryRemoved = std::min(_inventory[key], needed);
        if (needed != 0)
            _targetObjects[key] = needed - inventoryRemoved;
        for (size_t i = _currentLevel; i < _settings["elevationPath"].size(); i++) {
            if (_settings["elevationPath"][i].contain(key))
                _optionalObjects[key] += _settings["elevationPath"][i][key].get<size_t>()/* * (i+1 > _currentLevel? 1: 0)*/;
        }
        _optionalObjects[key] -= _inventory[key] - inventoryRemoved < _optionalObjects[key]? _inventory[key] - inventoryRemoved: _optionalObjects[key];
    }
    if (std::none_of(_targetObjects.begin(), _targetObjects.end(), [](const std::pair<std::string,size_t> &obj) {return obj.first != "food" && obj.second != 0;}))
        changeCircumstance(WaitAscend);
}

void Trantorian::selectNextTargetGatherObject()
{
    inv_t food({ {"food", 1} });
    if (_inventory["food"] < 10 && isObjectFront(_targetObjects+food)) {
        _targetPos = posClosestObject(_targetObjects+food, true);
    } else if (_inventory["food"] >= 10 && isObjectFront(_targetObjects)) {
        _targetPos = posClosestObject(_targetObjects, true);
    } else if (isObjectNear(_targetObjects)) {
        _targetPos = posClosestObject(_targetObjects, false);
    } else if (_inventory["food"] <= 30 && isObjectNear(_optionalObjects+food)) {
        _targetPos = posClosestObject(_optionalObjects+food, false);
    } else if (_inventory["food"] > 30 && isObjectNear(_optionalObjects)) {
        _targetPos = posClosestObject(_optionalObjects, false);
    } else {
        if (_pos > _mapSize || _pos < pos_t({0,0})) {
            pos_t midMap = {_mapSize[0]/2, _mapSize[1]/2};
            if (actionToReach(midMap) > actionToReach(midMap, _pos, orientationToVector(0,1)))
                _targetPos = _pos + orientationToVector(0,1);
            else if (actionToReach(midMap) > actionToReach(midMap, _pos, orientationToVector(0,-1)))
                _targetPos = _pos + orientationToVector(0,-1);
            else
                _targetPos = _pos + orientationToVector(_currentLevel != 1? _currentLevel: _currentLevel+1, 0);    
        } else
            _targetPos = _pos + orientationToVector(_currentLevel != 1? _currentLevel: _currentLevel+1, 0);
        _wantedObject.clear();
    }
}

void Trantorian::actionCallbackGatherObject(FunctionsCode code, bool result)
{
    switch (code) {
    case Looking:
        selectNextTargetGatherObject();
        goToPos(_targetPos);
        break;
    case TakingObject:
        _wantedObject.clear();
        if (result == true) {
            updateGoalGatherObject();
            if (_currentCircumstance != GatherObject) {
                (this->*_actionCallbackCircumstance.at(_currentCircumstance))(TakingObject, true);
            } else {
                selectNextTargetGatherObject();
                if (_wantedObject.empty())
                    prepareLook();
                else
                    goToPos(_targetPos);
            }
        } else
            prepareLook();
        break;
    case Moving:
    case MovingRight:
    case MovingLeft:
        goToPos(_targetPos);
        break;

    case Talking:
    case LayingEgg:
    case CheckingInventory:
        break;

    default:
        std::cerr << "Strange code received: " << code << std::endl;
        prepareLook();
        break;
    }
}

void Trantorian::messageReceivedGatherObject(Direction /*orig*/, const std::string &msg)
{
    if (msg.find("to reach level " + std::to_string(_currentLevel+1)) != std::string::npos && msg.find(" 0 ") == std::string::npos) {
        if (_posSynchronized && _inventory["food"] > std::ceil(getActionTime(Incantating)/_settings["timePerFood"].get<double>()) + 3) {
            _ascenderToRally = std::stoul(msg);
            _targetPos = std::find_if(_otherPlayers.begin(), _otherPlayers.end(), [this](const OtherPlayer &pl) { return pl.number == _ascenderToRally; })->pos;
            changeCircumstance(RallyAscend);
        }
    }
}
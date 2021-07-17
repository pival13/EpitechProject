/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Ubuntu]
** File description:
** RallyLayer
*/

#include "../Trantorian.hpp"

void Trantorian::updateGoalRallyLayer()
{
    _targetObjects.clear();
    _optionalObjects.clear();
    _targetPos = _pos;

    for (size_t iK = 0; iK < _settings["collectable"].size(); iK++) {
        std::string key = _settings["collectable"][iK].get<std::string>();
        for (size_t i = 0; i != _settings["elevationPath"].size(); i++)
            if (_settings["elevationPath"][i].contain(key))
                _optionalObjects[key] += _settings["elevationPath"][i][key].get<size_t>() * (_currentLevel-1 < i? 2: 1);
    }
    _optionalObjects["food"] = 30;
    _actionPlannedRallyLayer = true;
}

void Trantorian::goToTargetRallyLayer()
{
    if (_inventory["food"] < 5) {
        if (_world[_pos].count("food") && _world[_pos]["food"] > 0)
            prepareTake("food");
        else if (isObjectNear("food")) {
            goToPos(posClosestObject("food", false));
        } else
            if (isAtOriginLook())
                prepareMove();
            else
                prepareLook();
    } else  {
        size_t actionNeeded = actionToReach(_targetPos);
        auto itObj = std::find_if(_optionalObjects.begin(), _optionalObjects.end(), [this](const obj_t &obj) {
            return obj.second > 0 && _world.count(_pos) && _world[_pos].count(obj.first) && _world[_pos][obj.first] > 0;
        });
        auto itPly = std::find_if(_world.begin(), _world.end(), [this](const std::pair<pos_t,inv_t> &cell) {
            return cell.first != _pos && cell.second.count("player") && cell.second.at("player") > 0;
        });
        if (!_world.count(_pos)) {
            prepareTalk("Where are you, @Layer");
            prepareLook();
        } else if (_world[_pos].count("player") && _world[_pos]["player"] > 1 && !_isWithPlayerRallyLayer) {
            _isWithPlayerRallyLayer = true;
            _actionPlannedRallyLayer = false;
            prepareTalk("Are you here, @Layer");
        } else if (itObj != _optionalObjects.end()) {
            prepareTake(itObj->first);
        } else if (itPly != _world.end() && _targetPos != itPly->first) {
            _targetPos = itPly->first;
            goToTargetRallyLayer();
        } else if (actionNeeded > actionToReach(_targetPos, _pos, orientationToVector(0,1))) {
            prepareTurnRight();
        } else if (actionNeeded > actionToReach(_targetPos, _pos, orientationToVector(0,-1))) {
            prepareTurnLeft();
        } else if (_pos == _targetPos) {
            _actionPlannedRallyLayer = false;
            prepareTalk("Where are you, @Layer");
        } else {
            prepareMove();
        }
    }
}

void Trantorian::actionCallbackRallyLayer(AI::FunctionsCode code, bool result)
{
    if (code == CheckingInventory || code == Talking)
        return;
    if (code == Looking)
        _isWithPlayerRallyLayer = false;
    if (code == TakingObject && result == true)
        _optionalObjects[callbackedActionParameter] -= 1;
    if (result == false)
        prepareLook();
    else
        goToTargetRallyLayer();
}

void Trantorian::beenEjectRallyLayer()
{
    _ejectedLastRL = true;
}

void Trantorian::messageReceivedRallyLayer(AI::Direction orig, const std::string &msg)
{
    std::smatch match;
    if (_ejectedLastRL && std::regex_search(msg, match, std::regex("You were at \\{(-?\\d+),(-?\\d+)\\}, you are at \\{(-?\\d+),(-?\\d+)\\}"))) {
        _posSynchronized = true;
        _pos = pos_t({stol(match[3].str()), stol(match[4].str())});
        if (orig == Back) //TODO Improve
            _orientation = North;
        else if (orig == Front)
            _orientation = South;
        else if (orig == Right)
            _orientation = East;
        else if (orig == Left)
            _orientation = West;
        prepareGetInventory();
        changeCircumstance(GatherObject);
        if (!_actionPlannedRallyLayer)
            prepareLook();
    } else if (msg.find("I am the Layer") != std::string::npos) {
        if (orig == Self)
            prepareTalk("I'm here, @Layer");
        else {
            _targetPos = _pos + directionToWorldMax(orig);
            if (!_actionPlannedRallyLayer)
                goToTargetRallyLayer();
            _actionPlannedRallyLayer = true;
        }
        _ejectedLastRL = false;
    }
}

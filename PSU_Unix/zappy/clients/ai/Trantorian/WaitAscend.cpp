/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Ubuntu]
** File description:
** WaitAscent
*/

#include "../Trantorian.hpp"

void Trantorian::updateGoalWaitAscend()
{
    Json currentLevelObjectif = _settings["elevationPath"][_currentLevel-1];
    _targetObjects.clear();
    _optionalObjects.clear();
    _givingUpWaitAscend = false;
    for (const std::string &key : currentLevelObjectif.keys())
        _targetObjects[key] = currentLevelObjectif[key].get<size_t>();
    _supportingAlliesAscend.clear();
    _supportingAlliesAscend[_personalNumber] = _pos;

    if (std::any_of(_targetObjects.begin(), _targetObjects.end(), [this](const obj_t &pair) {
        return pair.first != "player" && (!_inventory.count(pair.first) || _inventory[pair.first] < pair.second);
    }))
        changeCircumstance(GatherObject);
}

void Trantorian::goToClosestFood()
{
    if (isObjectNear("food")) {
        _targetPos = posClosestObject("food", false);
        goToPos(_targetPos);
    } else if (!_world.count(_pos+orientationToVector())) {
        prepareLook();
    } else {
        prepareMove();
    }
}

void Trantorian::askHelpWaitAscend()
{
    std::stringstream ss;
    ss << "I need " << _targetObjects["player"]-_supportingAlliesAscend.size() << " more peoples to reach level " << _currentLevel +1;
    _whatToSay = ss.str();
    if ((rand() & 0b1) == 0)
        prepareLook();
    else
        prepareTurnRight();
}

bool Trantorian::isCellReadyAscend()
{
    return _world.count(_pos) && std::all_of(_targetObjects.begin(), _targetObjects.end(), [this](const obj_t &obj) {
        return (_world[_pos].count(obj.first) && _world[_pos][obj.first] >= obj.second) || obj.second == 0;
    });
}

void Trantorian::prepareCellAscend()
{
    if (!_world.count(_pos)) {
        prepareLook();
        return;
    }
    auto it = std::find_if(_targetObjects.begin(), _targetObjects.end(), [this](const obj_t &obj) {
        return obj.first != "player" && !((_world[_pos].count(obj.first) && _world[_pos][obj.first] >= obj.second) || obj.second == 0);
    });
    if (it == _targetObjects.end())
        prepareLook();
    else
        prepareDrop(it->first);
}

void Trantorian::waitForAscendWaitAscend(FunctionsCode code)
{
    if (!_givingUpWaitAscend && std::any_of(_targetObjects.begin(), _targetObjects.end(), [this](const obj_t &pair) {
        return pair.first != "player" && (_world[_pos].count(pair.first) ? _world[_pos][pair.first] : 0) + _inventory[pair.first] < pair.second;
    })) {
        if (code == Looking)
            _givingUpWaitAscend = true;
        prepareLook();
    } else if (std::any_of(_otherPlayers.begin(), _otherPlayers.end(), [this](const OtherPlayer &pl) { return pl.incantate && pl.pos == _pos; })
        || _pos == pos_t({0,0})) {
        uint8_t n = rand() % 0b100;
        if (n & 0b1)
            prepareMove();
        else if (n & 0b10)
            prepareTurnLeft();
        else
            prepareTurnRight();
    } else if (long(_targetObjects["player"]) > std::count_if(_supportingAlliesAscend.begin(), _supportingAlliesAscend.end(), 
        [this](const std::pair<size_t,pos_t> &allies) { return allies.second == _pos; })) {
        askHelpWaitAscend();
    } else {
        _whatToSay = "Ready to ascend";
        if (!isCellReadyAscend()) {
            prepareCellAscend();
        } else {
            if (code == Looking)
                addActionToDo([this]() {
                    trantorianTalk("Begining ascension to level " + std::to_string(_currentLevel+1));
                    incantate();
                    look();
                });
            else
                prepareLook();
        }
    }
}

void Trantorian::givingUpAscendWaitAscend()
{
    if (_world.count(_pos) && std::any_of(_world[_pos].begin(), _world[_pos].end(), [](const obj_t &obj) { 
        return obj.first != "player" && obj.first != "food" && obj.second > 0;
    })) {
        for (const auto &obj : _world[_pos])
            if (obj.first != "player" && obj.first != "food" && obj.second != 0) {
                prepareTake(obj.first);
                return;
            }
    } else {
        std::stringstream ss;
        for (const auto &pl : _supportingAlliesAscend)
            ss << "@" << pl.first << ", ";
        ss << "Ascension give up. Sorry everyone.";
        prepareTalk(ss.str());
        changeCircumstance(GatherObject);
        prepareLook();
    }
}

void Trantorian::actionCallbackWaitAscend(AI::FunctionsCode code, bool result)
{
    _supportingAlliesAscend[_personalNumber] = _pos;
    if (code == PuttingObject && result == false && !isCellReadyAscend())
        _givingUpWaitAscend = true;
    if (code == Talking || code == CheckingInventory) {
        return;
    } else if (result == false) {
        prepareLook();
    } else if (std::ceil(getActionTime(Incantating) / _settings["timePerFood"].get<double>() + 2) > _inventory["food"]) {
        goToClosestFood();
    } else if (!_givingUpWaitAscend) {
        waitForAscendWaitAscend(code);
    } else {
        givingUpAscendWaitAscend();
    }
}

void Trantorian::messageReceivedWaitAscend(AI::Direction /*orig*/, const std::string &msg)
{
    std::smatch m;
    std::regex_search(msg, m, std::regex("^(\\d+)"));
    size_t talker = std::stoul(m[1].str());

    if (std::regex_search(msg, m, std::regex("(\\d+) is probably dead"))) {
        size_t target = std::stoul(m[1]);
        if (_supportingAlliesAscend.count(target)) {
            _supportingAlliesAscend.erase(target);
            prepareTalk("@" + std::to_string(target) + " I don't need you anymore");
        }
    } else if (msg.find("I will help") != std::string::npos) {
        if (_supportingAlliesAscend.size() == _targetObjects["player"])
            prepareTalk("@" + std::to_string(talker) + " I don't need you anymore");
        else {
            prepareTalk("@" + std::to_string(talker) + " I wait for you");
            _supportingAlliesAscend[talker] = std::find_if(_otherPlayers.begin(), _otherPlayers.end(), [talker](OtherPlayer pl) { return pl.number == talker; })->pos;
        }
    } else if (_supportingAlliesAscend.count(talker) && (msg.find("I come") != std::string::npos || msg.find("here I am") != std::string::npos)) {
        _supportingAlliesAscend[talker] = std::find_if(_otherPlayers.begin(), _otherPlayers.end(), [talker](OtherPlayer pl) { return pl.number == talker; })->pos;
    } else if (msg.find("I can't help") != std::string::npos && _supportingAlliesAscend.count(talker)) {
        _supportingAlliesAscend.erase(talker);
    } else if (msg.find("to reach level " + std::to_string(_currentLevel+1)) != std::string::npos && msg.find(" 0 ") == std::string::npos && talker < _personalNumber && !_inIncantation) {
        std::stringstream ss;
        for (const auto &pl : _supportingAlliesAscend)
            ss << "@" << pl.first << ", ";
        ss << "Ascension give up. Sorry everyone.";
        prepareTalk(ss.str());
        _ascenderToRally = talker;
        _targetPos = std::find_if(_otherPlayers.begin(), _otherPlayers.end(), [this](const OtherPlayer &pl) { return pl.number == _ascenderToRally; })->pos;
        changeCircumstance(RallyAscend);
    }
}

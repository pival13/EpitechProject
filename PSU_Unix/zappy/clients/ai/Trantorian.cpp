/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Ubuntu]
** File description:
** Trantorian
*/

#include "Trantorian.hpp"

Trantorian::Trantorian(const std::string &teamName)
: AI(teamName)
, _personalNumber(getpid()), _teamName(teamName)
, _timePerAction(0)
{
    _childs.emplace();
    _settings = getSettingsAI();
    _inventory = {
        {"food", _settings["initialFood"].get<size_t>()-1},
        {"linemate", 0},
        {"deraumere", 0},
        {"sibur", 0},
        {"mendiane", 0},
        {"phiras", 0},
        {"thystame", 0}
    };
}

Trantorian::~Trantorian()
{
    while (_childs.size() > 0) {
        if (_childs.front().joinable())
            _childs.front().join();
        _childs.pop();
    }
}

void Trantorian::launch()
{
    _constructed = true;
    while (!_isConnect && _isAlive);
    if (_isAlive) {
        changeCircumstance(GatherObject);
        initialActionLaunch();
    }
    while (_isAlive) {
        if (_timePerAction.count() > 1 && _timePerAction.count() < 10000000)
            std::this_thread::sleep_for(_timePerAction/2);
        executePerTurnAction();
    }
}

void Trantorian::loopTrantorianTalk()
{
    static size_t lastActionCount = -1;
    static size_t mult = 1;

    if (lastActionCount != _currentAction) {
        lastActionCount = _currentAction;
        mult = 1;
    } else
        ++mult;
    if (_isAlive && !_whatToSay.empty()) {
        trantorianTalk(_whatToSay);
        addActionToDo([this]() { loopTrantorianTalk(); },
            (_inIncantation? getActionTime(Incantating): 0) + 50*mult);
    }
}

void Trantorian::actionCallback(FunctionsCode functCode, bool result)
{
    _currentAction += getActionTime(functCode);

    if (functCode == Incantating) {
        prepareTalk(result ? ("I am now level " + std::to_string(_currentLevel)) : "Failed to level up");
        prepareGetInventory();
        changeCircumstance(GatherObject);
        return;
    }
    if (result == true) {
        if (functCode == TakingObject) {
            _inventory[callbackedActionParameter] += 1;
            _world[_pos][callbackedActionParameter] -= 1;
        } else if (functCode == PuttingObject) {
            _inventory[callbackedActionParameter] -= 1;
            _world[_pos][callbackedActionParameter] += 1;
        } else if (functCode == Moving) {
            _world[_pos]["player"] -= 1;
            _pos = _pos + orientationToVector();
            if (_world.count(_pos))
                _world[_pos]["player"] += 1;
        } else if (functCode == MovingLeft)
            _orientation = Orientation((_orientation+1)%4);
        else if (functCode == MovingRight)
            _orientation = Orientation((_orientation-1+4)%4);
    }

    if (_actionCallbackCircumstance.count(_currentCircumstance))
        (this->*_actionCallbackCircumstance.at(_currentCircumstance))(functCode, result);
}

void Trantorian::lookCallback(const std::deque<inv_t> &content)
{
    _currentAction += getActionTime(Looking);

    updateWorld(content);

    if (_actionCallbackCircumstance.count(_currentCircumstance))
        (this->*_actionCallbackCircumstance.at(_currentCircumstance))(Looking, true);
}

void Trantorian::inventoryCallback(const inv_t &inventory)
{
    _currentAction += getActionTime(CheckingInventory);
    
    _inventory = inventory;

    if (_actionCallbackCircumstance.count(_currentCircumstance))
        (this->*_actionCallbackCircumstance.at(_currentCircumstance))(CheckingInventory, true);
}

void Trantorian::messageReceived(Direction orig, const std::string &_msg)
{
    std::string msg(_msg);
    if (!preParseMessage(msg))
        return;

    if (msg.find("I am the Layer") != std::string::npos && !_posSynchronized && _currentCircumstance != RallyLayer)
        changeCircumstance(RallyLayer);
    if (_msgReceivedCircumstance.count(_currentCircumstance))
        (this->*_msgReceivedCircumstance.at(_currentCircumstance))(orig, msg);
}

void Trantorian::beenEject(Direction orig)
{
    pos_t delta = directionToVector(orig);
    _pos[0] -= delta[0];
    _pos[1] -= delta[1];

    if (_currentCircumstance == RallyLayer || !_posSynchronized)
        beenEjectRallyLayer();
}

void Trantorian::isDead()
{}

void Trantorian::inIncantation()
{}

void Trantorian::remainingPlace(size_t /*places*/)
{}

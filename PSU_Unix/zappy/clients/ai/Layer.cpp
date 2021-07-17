/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Ubuntu]
** File description:
** Layer
*/

#include "Layer.hpp"

Layer::Layer(const std::string &teamName)
: Trantorian(teamName)
{
    _posSynchronized = true;
    _missingTrantorian = 2;
    _whatToSay = "I am the Layer";
}

void Layer::launch()
{
    _constructed = true;
    while (!_isConnect && _isAlive);
    if (_isAlive)
        initialActionLaunch();
    while (_isAlive) {
        if (_timePerAction.count() > 1 && _timePerAction.count() < 10000000)
            std::this_thread::sleep_for(_timePerAction/2);
        
        executePerTurnAction();
        checkDeadPlayer();
        checkMissingTrantorian();
        layerCreateChild();
    }
}

void Layer::prepareNewConnection()
{
    addActionToDo([this]() {
        _listMutex.lock();
        if (_reservedPlace >= 2) {
            int nb = rand() % 20;
            if (nb == 0)
                _childsList.push_back("Scrambler");
            else
                _childsList.push_back("CannonFodder");
        } else
            _reservedPlace++;
        _listMutex.unlock();
    }, getActionTime(LayingEgg)+getActionTime("Egg hatching"));
}

void Layer::remainingPlace(size_t remainingPlaces)
{
    _listMutex.lock();
    for (size_t i = 0; i < remainingPlaces; i++)
        _childsList.push_back("CannonFodder");
    _listMutex.unlock();
}

void Layer::lookCallback(const std::deque<inv_t> &/*content*/)
{
    _currentAction += getActionTime(Looking);

    addActionToDo([this]() {
        layEgg();
        prepareNewConnection();
    });
}

void Layer::actionCallback(FunctionsCode funct, bool /*result*/)
{
    _currentAction += getActionTime(funct);

    if (funct == LayingEgg) {
        addActionToDo([this]() {
            take("food");
            layEgg();
            prepareNewConnection();
        });
    } else if (funct == Talking)
        _alreadyTalk = false;
}

void Layer::messageReceived(Direction orig, const std::string &_msg)
{
    std::string msg(_msg);
    try {
        _lastTalk[std::stoul(msg)] = _currentAction;
    } catch (const std::invalid_argument &e) {
        return;
    }
    if (!preParseMessage(msg))
        return;

    if (msg.find("Nice to meet you") != std::string::npos || msg.find("@Layer") != std::string::npos) {
        if (orig == Self)
            addActionToDo([this]() {
                std::stringstream ss("");
                ss << "I am the Layer. You were at " << _pos << ", you are at " << (_pos + orientationToVector());

                eject();
                trantorianTalk(ss.str());
            });
        else if (!_alreadyTalk) {
            addActionToDo([this]() {
                trantorianTalk("I am the Layer");
            });
            _alreadyTalk = true;
        }
    }
}
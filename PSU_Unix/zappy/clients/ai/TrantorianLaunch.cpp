/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Ubuntu]
** File description:
** TrantorianLaunch
*/

#include "Trantorian.hpp"
#include "Layer.hpp"

void Trantorian::initialActionLaunch()
{
    trantorianTalk(std::string("Nice to meet you, I am a ") + typeid(*this).name());
    look();

    _timePerAction = std::chrono::nanoseconds(1);
    std::chrono::nanoseconds beforeTime(std::chrono::system_clock::now().time_since_epoch().count());
    addActionToDo([this, beforeTime]() {
        std::chrono::nanoseconds afterTime(std::chrono::system_clock::now().time_since_epoch().count());
        this->_timePerAction = (afterTime-beforeTime) / (getActionTime(Talking)+getActionTime(Looking));
    }, getActionTime(Talking)+getActionTime(Looking));
    addActionToDo([this]() { loopTrantorianTalk(); }, 50);
}

void Trantorian::executePerTurnAction()
{
    static std::chrono::nanoseconds lastActionTime;
    static size_t lastActionCount = -1;
    static size_t lastFoodRemove = 0;

    std::chrono::nanoseconds now(std::chrono::system_clock::now().time_since_epoch().count());
    size_t usedActionNb = _currentAction + (lastActionCount != _currentAction || _timePerAction.count() == 1 ? 0 : (now-lastActionTime) / _timePerAction);

    lastActionTime = lastActionCount != _currentAction ? now : lastActionTime;
    lastActionCount = _currentAction;
    if (usedActionNb - lastFoodRemove > _settings["timePerFood"].get<size_t>() * 0.8) {
        _inventory["food"] -= 1;
        lastFoodRemove = usedActionNb;
    } else if (lastFoodRemove > usedActionNb) {
        lastFoodRemove = usedActionNb;
        prepareGetInventory();
    }

    std::list<size_t> actionsTime;
    for (const auto &p : _todoActions)
        if (p.first <= usedActionNb)
            actionsTime.push_back(p.first);
    _todoMutex.lock();
    while (!actionsTime.empty()) {
        for (const auto &f : _todoActions[actionsTime.front()])
            f();
        _todoActions.erase(actionsTime.front());
        actionsTime.pop_front();
    }
    _todoMutex.unlock();
}


void Layer::checkDeadPlayer()
{
    for (auto pl = _otherPlayers.begin(); pl != _otherPlayers.end(); ++pl)
        if (_lastTalk[pl->number] + getActionTime(Incantating) + 100 + getActionTime(Talking) < _currentAction) {
            prepareTalk(std::to_string(pl->number) + " is probably dead");
            _otherPlayers.erase(pl);
            _childsList.push_front("Trantorian");
            _reservedPlace--;
            break;
        }
}

void Layer::checkMissingTrantorian()
{
    static std::map<size_t, size_t> oldTeamLevels;
    bool check = false;

    for (const auto &pl : _otherPlayers) {
        if (!oldTeamLevels.count(pl.number) || oldTeamLevels[pl.number] != pl.level) {
            oldTeamLevels[pl.number] = pl.level;
            check = true;
        }
    }
    for (ssize_t level = _settings["elevationPath"].size()-1; level >= 0 && check; level--) {
        size_t nbPl = 0;
        size_t nbPlLow = 0;
        size_t nbReq = 0;
        for (const auto &pl : _otherPlayers) {
            nbPl += (pl.level == level+1 ? 1 : 0);
            nbPlLow += (pl.level <= level+1 ? 1 : 0);
        }
        while (nbPl > nbReq)
            nbReq += _settings["elevationPath"][level]["player"].get<size_t>();
        if (nbReq > nbPlLow) {
            _missingTrantorian = nbReq - nbPlLow;
            break;
        }
    }
}

void Layer::layerCreateChild()
{
    while (!_childsList.empty()) {
        if (_missingTrantorian > 0) {
            createNewChild("Trantorian");
            _missingTrantorian -= 1;
        } else
            createNewChild(_childsList.front());
        _listMutex.lock();
        _childsList.pop_front();
        _listMutex.unlock();
    }
}

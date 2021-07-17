/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Ubuntu]
** File description:
** Trantorian
*/

#include "Trantorian.hpp"

size_t Trantorian::getActionTime(FunctionsCode action)
{
    static const std::map<FunctionsCode, std::string> actionCode({
        {Moving, "Forward"},
        {MovingRight, "Right"},
        {MovingLeft, "Left"},
        {Looking, "Look"},
        {CheckingInventory, "Inventory"},
        {Talking, "Broadcast @@@"},
        {CheckingPlaceTeam, "Connect_nbr"},
        {LayingEgg, "Fork"},
        {Ejecting, "Eject"},
        {TakingObject, "Take @@@"},
        {PuttingObject, "Set @@@"},
        {Incantating, "Incantation"}
    });
    if (actionCode.count(action))
        return getActionTime(actionCode.at(action));
    else
        return 0;
}

size_t Trantorian::getActionTime(const std::string &action)
{
    return _settings["commandTime"].contain(action) ? _settings["commandTime"][action].get<size_t>() : size_t(-1);
}

pos_t Trantorian::orientationToVector(ssize_t forward, ssize_t lateral)
{
    if (_orientation == North)
        return pos_t({lateral, forward});
    if (_orientation == South)
        return pos_t({-lateral, -forward});
    if (_orientation == East)
        return pos_t({forward, -lateral});
    if (_orientation == West)
        return pos_t({-forward, lateral});
    return pos_t({0,0}); 
}

pos_t Trantorian::directionToVector(Direction dir)
{
    switch (dir) {
    case Front: return pos_t({0, 1});
    case FrontLeft: return pos_t({-1, 1});
    case Left: return pos_t({-1, 0});
    case BackLeft: return pos_t({-1, -1});
    case Back: return pos_t({0, -1});
    case BackRight: return pos_t({1, -1});
    case Right: return pos_t({1, 0});
    case FrontRight: return pos_t({1, 1});
    default: return pos_t({0, 0});
    }
}

pos_t Trantorian::directionToWorldMax(Direction dir)
{
    ssize_t v = std::max(_mapSize[0], _mapSize[1]) / 2;
    switch (dir) {
    case Front: return orientationToVector(v, 0);
    case FrontLeft: return orientationToVector(v,-v);
    case Left: return orientationToVector(0,-v);
    case BackLeft: return orientationToVector(-v,-v);
    case Back: return orientationToVector(-v, 0);
    case BackRight: return orientationToVector(-v,v);
    case Right: return orientationToVector(0,v);
    case FrontRight: return orientationToVector(v,v);
    default: return pos_t({0,0});
    }
}

bool Trantorian::isFront(const pos_t &pos, const pos_t &dir)
{
    return pos == _pos ||
           (pos[0] == _pos[0] && (pos[1]-_pos[1]) * (dir == pos_t({0,0})? orientationToVector()[1]: dir[1]) > 0) ||
           (pos[1] == _pos[1] && (pos[0]-_pos[0]) * (dir == pos_t({0,0})? orientationToVector()[0]: dir[0]) > 0);
}

size_t Trantorian::actionToReach(const pos_t &pos, const pos_t &orig, const pos_t &_dir)
{
    pos_t dir = _dir[0] == 0 && _dir[1] == 0? orientationToVector(): _dir;
    pos_t myPos = orig[0] == -1 && orig[1] == -1? _pos: orig;
    size_t distance = abs(pos[0]-myPos[0]) + abs(pos[1]-myPos[1]);

    if (pos[0] == myPos[0] || pos[1] == myPos[1]) {
        if ((pos[0]-myPos[0]) * dir[0] < 0 || (pos[1]-myPos[1]) * dir[1] < 0)
            distance += 2;
        else if (!isFront(pos, dir))
            distance += 1;
    } else {
        if ((pos[0]-myPos[0]) * dir[0] > 0 || (pos[1]-myPos[1]) * dir[1] > 0)
            distance += 1;
        else
            distance += 2;
    }
    return distance;
}

bool Trantorian::isObjectFront(const inv_t &obj, bool checkOnYou)
{
    return std::any_of(_world.begin(), _world.end(), [&obj, checkOnYou, this](const std::pair<pos_t, inv_t> &cell) {
        return (checkOnYou || cell.first != _pos) && isFront(cell.first) && std::any_of(cell.second.begin(), cell.second.end(), [&obj, &cell, this](const obj_t &cellContent) {
            return cellContent.second > 0 && obj.count(cellContent.first) && obj.at(cellContent.first) > 0 && std::none_of(_otherPlayers.begin(), _otherPlayers.end(), [&cell](const OtherPlayer &pl) {
                return pl.incantate && pl.pos == cell.first;
            });
        });
    });
}

bool Trantorian::isObjectFront(const std::string &obj, bool checkOnYou)
{
    return isObjectFront(inv_t({ {obj, 1} }), checkOnYou);
}

bool Trantorian::isObjectNear(const inv_t &obj, bool checkOnYou)
{
    return std::any_of(_world.begin(), _world.end(), [&obj, checkOnYou, this](const std::pair<pos_t, inv_t> &cell) {
        return (checkOnYou || cell.first != _pos) && std::any_of(cell.second.begin(), cell.second.end(), [&obj, &cell, this](const obj_t &cellContent) {
            return cellContent.second > 0 && obj.count(cellContent.first) && obj.at(cellContent.first) > 0 && std::none_of(_otherPlayers.begin(), _otherPlayers.end(), [&cell](const OtherPlayer &pl) {
                return pl.incantate && pl.pos == cell.first;
            });
        });
    });
}

bool Trantorian::isObjectNear(const std::string &obj, bool checkOnYou)
{
    return isObjectNear(inv_t({ {obj, 1} }), checkOnYou);
}

pos_t Trantorian::posClosestObject(const inv_t &obj, bool frontOnly, bool checkOnSelf, bool assignAsTarget)
{
    pos_t pos = _pos + _mapSize;
    for (const auto &cell : _world) {
        if ((!frontOnly || isFront(cell.first)) && (checkOnSelf || cell.first != _pos) && actionToReach(cell.first) < actionToReach(pos) && 
            std::none_of(_otherPlayers.begin(), _otherPlayers.end(), [&cell](const OtherPlayer &pl) {
                return pl.incantate && pl.pos == cell.first;
            })) {
            for (const obj_t &elem : cell.second) {
                if (elem.second > 0 && obj.count(elem.first) && obj.at(elem.first) > 0) {
                    pos = cell.first;
                    if (assignAsTarget)
                        _wantedObject = elem.first;
                }
            }
        }
    }
    return pos;
}

pos_t Trantorian::posClosestObject(const std::string &obj, bool frontOnly, bool checkOnSelf, bool assignAsTarget)
{
    return posClosestObject(inv_t({ {obj, 1} }), frontOnly, checkOnSelf, assignAsTarget);
}

bool Trantorian::isAtOriginLook()
{
    std::array<pos_t, 9> a({pos_t({-1, 1}), pos_t({0, 1}), pos_t({1, 1}),
                            pos_t({-1, 0}), pos_t({0, 0}), pos_t({1, 0}),
                            pos_t({-1,-1}), pos_t({0,-1}), pos_t({1,-1})});
    return std::count_if(a.begin(), a.end(), [this](const pos_t &pos) {
        return _world.count(_pos+pos);
    }) == 4;
}

void Trantorian::goToPos(const pos_t &pos, bool usePrepare)
{
    size_t actionNeeded = actionToReach(pos);
    if (actionNeeded == 0 && !_wantedObject.empty())
        usePrepare? prepareTake(_wantedObject): take(_wantedObject);
    else if (actionNeeded == 0)
        usePrepare? prepareLook(): look();
    else if (actionNeeded > actionToReach(pos, _pos, orientationToVector(0,1)))
        usePrepare? prepareTurnRight(): turnRight();
    else if (actionNeeded > actionToReach(pos, _pos, orientationToVector(0,-1)))
        usePrepare? prepareTurnLeft(): turnLeft();
    else
        usePrepare? prepareMove(): move();
}

void Trantorian::updateWorld(const std::deque<inv_t> &lookResult, bool reset)
{
    if (reset)
        _world.clear();
    for (size_t i = 0; i != lookResult.size(); i++) {
        int depth = int(sqrt(i));
        int width = i - depth*depth - depth;
        pos_t pos = orientationToVector(depth, width);
        _world[_pos+pos] = lookResult[i];
    }
}

bool Trantorian::preParseMessage(std::string &msg)
{
    std::smatch match;

    if (!std::regex_match(msg, match, std::regex("(\\d+), "+_teamName+", (\\d+)(?:, position \\{(-?\\d+),(-?\\d+)\\})?, (.+)")))
        return false;

    size_t talkerNb = stoul(match[1].str());
    size_t msgNumber = stoul(match[2].str());
    if (talkerNb == _personalNumber)
        return false;

    auto talker = std::find_if(_otherPlayers.begin(), _otherPlayers.end(), [talkerNb](const OtherPlayer &pl) {return pl.number == talkerNb;});
    if (talker == _otherPlayers.end())
        _otherPlayers.push_back({talkerNb, 1, msgNumber, pos_t({0,0}), false});
    else if (msgNumber == talker->lastMsgNb+1)
        talker->lastMsgNb++;
    else
        return false;
    if (match[3].length())
        talker->pos = pos_t({stol(match[3].str()),stol(match[4].str())});
    if (match[5].str().find("Begining ascension") != std::string::npos || match[5].str().find("Ready to ascend") != std::string::npos)
        talker->incantate = true;
    else
        talker->incantate = false;
    if (match[5].str().find("I am now level ") != std::string::npos)
        talker->level = std::stoul(match[5].str().substr(match[5].str().find("I am now level ")+15));

    msg = match[1].str() + ", " + match[5].str();
    std::string str = msg;
    if (std::regex_search(str, match, std::regex("@\\d+"))) {
        do {
            if (stoul(match.str().substr(1)) == _personalNumber)
                return true;
            str = match.suffix();
        } while (std::regex_search(str, match, std::regex("@\\d+")));
        return false;
    } else
        return true;
}

void Trantorian::trantorianTalk(const std::string &msg)
{
    std::stringstream ss("");
    ss << _personalNumber << ", " << _teamName << ", " << _msgNumber++ << ", ";
    if (_posSynchronized)
        ss << "position " << _pos << ", ";
    std::cout << _personalNumber;
    if (_posSynchronized)
        std::cout << " (" << _pos << ", " << orientationToVector() << ")";
    std::cout << " said: " + msg << std::endl;
    talk(ss.str() + msg);
}

void Trantorian::addActionToDo(const std::function<void()> &funct, size_t timeout)
{
    _todoMutex.lock();
    _todoActions[_currentAction + timeout].push_back(funct);
    _todoMutex.unlock();
}

void Trantorian::changeCircumstance(Circumstance newCircumstance)
{
    _whatToSay = "I'm still alive";
    _currentCircumstance = newCircumstance;
    if (_updateGoalCircumstance.count(_currentCircumstance))
        (this->*_updateGoalCircumstance.at(_currentCircumstance))();
}

void Trantorian::createNewChild(const std::string &kind)
{
    if (_isAlive) {
        std::stringstream ss;
        ss << "./zappy_ai -h " << connectionHost << " -p " << connectionPort << " -n " << _teamName << " --child-kind=" << kind;
        _childs.emplace(ss.str());
    }
}

std::ostream &operator<<(std::ostream &os, const pos_t &pos)
{
    os << "{" << pos[0] << "," << pos[1] << "}";
    return os;
}

std::ostream &operator<<(std::ostream &os, const AI::FunctionsCode &pos)
{
    switch (pos) {
    case AI::Moving: os << "Moving"; break;
    case AI::MovingRight: os << "MovingRight"; break;
    case AI::MovingLeft: os << "MovingLeft"; break;
    case AI::Looking: os << "Looking"; break;
    case AI::CheckingInventory: os << "CheckingInventory"; break;
    case AI::Talking: os << "Talking"; break;
    case AI::CheckingPlaceTeam: os << "CheckingPlaceTeam"; break;
    case AI::LayingEgg: os << "LayingEgg"; break;
    case AI::Ejecting: os << "Ejecting"; break;
    case AI::TakingObject: os << "TakingObject"; break;
    case AI::PuttingObject: os << "PuttingObject"; break;
    case AI::Incantating: os << "Incantating"; break;
    default: os << pos; break;
    }
    return os;
}

bool operator==(const pos_t &p1, const pos_t &p2)
{
    return p1[0] == p2[0] && p1[1] == p2[1];
}

bool operator!=(const pos_t &p1, const pos_t &p2)
{
    return !(p1 == p2);
}

bool operator>(const pos_t &p1, const pos_t &p2)
{
    return p1[0] > p2[0] || p1[1] > p2[1];
}

bool operator<(const pos_t &p1, const pos_t &p2)
{
    return p2 > p1;
}

pos_t operator+(const pos_t &p1, const pos_t &p2)
{
    return pos_t({p1[0]+p2[0], p1[1]+p2[1]});
}

inv_t operator+(const inv_t &p1, const inv_t &p2)
{
    inv_t result;

    for (const auto &pair : p1)
        if (p2.count(pair.first))
            result[pair.first] = pair.second + p2.at(pair.first);
        else
            result[pair.first] = pair.second;
    for (const auto &pair : p2)
        if (!result.count(pair.first))
            result[pair.first] = pair.second;
    return result;
}

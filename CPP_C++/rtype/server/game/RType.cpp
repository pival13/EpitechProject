/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** RType
*/

#include "RType.hpp"

RType::RType(const std::string &playerId)
: basicGO(), elements(), toDestroy(), enemySpam(1000), obstacleSpam(5000)
{
    deltaTime = std::chrono::milliseconds(0);
    addPlayer(playerId);
    loopThread = std::thread([this]() { mainLoop(); });
}

RType::~RType()
{
    over = true;
    if (loopThread.joinable())
        loopThread.join();
}

void RType::receiveInputs(const std::string &id, const std::vector<uint8_t> &data)
{
    if (!players.count(id)) return;
    size_t uuid = players[id];
    if (!elements.count(uuid)) return;
    Player *pl = static_cast<Player*>(elements.at(uuid).get());

    RTypeNetworkInput *inputs = (RTypeNetworkInput*)data.data();

    if (data.size() < sizeof(RTypeNetworkInput))
        return;
    pl->setDirectionMove({
        double(inputs->moveX) / 100 * mapWidth/4,
        double(inputs->moveY) / 100 * mapHeight/4
    , 0});
    if (inputs->isShooting)
        pl->shoot();
}

std::vector<uint8_t> RType::exportOutputs() const
{
    std::vector<uint8_t> data;
    for (const auto &p : elements) {
        RTypeNetworkObject obj = p.second->toNetworkObject();
        obj.uuid = p.first;
        if (obj.type == RTypeObjectType::ObjectPlayer)
            obj.player.playerId = std::count_if(players.begin(), players.end(), [&p](const std::pair<std::string, size_t> &p2) { return p.first > p2.second; });
        
        data.resize(data.size() + sizeof(obj));
        std::memcpy(data.data()+data.size()-sizeof(obj), &obj, sizeof(obj));
    }
    return data;
}

bool RType::addPlayer(const std::string &playerId)
{
    if (players.size() >= maxPlayer) return false;
    players[playerId] = _uuid;
    try {
        instantiate(RTypeObjectType::ObjectPlayer, "RTPlayer", {border*2, mapHeight/(maxPlayer+1)*players.size()+border, 0});
    } catch (const std::exception &e) {
        std::cerr << "[Server] Failed to add a player: " << e.what() << std::endl;
        return false;
    }
    elements[players[playerId]]->setDirectionMove({0,0,0});
    return true;
}

std::list<RTypeEvents> RType::getEvents() const
{
    std::list<RTypeEvents> l = events;

    auto it = players.begin();
    for (size_t i = 0; i != players.size(); ++i) {
        l.push_front({});
        l.front().type = RTypeEvents::EventType::PlayerScore;
        if (elements.count(it->second))
            l.front().playerScore.score = int(static_cast<Player*>(elements.at(it->second).get())->getScore());
        else
            l.front().playerScore.score = 0;
        l.front().playerScore.playerNumber = uint32_t(i);
        ++it;
    }
    return l;
}

void RType::mainLoop()
{
    std::chrono::system_clock::time_point t0 = std::chrono::system_clock::now();
    lastLoopExecution = t0;
    lastNewEnemy = t0;
    lastNewObstacle = t0;

    const std::chrono::milliseconds fps_1(1000 / 30);
    const auto a = t0-lastLoopExecution;
    const double mult = 1000.0 * decltype(a)::period::num / decltype(a)::period::den; // 1000.0 * 1 / 10000000

    while (!over) {
        std::this_thread::sleep_until(lastLoopExecution + fps_1);

        events.clear();
        std::chrono::system_clock::time_point t =  std::chrono::system_clock::now();
        deltaTime = std::chrono::milliseconds(size_t((t - lastLoopExecution).count() * mult));
        if (t > t0 + std::chrono::seconds(3)) {
            if (t > lastNewEnemy + enemySpam) {
                try {
                    instantiateRandomEnemy();
                    lastNewEnemy = t;
                } catch (const std::exception &e) {
                    std::cerr << "[Server] Failed to create an enemy: " << e.what() << std::endl;
                }
            }
            if (t > lastNewObstacle + obstacleSpam) {
                try {
                    instantiateRandomObstacle();
                    lastNewObstacle = t;
                } catch (const std::exception &e) {
                    std::cerr << "[Server] Failed to create an obstacle: " << e.what() << std::endl;
                }
            }
        }
        for (auto &elem : elements)
            elem.second->update(*this, _colliders, &RType::destroy, &RType::instantiate);
        destroy();
        lastLoopExecution += fps_1;
    }
}

RTypeObject *RType::instantiate(const std::string &what, const Vector3 &pos, const Vector3 &rotation, const Vector3 &scale)
{
    std::smatch m;
    if (std::regex_match(what, m, std::regex("(\\w+)::(.+)"))) {
        if (m[1] == "Player")
            return instantiate(RTypeObjectType::ObjectPlayer, m[2].str(), pos, rotation, scale);
        else if (m[1] == "Enemy")
            return instantiate(RTypeObjectType::ObjectEnemy, m[2].str(), pos, rotation, scale);
        else if (m[1] == "Missile")
            return instantiate(RTypeObjectType::ObjectMissile, m[2].str(), pos, rotation, scale);
        else if (m[1] == "Obstacle")
            return instantiate(RTypeObjectType::ObjectObstacle, m[2].str(), pos, rotation, scale);
        else if (m[1] == "PowerUp")
            return instantiate(RTypeObjectType::ObjectPowerUp, m[2].str(), pos, rotation, scale);
    }
    throw std::invalid_argument("RType::instantiate Unknow object: \""+what+"\"");
}

RTypeObject *RType::instantiate(RTypeObjectType type, const std::string &what, const Vector3 &pos, const Vector3 &rotation, const Vector3 &scale)
{
    mutex.lock();
    try {
        switch (type) {
            case RTypeObjectType::ObjectPlayer:
                elements.emplace(_uuid, RTypeFactory::createPlayer(what)); break;
            case RTypeObjectType::ObjectEnemy:
                elements.emplace(_uuid, RTypeFactory::createEnemy(what)); break;
            case RTypeObjectType::ObjectMissile:
                elements.emplace(_uuid, RTypeFactory::createMissile(what)); break;
            case RTypeObjectType::ObjectObstacle:
                elements.emplace(_uuid, RTypeFactory::createObstacle(what)); break;
            case RTypeObjectType::ObjectPowerUp:
                elements.emplace(_uuid, RTypeFactory::createPowerUp(what)); break;
        }
    } catch (std::exception &e) {
        mutex.unlock();
        throw e;
    }
    RTypeObject *obj = elements[_uuid++].get();
    obj->setParent(&basicGO);
    obj->getTransform().setPosition(pos);
    obj->getTransform().setDegRotation(rotation);
    obj->getTransform().setScale(scale);
    obj->setDirectionMove({mapWidth/5, 0, 0});
    _colliders.insert(_colliders.end(), obj->getColliders().begin(), obj->getColliders().end());

    addEvents(RTypeEvents::ObjectCreate, obj);
    mutex.unlock();
    return obj;
}

void RType::instantiateRandomEnemy()
{
    mutex.lock();
    try {
        elements.emplace(_uuid, RTypeFactory::createEnemyRandom());
    } catch (std::exception &e) {
        mutex.unlock();
        throw e;
    }
    RTypeObject *obj = elements[_uuid++].get();
    obj->setParent(&basicGO);
    obj->getTransform().setPosition({mapWidth+2*border, rand()%int64_t(mapHeight)+border, 0});
    obj->getTransform().setScale({-1, 1, 1});
    obj->setDirectionMove({mapWidth/5, 0, 0});
    addEvents(RTypeEvents::ObjectCreate, obj);
    _colliders.insert(_colliders.end(), obj->getColliders().begin(), obj->getColliders().end());
    mutex.unlock();
}

void RType::instantiateRandomObstacle()
{
    mutex.lock();
    try {
        elements.emplace(_uuid, RTypeFactory::createObstacleRandom());
    } catch (std::exception &e) {
        mutex.unlock();
        throw e;
    }
    RTypeObject *obj = elements[_uuid++].get();
    obj->setParent(&basicGO);
    obj->getTransform().setPosition({mapWidth+2*border, rand()%int64_t(mapHeight)+border, 0});
    obj->getTransform().setScale({-1, 1, 1});
    obj->setDirectionMove({mapWidth/5, 0, 0});
    _colliders.insert(_colliders.end(), obj->getColliders().begin(), obj->getColliders().end());
    addEvents(RTypeEvents::ObjectCreate, obj);
    mutex.unlock();
}

void RType::destroy()
{
    for (const auto &p : elements) {
        const Vector3 &pos = p.second->getTransform().getPosition();
        if (pos.x < 0 || pos.y < 0 || pos.x > mapWidth+border*2 || pos.y > mapHeight + border*2)
            toDestroy.insert(p.second.get());
    }
    for (const void *ptr : toDestroy)
        for (const auto &p : elements)
            if (p.second.get() == ptr) {
                mutex.lock();
                addEvents(RTypeEvents::ObjectDestroy, p.second.get());
                for (const auto &c : p.second->getColliders())
                    for (auto it = _colliders.begin(); it != _colliders.end(); ++it)
                        if (*it == c) {
                            _colliders.erase(it);
                            break;
                        }
                elements.erase(p.first);
                mutex.unlock();
                break;
            }
    toDestroy.clear();
}

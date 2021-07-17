/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019 [WSL: Ubuntu]
** File description:
** Pacman
*/

#include "Pacman.hpp"

Pacman::Pacman(ArcadeContent &ac)
: AGameModule(ac, "Pac-Man/texture.txt")
, now(std::chrono::system_clock::now().time_since_epoch().count() / 1000000)
, playerTimer(now)
, superTimer(0)
{
    if (getMapHeight() < 30 || getMapWidth() < 30)
        page = 0;
    else
        initGame(map);
}

Pacman::~Pacman()
{
}

void Pacman::initGame(int nMap)
{
    std::ifstream f("games/Pac-Man/map/" + std::to_string(nMap) + ".txt");
    const char ghosts[] = {GHOST1, GHOST2, GHOST3, GHOST4};

    if (!f.is_open()) {
        page = 0;
        return;
    }
    std::string s;
    std::getline(f, s, '\0');
    std::vector<std::string> arr;
    while (s.length()) {
        int size = s.find_first_of("\n\0");
        arr.push_back(s.substr(0, (size == -1 ? s.length() : size)));
        s = s.substr(size == -1 ? s.length() : size+1);
    }
    if (!std::all_of(arr.begin(), arr.end(), [&](std::string s) { return s.length() == arr[0].length(); }))
        page = 0;
    else {
        cleanMap();
        mapSize = {arr[0].size(), arr.size()};
        for (size_t j = 0; j != arr.size(); j++)
            for (size_t i = 0; i != arr[j].size(); i++) {
                setMapAt(getMapWidth() / 2 - arr[j].size() / 2 + i, getMapHeight() / 2 - arr.size() / 2 + j, arr[j][i]);
                for (int g = 0; g != 4; g++)
                    if (arr[j][i] == ghosts[g])
                        beginGhost[g] = {getMapWidth() / 2 - arr[j].size() / 2 + i, getMapHeight() / 2 - arr.size() / 2 + j};
            }
    }
    f.close();
    for (size_t i = 0; i != 4; i++)
        enemyTimer[i] = now + msec(10000);
    beforeGhost = {' ', ' ', ' ', ' '};
    direction = 0;
    superTimer = msec(0);
}

void Pacman::gameOver()
{
    life--;
    if (life == 0)
        page = 2;
    else
        initGame(map);
    dead = false;
}

void Pacman::moveUnit()
{
    if (isKeyDown())
        direction = 3;
    else if (isKeyUp())
        direction = 1;
    else if (isKeyLeft())
        direction = 4;
    else if (isKeyRight())
        direction = 2;

    if (playerTimer + msec(200) < now)
        playerTimer += msec(200);
    else
        return;

    pos_t pos = getPos(PLAYER);
    setMapAt(pos, GROUND);
    if (direction == 1 && getMapAt(pos[0], pos[1]-1) != WALL)
        pos[1] -= 1;
    else if (direction == 2 && getMapAt(pos[0]+1, pos[1]) != WALL)
        pos[0] += 1;
    else if (direction == 3 && getMapAt(pos[0], pos[1]+1) != WALL)
        pos[1] += 1;
    else if (direction == 4 && getMapAt(pos[0]-1, pos[1]) != WALL)
        pos[0] -= 1;

    tryCrossMap(pos);

    if (isEnemy(pos))
        dead = true;
    else {
        if (getMapAt(pos) == POINT || getMapAt(pos) == SUPER_POINT)
            score += 10;
        else if (isEatable(pos)) {
            respawnGhost(pos);
            score += 50;
        }
        if (getMapAt(pos) == SUPER_POINT)
            superTimer = now;
        setMapAt(pos, PLAYER);
    }
}

void Pacman::respawnGhost(pos_t pos)
{
    char c = getMapAt(pos);
    const char ghosts[] = {EAT_GHOST1, EAT_GHOST2, EAT_GHOST3, EAT_GHOST4};

    for (size_t i = 0; i != 4; i++)
        if (c == ghosts[i]) {
            enemyTimer[i] += msec(10000);
            if (beforeGhost[i] == POINT || beforeGhost[i] == SUPER_POINT)
                score += 10;
            beforeGhost[i] = ' ';
        }
}

void Pacman::moveEnemies()
{
    const char enemies[] = {GHOST1, GHOST2, GHOST3, GHOST4};
    msec deltaTime(superTimer >= now - msec(10000) ? 250 : 200);

    refreshMap(EAT_GHOST1, GHOST1);
    refreshMap(EAT_GHOST2, GHOST2);
    refreshMap(EAT_GHOST3, GHOST3);
    refreshMap(EAT_GHOST4, GHOST4);
    
    for (size_t i = 0; i != 4; i++) {
        if (enemyTimer[i] + deltaTime < now)
            enemyTimer[i] += deltaTime;
        else
            continue;

        pos_t pos = getPos(enemies[i]);
        pos_t newPos = {pos[0], pos[1]};
        for (int i = 0; newPos[0] == pos[0] && newPos[1] == pos[1] && i < 20; i++) {
            int dir = rand() % 4;
            if (dir == 0 && isWalkableGhost({pos[0], pos[1]-1}))
                newPos[1] -= 1;
            else if (dir == 1 && isWalkableGhost({pos[0]+1, pos[1]}))
                newPos[0] += 1;
            else if (dir == 2 && isWalkableGhost({pos[0], pos[1]+1}))
                newPos[1] += 1;
            else if (dir == 3 && isWalkableGhost({pos[0]-1, pos[1]}))
                newPos[0] -= 1;
        }

        tryCrossMap(newPos);

        if (getMapAt(newPos) == PLAYER)
            dead = true;

        setMapAt(pos, beforeGhost[i]);
        beforeGhost[i] = getMapAt(newPos);
        setMapAt(newPos, enemies[i]);
    }
}

void Pacman::updateMap()
{
    if (now - superTimer < msec(10000)) {    
        refreshMap(GHOST1, EAT_GHOST1);
        refreshMap(GHOST2, EAT_GHOST2);
        refreshMap(GHOST3, EAT_GHOST3);
        refreshMap(GHOST4, EAT_GHOST4);
    }
    if (isComplete())
        initGame(++map); 
    else if (dead)
        gameOver();
}

void Pacman::gamePage()
{
    moveUnit();
    moveEnemies();
    updateMap();
}

void Pacman::update()
{
    void (Pacman::*f[])() = {&Pacman::unableToLaunchPage, &Pacman::gamePage, &Pacman::gameOverPage};

    now = msec(std::chrono::system_clock::now().time_since_epoch().count() / 1000000);
    (this->*f[page])();
}

Pacman *getGameModule(ArcadeContent &ac)
{
    return new Pacman(ac);
}
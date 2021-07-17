/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019 [WSL: Ubuntu]
** File description:
** Qix
*/

#include "Qix.hpp"

Qix::Qix(ArcadeContent &ac)
: AGameModule(ac, "qix/texture.txt")
{
    enemyTimer = std::chrono::milliseconds(std::chrono::system_clock::now().time_since_epoch().count() / 1000000);
    initGame();
}

Qix::~Qix()
{
}

void Qix::initGame()
{
    cleanMap();
    for (size_t i = 0; i != getMapHeight(); i++) {
        setMapAt(10, i, WALL);
        setMapAt(40, i, WALL);
    }
    for (size_t i = 10; i != getMapWidth()-10; i++) {
        setMapAt(i, 0, WALL);
        setMapAt(i, -1, WALL);
    }
    setMapAt(getMapWidth()/2, -1, PLAYER);
    setMapAt(getMapWidth()/2-1, 0, STARK);
    setMapAt(getMapWidth()/2, 0, STARK);
    setMapAt(getMapWidth()/2, getMapHeight()/2, QIX);
    recreateWall();
}

void Qix::recreateWall()
{
    for (size_t x = 0; x < getMapWidth(); x++)
        for (size_t y = 0; y < getMapHeight(); y++) {
            if (getMapAt(x, y) == BORDER || getMapAt(x, y) == TRAIL || getMapAt(x, y) == BURN)
                setMapAt(x, y, WALL);
            if (isNotWithQix(x, y))
                refreshMap(1, WALL);
        }
    for (size_t x = 0; x < getMapWidth(); x++)
        for (size_t y = 0; y < getMapHeight(); y++)
            if (getMapAt(x, y) == WALL && isNextCell(x, y, GROUND, true))
                setMapAt(x, y, BORDER);
    if (isComplete()) {
        level++;
        initGame();   
    }
}

void Qix::gameOver()
{
    bool isWalk = getMapAt(getQixPos()) == PLAYER_WALK;

    live--;
    refreshMap(STARK, BORDER);
    refreshMap(STARK_TAIL, BORDER);
    if (isWalk) {
        refreshMap(PLAYER_WALK, GROUND);
        refreshMap(TRAIL, GROUND);
        refreshMap(BURN, GROUND);
        setMapAt(beginWalk, PLAYER);
    }
    if ((isWalk && beginWalk[1] > getMapHeight()/2) || (!isWalk && getQixPos()[1] > getMapHeight() / 2)) {
        setMapAt(getMapWidth()/2-1, 0, STARK);
        setMapAt(getMapWidth()/2, 0, STARK);
    } else {
        setMapAt(getMapWidth()/2-1, getMapHeight()-1, STARK);
        setMapAt(getMapWidth()/2, getMapHeight()-1, STARK);
    }
    if (live == 0)
        page = 1;
}

void Qix::burnTrail()
{
    pos_t pos({0, 0});

    for (size_t x = 0; x != getMapWidth(); x++)
        for (size_t y = 0; y != getMapHeight(); y++)
            if (getMapAt(x, y) == BURN && isNextCell(x, y, TRAIL)) {
                pos = {x, y}; break; }
    if (pos[0] == 0 && pos[1] == 0)
        pos = beginWalk;

    if (isNextCell(pos[0], pos[1], TRAIL))
        setMapAt(posNextCell(pos[0], pos[1], TRAIL), BURN);
    else
        gameOver();
}

void Qix::moveQix(pos_t pos)
{
    pos_t newPos = {0, 0};
    while (newPos[0] == 0 && newPos[1] == 0) {
        int dir = rand() % 4;
        if (dir == 0 && isWalkable(pos[0], pos[1]-1, QIX))
            newPos = {pos[0], pos[1]-1};
        else if (dir == 1 && isWalkable(pos[0]+1, pos[1], QIX))
            newPos = {pos[0]+1, pos[1]};
        else if (dir == 2 && isWalkable(pos[0], pos[1]+1, QIX))
            newPos = {pos[0], pos[1]+1};
        else if (dir == 3 && isWalkable(pos[0]-1, pos[1], QIX))
            newPos = {pos[0]-1, pos[1]};
    }
    setMapAt(pos, GROUND);
    if (getMapAt(newPos) != GROUND)
        gameOver();
    setMapAt(newPos, QIX);
}

void Qix::moveStark(std::array<pos_t, 2> pos)
{
    if (isNextCell(pos[0][0], pos[0][1], STARK))
        refreshMap(STARK_TAIL, BORDER);

    std::array<pos_t, 2> starkTail = {posNextCell(pos[0][0], pos[0][1], STARK_TAIL), posNextCell(pos[1][0], pos[1][1], STARK_TAIL)};
    pos_t newPos;
    for (int i = 0; i != 2; i++) {
        newPos = posNextCell(pos[i][0], pos[i][1], BORDER);
        if (newPos[0] == 0 && newPos[1] == 0)
            newPos = posNextCell(pos[i][0], pos[i][1], PLAYER);
        if (newPos[0] == 0 && newPos[1] == 0)
            continue;
        setMapAt(starkTail[i], BORDER);
        setMapAt(pos[i], STARK_TAIL);
        if (getMapAt(newPos) == PLAYER) {
            gameOver();
            return;
        }
        setMapAt(newPos, STARK);
    }
}

void Qix::moveEnemies()
{
    std::chrono::milliseconds now(std::chrono::system_clock::now().time_since_epoch().count() / 1000000);

    pos_t allyPos(getQixPos());
    if (getMapAt(allyPos[0], allyPos[1]) == PLAYER_WALK && unitTimer.count() + 1000 < now.count()) {
        burnTrail();
        unitTimer += std::chrono::milliseconds(1000);
    }

    std::array<pos_t, 3> enemyPos(getEnemyPos());
    moveQix(enemyPos[0]);
    moveStark({enemyPos[1], enemyPos[2]});
}

void Qix::moveUnit()
{
    pos_t pos = getQixPos();
    pos_t newPos = pos;

    if (isKeyDown() && isWalkable(pos[0], pos[1]+1, PLAYER))
        newPos[1] += 1;
    else if (isKeyUp() && isWalkable(pos[0], pos[1]-1, PLAYER))
        newPos[1] -= 1;
    else if (isKeyLeft() && isWalkable(pos[0]-1, pos[1], PLAYER))
        newPos[0] -= 1;
    else if (isKeyRight() && isWalkable(pos[0]+1, pos[1], PLAYER))
        newPos[0] += 1;

    if (getMapAt(newPos[0], newPos[1]) == QIX || getMapAt(newPos[0], newPos[1]) == STARK)
        gameOver();
    else if (getMapAt(newPos[0], newPos[1]) == GROUND) {
        setMapAt(newPos[0], newPos[1], PLAYER_WALK);
        if (getMapAt(pos[0], pos[1]) == PLAYER_WALK)
            setMapAt(pos[0], pos[1], TRAIL);
        else {
            setMapAt(pos[0], pos[1], BORDER);
            beginWalk = pos;
        }
    } else if (getMapAt(newPos[0], newPos[1]) == BORDER) {
        setMapAt(newPos[0], newPos[1], PLAYER);
        if (getMapAt(pos[0], pos[1]) == PLAYER_WALK) {
            setMapAt(pos[0], pos[1], TRAIL);
            recreateWall();
        } else
            setMapAt(pos[0], pos[1], BORDER);
    }
}

void Qix::drawGameOver()
{
    static const std::string arr[] = {" %%%   %%%  %% %% %%%%%",
                         "%     %   % % % % %    ",
                         "%  %% %%%%% % % % %%%  ",
                         "%   % %   % %   % %    ",
                         " %%%  %   % %   % %%%%%",
                         "                       ",
                         " %%%  %   % %%%%% %%%% ",
                         "%   % %   % %     %   %",
                         "%   % %   % %%%   %%%% ",
                         "%   %  % %  %     %  %  ",
                         " %%%    %   %%%%% %   % " };
    size_t x = getMapWidth()/2 - 11;
    size_t y = getMapHeight()/2 - 5;

    for (size_t i = 0; i != 11; i++)
        for (size_t j = 0; j != arr[i].size(); j++)
            setMapAt(x+j, y+i, arr[i][j]);
}

void Qix::gameOverPage()
{
    std::chrono::milliseconds now(std::chrono::system_clock::now().time_since_epoch().count() / 1000000);
    static std::chrono::milliseconds t(0);

    if (t.count() == 0) {
        t = now;
        drawGameOver();
    }
    if (t.count() + 3000 < now.count())
        backToMenu();
}

void Qix::gamePage()
{
    std::chrono::milliseconds now(std::chrono::system_clock::now().time_since_epoch().count() / 1000000);

    if (isKeyRight() || isKeyDown() || isKeyLeft() || isKeyUp()) {
        moveUnit();
        unitTimer = now;
    }
    if (enemyTimer.count() + 250 < now.count()) {
        enemyTimer += std::chrono::milliseconds(250);
        moveEnemies();
    }
}

void Qix::update()
{
    void (Qix::*f[])() = {&Qix::gamePage, &Qix::gameOverPage};

    (this->*f[page])();
}

Qix *getGameModule(ArcadeContent &ac) { return new Qix(ac); }
/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019 [WSL: Ubuntu]
** File description:
** Tetris
*/

#include "Tetris.hpp"

Tetris::Tetris(ArcadeContent &ac)
: AGameModule(ac, "Tetris/texture.txt")
, now(std::chrono::system_clock::now().time_since_epoch().count() / 1000000)
, deltaTime(500), lastDown(now)
{
    if (getMapWidth() < 12 || getMapHeight() < 24) {
        page = 0;
        return;
    }
    page = 1;
    srand(now.count());
    cleanMap();

    for (size_t i = getMapHeight()/2-12; i != getMapHeight()/2+12; i++) {
        setMapAt(getMapWidth()/2-6, i, '#');
        setMapAt(getMapWidth()/2+5, i, '#');
    }
    for (size_t i = getMapWidth()/2-6; i != getMapWidth()/2+6; i++) {
        setMapAt(i, getMapHeight()/2-12, '#');
        setMapAt(i, getMapHeight()/2+11, '#');
    }

    try {
        DirReader piecesDir("games/Tetris/Pieces");
        for (auto file : piecesDir.getFiles())
            loadPiece(file);
        if (_pieces.size() == 0)
            page = 0;
        else
            addPiece();
            
    } catch (const std::exception &) {
        page = 0;
    }
}

Tetris::~Tetris()
{}

void Tetris::loadPiece(const std::string &file)
{
    size_t nb = _pieces.size(); 
    std::ifstream f("games/Tetris/Pieces/" + file);
    if (f.is_open()) {
        _pieces.push_back({});
        _pieces[nb].push_back({});
        std::string content;
        std::getline(f, content, '\0');
        for (char c : content)
            if (c == '\n') {
                if (_pieces[nb][_pieces[nb].size()-1].size() >= getMapWidth()) {
                    std::cerr << "Tetriminos " << file << " is too large" << std::endl;
                    _pieces.pop_back();
                    break;
                }
                _pieces[nb].push_back({});
            } else
                _pieces[nb][_pieces[nb].size()-1].push_back(c);
        if (nb != _pieces.size() && _pieces[nb].size() >= getMapHeight()) {
            std::cerr << "Tetriminos " << file << "is too large" << std::endl;
            _pieces.pop_back();
        }
    }
    f.close();
}

void Tetris::addPiece()
{
    auto piece = _pieces[rand() % _pieces.size()];
    for (size_t y = 0; y != piece.size(); y++)
        for (size_t x = 0; x != piece[y].size(); x++)
            if (isActivePiece(piece[y][x])) {
                if (!isBlockPiece({getMapWidth()/2-5+x, getMapHeight()/2-11+y}))
                    setMapAt(getMapWidth()/2-5+x, getMapHeight()/2-11+y, piece[y][x]);
                else
                    page = 2;
            }
}

void Tetris::movePiece(spos_t dir)
{
    if (!canMove(dir))
        return;

    std::vector<pos_t> poss;
    std::vector<char> symb;

    for (size_t x = 0; x != getMapWidth(); x++)
        for (size_t y = 0; y != getMapHeight(); y++)
            if (isActivePiece({x,y})) {
                poss.push_back({x, y});
                symb.push_back(getMapAt(x,y));
                setMapAt(x, y, ' ');
            }
    for (size_t i = 0; i != poss.size(); i++)
        setMapAt(poss[i][0]+dir[0], poss[i][1]+dir[1], symb[i]);
}

void Tetris::rotatePiece()
{
    std::vector<pos_t> poss;
    std::vector<char> symb;

    for (size_t x = 0; x != getMapWidth(); x++)
        for (size_t y = 0; y != getMapHeight(); y++)
            if (isActivePiece({x, y})) {
                poss.push_back({x, y});
                symb.push_back(getMapAt(x, y));
                setMapAt(x, y, ' ');
            }

    std::array<size_t, 4> rect = getRect(poss);
    if (rect[0]+rect[3] <= getMapWidth() / 2 + 5 && rect[1]+rect[2] <= getMapHeight() / 2 + 11)
        for (pos_t &pos : poss)
            pos = {pos[1]-rect[1]+rect[0], -pos[0]+rect[0]+rect[1]+rect[2]-1};

    for (size_t i = 0; i != poss.size(); i++)
        setMapAt(poss[i][0], poss[i][1], symb[i]);
}

void Tetris::fixedPiece()
{
    for (size_t x = 0; x != getMapWidth(); x++)
        for (size_t y = 0; y != getMapHeight(); y++)
            if (isActivePiece({x,y}))
                setMapAt(x, y, getMapAt(x,y)-'a'+'A');

    for (size_t y = getMapHeight()/2-11; y != getMapHeight()/2+11; y++)
        for (size_t x = getMapWidth()/2-5; x != getMapWidth()/2+5 && isBlockPiece({x,y}); x++) {
            if (x == getMapWidth()/2+4) {
                score++;
                for (size_t i = y; i >= getMapHeight()/2-11; i--)
                    for (size_t j = getMapWidth()/2-5; j != getMapWidth()/2+5; j++)
                        setMapAt(j,i,(i == getMapHeight()/2-11 ? ' ' : getMapAt(j, i-1)));
                if (score % 5 == 0)
                    deltaTime = msec(deltaTime.count() * 10 / 9);
            }
    }
}

void Tetris::gamePage()
{
    if (isKeyUp())
        rotatePiece();
    if (isKeyLeft())
        movePiece({-1,0});
    if (isKeyRight())
        movePiece({1,0});
    if (lastDown + deltaTime < now || isKeyDown()) {
        if (!canMove({0,1})) {
            fixedPiece();
            addPiece();
        } else
            movePiece({0,1});
        lastDown = now;
    }
}

void Tetris::update()
{
    void (Tetris::*f[])() = {&Tetris::errorPage, &Tetris::gamePage, &Tetris::gameOverPage};

    now = msec(std::chrono::system_clock::now().time_since_epoch().count() / 1000000);
    (this->*f[page])();
}

Tetris *getGameModule(ArcadeContent &ac)
{
    return new Tetris(ac);
}
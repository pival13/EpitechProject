/*
** EPITECH PROJECT, 2021
** AIA_gomoku
** File description:
** BoardReader
*/

#include "BoardReader.hpp"

#define getCell(i) cellAt(board, pos + vec * (i))

GomokuCell BoardReader::cellAt(const GomokuBoard &board, const Vector2 &pos)
{
    if (pos.second < 0 || pos.first < 0 || pos.second >= int(board.size()) || pos.first >= int(board[pos.second].size()))
        return GomokuCell::Error;
    return board.at(pos.second).at(pos.first);
}

bool BoardReader::belongFive(const GomokuBoard &board, bool yourSide, const Vector2 &pos)
{ for (const Vector2 &vec : VECTORS) if (belongFive(board, yourSide, pos, vec)) return true; return false; }
bool BoardReader::belongFive(const GomokuBoard &board, bool yourSide, const Vector2 &pos, const Vector2 &vec)
{ return indexFive(board, yourSide, pos, vec) != uint8_t(-1); }
uint8_t BoardReader::indexFive(const GomokuBoard &board, bool yourSide, const Vector2 &pos, const Vector2 &vec)
{
    // X X X X X
    for (int i = 0; i != 5; ++i)
        if (getCell(0-i) == (yourSide ? GomokuCell::Own : GomokuCell::Opponent) &&
            getCell(1-i) == (yourSide ? GomokuCell::Own : GomokuCell::Opponent) &&
            getCell(2-i) == (yourSide ? GomokuCell::Own : GomokuCell::Opponent) &&
            getCell(3-i) == (yourSide ? GomokuCell::Own : GomokuCell::Opponent) &&
            getCell(4-i) == (yourSide ? GomokuCell::Own : GomokuCell::Opponent))
                return i;
    return -1;
}

bool BoardReader::belongStraightFour(const GomokuBoard &board, bool yourSide, const Vector2 &pos)
{ for (const Vector2 &vec : VECTORS) if (belongStraightFour(board, yourSide, pos, vec)) return true; return false; }
bool BoardReader::belongStraightFour(const GomokuBoard &board, bool yourSide, const Vector2 &pos, const Vector2 &vec)
{ return indexStraightFour(board, yourSide, pos, vec) != uint8_t(-1); }
uint8_t BoardReader::indexStraightFour(const GomokuBoard &board, bool yourSide, const Vector2 &pos, const Vector2 &vec)
{
    // . X X X X .
    for (int i = 0; i != 6; ++i)
        if (getCell(0-i) == GomokuCell::None &&
            getCell(1-i) == (yourSide ? GomokuCell::Own : GomokuCell::Opponent) &&
            getCell(2-i) == (yourSide ? GomokuCell::Own : GomokuCell::Opponent) &&
            getCell(3-i) == (yourSide ? GomokuCell::Own : GomokuCell::Opponent) &&
            getCell(4-i) == (yourSide ? GomokuCell::Own : GomokuCell::Opponent) &&
            getCell(5-i) == GomokuCell::None)
                return i;
    return -1;
}

bool BoardReader::belongFour(const GomokuBoard &board, bool yourSide, const Vector2 &pos)
{ for (const Vector2 &vec : VECTORS) if (belongFour(board, yourSide, pos, vec)) return true; return false; }
bool BoardReader::belongFour(const GomokuBoard &board, bool yourSide, const Vector2 &pos, const Vector2 &vec)
{ return indexFour(board, yourSide, pos, vec) != uint8_t(-1); }
uint8_t BoardReader::indexFour(const GomokuBoard &board, bool yourSide, const Vector2 &pos, const Vector2 &vec)
{
    // . X X X X O
    for (int i = 0; i != 6; ++i)
        if (getCell(0-i) == GomokuCell::None &&
            getCell(1-i) == (yourSide ? GomokuCell::Own : GomokuCell::Opponent) &&
            getCell(2-i) == (yourSide ? GomokuCell::Own : GomokuCell::Opponent) &&
            getCell(3-i) == (yourSide ? GomokuCell::Own : GomokuCell::Opponent) &&
            getCell(4-i) == (yourSide ? GomokuCell::Own : GomokuCell::Opponent) &&
            (getCell(5-i) == (yourSide ? GomokuCell::Opponent : GomokuCell::Own) ||
             getCell(5-i) == GomokuCell::Error))
                return i;
    return -1;
}

bool BoardReader::belongBrokenFour(const GomokuBoard &board, bool yourSide, const Vector2 &pos)
{ for (const Vector2 &vec : VECTORS) if (belongBrokenFour(board, yourSide, pos, vec)) return true; return false; }
bool BoardReader::belongBrokenFour(const GomokuBoard &board, bool yourSide, const Vector2 &pos, const Vector2 &vec)
{ return indexBrokenFour(board, yourSide, pos, vec) != uint8_t(-1); }
uint8_t BoardReader::indexBrokenFour(const GomokuBoard &board, bool yourSide, const Vector2 &pos, const Vector2 &vec)
{
    // X X . X X
    for (int i = 0; i != 5; ++i)
        if (getCell(0-i) == (yourSide ? GomokuCell::Own : GomokuCell::Opponent) &&
            getCell(1-i) == (yourSide ? GomokuCell::Own : GomokuCell::Opponent) &&
            getCell(2-i) == GomokuCell::None &&
            getCell(3-i) == (yourSide ? GomokuCell::Own : GomokuCell::Opponent) &&
            getCell(4-i) == (yourSide ? GomokuCell::Own : GomokuCell::Opponent))
                return i;
    // X . X X X
    for (int i = 0; i != 5; ++i)
        if (getCell(0-i) == (yourSide ? GomokuCell::Own : GomokuCell::Opponent) &&
            getCell(1-i) == GomokuCell::None &&
            getCell(2-i) == (yourSide ? GomokuCell::Own : GomokuCell::Opponent) &&
            getCell(3-i) == (yourSide ? GomokuCell::Own : GomokuCell::Opponent) &&
            getCell(4-i) == (yourSide ? GomokuCell::Own : GomokuCell::Opponent))
                return i;
    return -1;
}

bool BoardReader::belongThree(const GomokuBoard &board, bool yourSide, const Vector2 &pos)
{ for (const Vector2 &vec : VECTORS) if (belongThree(board, yourSide, pos, vec)) return true; return false; }
bool BoardReader::belongThree(const GomokuBoard &board, bool yourSide, const Vector2 &pos, const Vector2 &vec)
{ return indexThree(board, yourSide, pos, vec) != uint8_t(-1); }
uint8_t BoardReader::indexThree(const GomokuBoard &board, bool yourSide, const Vector2 &pos, const Vector2 &vec)
{
    // Consider . . X X X . .
    // . X X X .
    for (int i = 0; i != 5; ++i)
        if (getCell(-1-i) == GomokuCell::None &&
            getCell(0-i) == GomokuCell::None &&
            getCell(1-i) == (yourSide ? GomokuCell::Own : GomokuCell::Opponent) &&
            getCell(2-i) == (yourSide ? GomokuCell::Own : GomokuCell::Opponent) &&
            getCell(3-i) == (yourSide ? GomokuCell::Own : GomokuCell::Opponent) &&
            getCell(4-i) == GomokuCell::None &&
            getCell(5-i) == GomokuCell::None)
                return i;
    // Plus a particular case
    // O . X X X . .
    for (int i = 0; i != 6; ++i)
        if ((getCell(-1-i) == (yourSide ? GomokuCell::Opponent : GomokuCell::Own) ||
             getCell(-1-i) == GomokuCell::Error) &&
            getCell(0-i) == GomokuCell::None &&
            getCell(1-i) == (yourSide ? GomokuCell::Own : GomokuCell::Opponent) &&
            getCell(2-i) == (yourSide ? GomokuCell::Own : GomokuCell::Opponent) &&
            getCell(3-i) == (yourSide ? GomokuCell::Own : GomokuCell::Opponent) &&
            getCell(4-i) == GomokuCell::None &&
            getCell(5-i) == GomokuCell::None)
                return i;
    return -1;
}

bool BoardReader::belongBrokenThree(const GomokuBoard &board, bool yourSide, const Vector2 &pos)
{ for (const Vector2 &vec : VECTORS) if (belongBrokenThree(board, yourSide, pos, vec)) return true; return false; }
bool BoardReader::belongBrokenThree(const GomokuBoard &board, bool yourSide, const Vector2 &pos, const Vector2 &vec)
{ return indexBrokenThree(board, yourSide, pos, vec) != uint8_t(-1); }
uint8_t BoardReader::indexBrokenThree(const GomokuBoard &board, bool yourSide, const Vector2 &pos, const Vector2 &vec)
{
    // . X . X X .
    for (int i = 0; i != 6; ++i)
        if (getCell(0-i) == GomokuCell::None &&
            getCell(1-i) == (yourSide ? GomokuCell::Own : GomokuCell::Opponent) &&
            getCell(2-i) == GomokuCell::None &&
            getCell(3-i) == (yourSide ? GomokuCell::Own : GomokuCell::Opponent) &&
            getCell(4-i) == (yourSide ? GomokuCell::Own : GomokuCell::Opponent) &&
            getCell(5-i) == GomokuCell::None)
                return i;
    return -1;
}

bool BoardReader::belongWinningThreat1Turn(const GomokuBoard &board, bool yourSide, const Vector2 &pos)
{
    for (const Vector2 &vec : VECTORS)
        if (BoardReader::belongStraightFour(board, yourSide, pos, vec) ||
            BoardReader::belongFour(board, yourSide, pos, vec) ||
            BoardReader::belongBrokenFour(board, yourSide, pos, vec))
                return true;
    return false;
}

bool BoardReader::belongWinningThreat2Turn(const GomokuBoard &board, bool yourSide, const Vector2 &pos)
{
    for (const Vector2 &vec : VECTORS) {
        uint8_t r = BoardReader::indexThree(board, yourSide, pos, vec);
        if (r == 4 ||
            (r == 0 && getCell(-1) == GomokuCell::None) ||//Available with both extremities free only
            BoardReader::indexBrokenThree(board, yourSide, pos, vec) == 2)
                return true;
    }
    return false;
}

size_t BoardReader::getThreatBelonging(const GomokuBoard &board, bool yourSide, const Vector2 &pos)
{
    size_t nbThreat = 0;
    for (const Vector2 &vec : VECTORS) {
        if (belongFive(board, yourSide, pos, vec))
            ++nbThreat;
        if (belongStraightFour(board, yourSide, pos, vec))
            ++nbThreat;
        if (belongFour(board, yourSide, pos, vec))
            ++nbThreat;
        if (belongBrokenFour(board, yourSide, pos, vec))
            ++nbThreat;
        if (belongThree(board, yourSide, pos, vec))
            ++nbThreat;
        if (belongBrokenThree(board, yourSide, pos, vec))
            ++nbThreat;
    }
    return nbThreat;
}

std::deque<Vector2> BoardReader::findWinningSquares(const GomokuBoard &board, bool yourSide)
{
    std::deque<Vector2> poss;
    for (size_t y = 0; y != board.size(); ++y)
        for (size_t x = 0; x != board[y].size(); ++x) {
            if (board[y][x] != GomokuCell::None) continue;
            if (BoardReader::belongWinningThreat1Turn(board, yourSide, {x, y}))
                poss.emplace_back(x, y);
        }
    return poss;
}

std::deque<Vector2> BoardReader::getCostSquares(const GomokuBoard &board, bool yourSide, const Vector2 &pos)
{
    uint8_t r;
    for (const Vector2 &vec : VECTORS) {
        r = indexFour(board, yourSide, pos, vec);
        if (r != uint8_t(-1))
            return {{pos + vec * (-r)}};
        r = indexBrokenFour(board, yourSide, pos, vec);
        if (r != uint8_t(-1)) {
            if (getCell(2-r) == GomokuCell::None)
                return {{pos + vec * (2-r)}};
            else
                return {{pos + vec * (1-r)}};
        }
    }
    for (const Vector2 &vec : VECTORS) {
        r = indexThree(board, yourSide, pos, vec);
        if (r != uint8_t(-1)) {
            if (getCell(-1-r) == GomokuCell::None)
                return {{pos + vec * (0-r)}, {pos + vec * (4-r)}};
            else
                return {{pos + vec * (0-r)}, {pos + vec * (4-r)}, {pos + vec * (5-r)}};
        }
        r = indexBrokenThree(board, yourSide, pos, vec);
        if (r != uint8_t(-1))
            return {{pos + vec * (0-r)}, {pos + vec * (2-r)}, {pos + vec * (5-r)}};
    }
    return {};
}

bool BoardReader::belongSameThreat(const GomokuBoard &board, const Vector2 &pos1, const Vector2 &pos2)
{
    GomokuCell type = cellAt(board, pos1);
    if (pos1.first == -1 && pos1.second == -1)
        return getThreatBelonging(board, cellAt(board, pos2) == GomokuCell::Own, pos2) != 0;
    else if (type != cellAt(board, pos2)) return false;

    int deltaX = pos2.first - pos1.first, deltaY = pos2.second - pos1.second;
    if (deltaX <= -5 || deltaX >= 5 || deltaY <= -5 || deltaY >= 5 || (deltaX == 0 && deltaY == 0) ||
        !(deltaX == 0 || deltaY == 0 || abs(deltaX) == abs(deltaY)))
            return false;

    Vector2 vec = {deltaX == 0 ? 0 : (deltaX > 0 ? 1 : -1), deltaY == 0 ? 0 : (deltaY > 0 ? 1 : -1)};
    int delta = std::max(deltaX, deltaY);

    if (indexFive(board, type == GomokuCell::Own, pos1, vec) < 5-delta ||
        indexStraightFour(board, type == GomokuCell::Own, pos1, vec) < 4-delta ||
        indexFour(board, type == GomokuCell::Own, pos1, vec) < 4-delta ||
        indexFour(board, type == GomokuCell::Own, pos2, vec*-1) < 4-delta ||
        indexBrokenFour(board, type == GomokuCell::Own, pos1, vec) < 5-delta ||
        indexBrokenFour(board, type == GomokuCell::Own, pos2, vec*-1) < 5-delta ||
        indexThree(board, type == GomokuCell::Own, pos1, vec) < 3-delta ||
        indexThree(board, type == GomokuCell::Own, pos2, vec*-1) < 3-delta ||
        indexBrokenThree(board, type == GomokuCell::Own, pos1, vec) < 4-delta ||
        indexBrokenThree(board, type == GomokuCell::Own, pos2, vec*-1) < 4-delta) {
            //std::cout << pos1.first << "x" << pos1.second << " <=> " << pos2.first << "x" << pos2.second << " (" << /*beginSquare.first << "x" << beginSquare.second << ", " <<*/ vec.first << "x" << vec.second << ")" << std::endl;
            return true;
        }
    return false;
/*
    Vector2 endSquare = pos1, beginSquare = pos1 + vec * -4 + Vector2{deltaX, deltaY};
    //std::deque<std::pair<int, int>> count;
    while (beginSquare.first != endSquare.first + vec.first || beginSquare.second != endSquare.second + vec.second) {
        if (indexFive(board, type == GomokuCell::Own, beginSquare, vec) != uint8_t(-1) ||
            indexStraightFour(board, type == GomokuCell::Own, beginSquare, vec) != uint8_t(-1) ||
            indexFour(board, type == GomokuCell::Own, beginSquare, vec) != uint8_t(-1) ||
            indexBrokenFour(board, type == GomokuCell::Own, beginSquare, vec) != uint8_t(-1) ||
            indexThree(board, type == GomokuCell::Own, beginSquare, vec) != uint8_t(-1) ||
            indexBrokenThree(board, type == GomokuCell::Own, beginSquare, vec) != uint8_t(-1)) {
                std::cout << "  OK" << std::endl;;
                return true;
            }
        //count.emplace_back(0, 0);
        //for (uint8_t i = 0; i != 5; ++i) {
        //    GomokuCell cell = cellAt(board, beginSquare + vec * i);
        //    if (cell == type) ++count.back().first;
        //    else if (cell != GomokuCell::None) break;
        //    ++count.back().second;
        //}
        beginSquare = beginSquare + vec;
    }
    //std::for_each(count.begin(), count.end(), [](std::pair<int, int> v) { std::cout << "  " << v.first << "," << v.second << std::endl; });
    //return std::any_of(count.begin(), count.end(), [](std::pair<int, int> v) { return v.first >= 3 && v.second >= 5; });
    return false;*/
}

bool BoardReader::belongDoubleThreat(const GomokuBoard &board, bool yourSide, const Vector2 &pos)
{
    bool first = false;
    int firstI = 0;
    for (size_t i = 0; i != VECTORS.size(); ++i) {
        const Vector2 &vec = VECTORS[i];
        if (first && i == firstI + VECTORS.size() / 2) continue;
        if (belongStraightFour(board, yourSide, pos, vec) ||
            belongFour(board, yourSide, pos, vec) ||
            belongBrokenFour(board, yourSide, pos, vec) ||
            belongThree(board, yourSide, pos, vec) ||
            belongBrokenThree(board, yourSide, pos, vec)) {
                if (first)
                    return true;
                else
                    first = true;
                firstI = i;
        }
    }
    return false;
}
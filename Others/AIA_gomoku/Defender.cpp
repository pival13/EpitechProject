/*
** EPITECH PROJECT, 2021
** AIA_gomoku
** File description:
** Defender
*/

#include "Defender.hpp"

Defender::Defender(GomokuBoard &_board) : board{_board} {}
Defender::~Defender() {}

std::deque<Vector2> Defender::findEnemyThreat()
{
    size_t nbThreat = 1;
    std::deque<Vector2> poss;
    for (size_t y = 0; y != board.size(); ++y)
        for (size_t x = 0; x != board[y].size(); ++x) {
            if (board[y][x] != GomokuCell::None) continue;
            size_t threats = BoardReader::getThreatBelonging(board, false, {x, y});
            if (threats > nbThreat) {
                nbThreat = threats;
                poss = {{x, y}};
            } else if (threats == nbThreat)
                poss.emplace_back(x, y);
        }
    return poss;
}

std::deque<Vector2> Defender::findFarEnemyThreat()
{
    std::deque<Vector2> poss;
    for (size_t y = 0; y != board.size(); ++y)
        for (size_t x = 0; x != board[y].size(); ++x)
            if (board[y][x] == GomokuCell::None)
                poss.emplace_back(x, y);
    return selectMostFarThreat(poss);
}

std::deque<Vector2> Defender::selectMostFarThreat(const std::deque<Vector2> &threats)
{
    if (threats.size() < 2) return threats;
    size_t nbThreat = 1;
    std::deque<Vector2> poss;
    for (const Vector2 &pos : threats) {
        GomokuCell old = board[pos.second][pos.first];
        board[pos.second][pos.first] = GomokuCell::Opponent;
        size_t threats = BoardReader::getThreatBelonging(board, false, pos);
        board[pos.second][pos.first] = old;
        if (threats > nbThreat) {
            nbThreat = threats;
            poss = {pos};
        } else if (threats == nbThreat)
            poss.push_back(pos);
    }
    if (poss.size() == 0) return threats;
    return poss;
}

std::deque<Vector2> Defender::selectMostEnemyUse(const std::deque<Vector2> &threats)
{
    if (threats.size() < 2) return threats;
    size_t nbSeries = 1;
    std::deque<Vector2> poss;
    for (const Vector2 &pos : threats) {
        size_t series = 0;
        for (size_t vectI = 0; vectI != VECTORS.size() / 2; ++vectI) {
            const Vector2 &vec = VECTORS[vectI];
            size_t min = 0, max = 0;
            for (size_t i = 4; i != 0; --i) {
                if (BoardReader::cellAt(board, pos + vec * i) == GomokuCell::Opponent && max == 0) max = i;
                else if (BoardReader::cellAt(board, pos + vec * i) == GomokuCell::Own) max = 0;
                if (BoardReader::cellAt(board, pos + vec * -i) == GomokuCell::Opponent && min == 0) min = i;
                else if (BoardReader::cellAt(board, pos + vec * -i) == GomokuCell::Own) min = 0;
            }
            if (max + min > 5) series += 2;
            else if (max != 0 || min != 0) series += 1;
        }
        if (series > nbSeries) {
            nbSeries = series;
            poss = {pos};
        } else if (series == nbSeries)
            poss.push_back(pos);
    }
    if (poss.size() == 0) return threats;
    return poss;
}
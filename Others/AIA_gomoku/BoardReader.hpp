/*
** EPITECH PROJECT, 2021
** AIA_gomoku
** File description:
** BoardReader
*/

#pragma once

#include "Gomoku.hpp"

class BoardReader {
    public:
        static std::deque<Vector2> findWinningSquares(const GomokuBoard &board, bool yourSide);
        static std::deque<Vector2> getCostSquares(const GomokuBoard &board, bool yourSide, const Vector2 &pos);

        static GomokuCell cellAt(const GomokuBoard &board, const Vector2 &pos);

        static bool belongDoubleThreat(const GomokuBoard &board, bool yourSide, const Vector2 &pos2);//TODO
        static bool belongWinningThreat1Turn(const GomokuBoard &board, bool yourSide, const Vector2 &pos);
        static bool belongWinningThreat2Turn(const GomokuBoard &board, bool yourSide, const Vector2 &pos);
        static size_t getThreatBelonging(const GomokuBoard &board, bool yourSide, const Vector2 &pos);

        static bool belongSameThreat(const GomokuBoard &board, const Vector2 &pos1, const Vector2 &pos2);//TODO

        static bool belongFive(const GomokuBoard &board, bool yourSide, const Vector2 &pos, const Vector2 &vector);
        static bool belongFive(const GomokuBoard &board, bool yourSide, const Vector2 &pos);
        static bool belongStraightFour(const GomokuBoard &board, bool yourSide, const Vector2 &pos, const Vector2 &vector);
        static bool belongStraightFour(const GomokuBoard &board, bool yourSide, const Vector2 &pos);
        static bool belongFour(const GomokuBoard &board, bool yourSide, const Vector2 &pos, const Vector2 &vector);
        static bool belongFour(const GomokuBoard &board, bool yourSide, const Vector2 &pos);
        static bool belongBrokenFour(const GomokuBoard &board, bool yourSide, const Vector2 &pos, const Vector2 &vector);
        static bool belongBrokenFour(const GomokuBoard &board, bool yourSide, const Vector2 &pos);
        static bool belongThree(const GomokuBoard &board, bool yourSide, const Vector2 &pos, const Vector2 &vector);
        static bool belongThree(const GomokuBoard &board, bool yourSide, const Vector2 &pos);
        static bool belongBrokenThree(const GomokuBoard &board, bool yourSide, const Vector2 &pos, const Vector2 &vector);
        static bool belongBrokenThree(const GomokuBoard &board, bool yourSide, const Vector2 &pos);

        static uint8_t indexFive(const GomokuBoard &board, bool yourSide, const Vector2 &pos, const Vector2 &vector);
        static uint8_t indexStraightFour(const GomokuBoard &board, bool yourSide, const Vector2 &pos, const Vector2 &vector);
        static uint8_t indexFour(const GomokuBoard &board, bool yourSide, const Vector2 &pos, const Vector2 &vector);
        static uint8_t indexBrokenFour(const GomokuBoard &board, bool yourSide, const Vector2 &pos, const Vector2 &vector);
        static uint8_t indexThree(const GomokuBoard &board, bool yourSide, const Vector2 &pos, const Vector2 &vector);
        static uint8_t indexBrokenThree(const GomokuBoard &board, bool yourSide, const Vector2 &pos, const Vector2 &vector);
};

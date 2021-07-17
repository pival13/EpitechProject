/*
** EPITECH PROJECT, 2021
** AIA_gomoku
** File description:
** Defender
*/

#pragma once

#include "Gomoku.hpp"
#include "BoardReader.hpp"

class Defender {
    public:
        Defender(GomokuBoard &board);
        ~Defender();

        ///@brief Return the position of an enemy threat
        ///@return Position of a piece to erase a threat.
        std::deque<Vector2> findEnemyThreat();
        ///@brief Return the position of an enemy threat at the second or third turn
        ///@return Position of a piece to erase a threat.
        std::deque<Vector2> findFarEnemyThreat();

        ///@brief Given a list of position, return the positions which may be used on the maximum number of threat.
        ///@param threats A list of positions.
        ///@return All positions of the lists which are at the maximal threat level.
        std::deque<Vector2> selectMostFarThreat(const std::deque<Vector2> &threats);
        ///@brief Given a list of position, return the positions which may be used by the most number of enemy pieces.
        ///@param threats A list of positions.
        ///@return All positions of the lists which are usefull for the maximum number of enemy pieces.
        std::deque<Vector2> selectMostEnemyUse(const std::deque<Vector2> &threats);

    protected:
    private:
        GomokuBoard &board;
};

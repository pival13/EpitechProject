/*
** EPITECH PROJECT, 2021
** AIA_gomoku
** File description:
** ThreatSpaceSearch
*/

#pragma once

#include "Gomoku.hpp"
#include "BoardReader.hpp"

class ThreatSpaceSearch {
    //TODO Maybe store the Tree in memory, and simlpy remove branch with cost square and add branch with gain square
    public:
        struct SearchTree {
            Vector2 gain = {-1, -1};
            std::deque<Vector2> costs;
            std::map<Vector2, SearchTree> dependencies;
            std::deque<Vector2> winningDependencies;

            SearchTree &operator=(const SearchTree &t);
        };
    
    public:
        ThreatSpaceSearch(GomokuBoard &board);
        ~ThreatSpaceSearch();

        std::deque<Vector2> getNextPositions();
        void playerMove(const Vector2 &pos);
        void enemyMove(const Vector2 &pos);

    protected:
    private:
        bool expandTree(SearchTree &tree, uint8_t maxDepth); ///Increase depth of branches
        bool extendTree(SearchTree &tree); ///Add new branch
        bool containWinning(const SearchTree &tree) const;


        GomokuBoard &board;
        GomokuBoard copyBoard;
        SearchTree winningTree;
        uint8_t depthLimit = 25;
};

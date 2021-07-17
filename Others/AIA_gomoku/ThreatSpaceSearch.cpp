/*
** EPITECH PROJECT, 2021
** AIA_gomoku
** File description:
** ThreatSpaceSearch
*/

#include "ThreatSpaceSearch.hpp"

ThreatSpaceSearch::SearchTree &ThreatSpaceSearch::SearchTree::operator=(const ThreatSpaceSearch::SearchTree &t)
{
    ThreatSpaceSearch::SearchTree tmp;
    tmp.gain = t.gain;
    tmp.costs = t.costs;
    tmp.dependencies = t.dependencies;
    tmp.winningDependencies = t.winningDependencies;
    this->gain = tmp.gain;
    this->costs = tmp.costs;
    this->dependencies = tmp.dependencies;
    this->winningDependencies = tmp.winningDependencies;
    return *this;
}

ThreatSpaceSearch::ThreatSpaceSearch(GomokuBoard &board_) : board{board_}, copyBoard(board_) {}
ThreatSpaceSearch::~ThreatSpaceSearch() {}

static void drawTree(const ThreatSpaceSearch::SearchTree &t, int padding=-1)
{
    if (padding >= 0) {
        std::cout << std::string(padding, ' ') << (t.winningDependencies.empty() ? " " : "*") << t.gain.first << ',' << t.gain.second << ":";
        for (const auto &square : t.costs)
            std::cout << " " << square.first << "," << square.second;
        std::cout << std::endl;
    } else
        std::cout << "Beginning the display" << std::endl;
    for (const auto &node : t.dependencies)
        drawTree(node.second, padding+1);
}

void ThreatSpaceSearch::playerMove(const Vector2 &pos)
{
    if (std::count(winningTree.winningDependencies.begin(), winningTree.winningDependencies.end(), pos))
        winningTree = winningTree.dependencies[pos];
    else
        winningTree.winningDependencies.clear();
}

void ThreatSpaceSearch::enemyMove(const Vector2 &pos)
{
    if (winningTree.winningDependencies.empty()) return;
    if (std::none_of(winningTree.costs.begin(), winningTree.costs.end(), [&pos](const Vector2 &v) { return v == pos; })) {
        winningTree.winningDependencies.clear();
        depthLimit = 2;
    }
}

std::deque<Vector2> ThreatSpaceSearch::getNextPositions()
{
    if (winningTree.winningDependencies.empty()) {
        SearchTree tree;
        copyBoard = board;
        while (!containWinning(tree) && expandTree(tree, depthLimit) && !containWinning(tree) && extendTree(tree));
        //drawTree(tree);
        winningTree = tree;
    }

    return winningTree.winningDependencies;
}

bool ThreatSpaceSearch::containWinning(const SearchTree &tree) const
{ return !tree.winningDependencies.empty(); }

bool ThreatSpaceSearch::expandTree(SearchTree &tree, uint8_t maxDepth)
{
    if (maxDepth == 0) return false;
    bool ret = false;
    if (!tree.dependencies.empty()) {
        for (auto node : tree.dependencies)
            if (expandTree(node.second, maxDepth-1))
                ret = true;
        return ret;
    }
    for (int y = 0; y != int(copyBoard.size()); ++y)
        for (int x = 0; x != int(copyBoard[y].size()); ++x) {
            if (copyBoard.at(y).at(x) != GomokuCell::None  || (x == tree.gain.first && y == tree.gain.second)) continue;
            copyBoard[y][x] = GomokuCell::Own;
            if (BoardReader::belongSameThreat(copyBoard, tree.gain, {x, y})) {
                ret = true;
                SearchTree &dep = tree.dependencies[{x, y}];
                dep.gain = {x, y};
                dep.costs = BoardReader::getCostSquares(copyBoard, true, {x, y});

                if (!BoardReader::belongFive(copyBoard, true, {x, y}) &&
                    !BoardReader::belongDoubleThreat(copyBoard, true, {x, y}))
                {
                    for (const Vector2 &cost : dep.costs)
                        copyBoard[cost.second][cost.first] = GomokuCell::Opponent;
                    expandTree(dep, maxDepth-1);
                    for (const Vector2 &cost : dep.costs)
                        copyBoard[cost.second][cost.first] = GomokuCell::None;
                    
                    if (!tree.dependencies[{x,y}].winningDependencies.empty())
                        tree.winningDependencies.emplace_back(x, y);
                } else
                    tree.winningDependencies.emplace_back(x, y);
            }
            copyBoard[y][x] = GomokuCell::None;
        }
    return ret;
}

bool ThreatSpaceSearch::extendTree(SearchTree &tree)
{
    return true;
}
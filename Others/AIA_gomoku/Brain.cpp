#include "Brain.hpp"

Brain::Brain(size_t sizeX, size_t sizeY)
: board(sizeY, std::vector<GomokuCell>(sizeX, None))
, defender(board), tss(board)
{ std::cout << "OK" << std::endl; }

void Brain::initBoard()
{
    std::regex parser("^(\\d+),(\\d+),(\\d)$");
    std::smatch matches;
    while (true) {
        std::string s;
        std::getline(std::cin, s);
        if (std::regex_match(s, matches, parser)) {
            if (matches[3] == "1") {
                board[std::stoi(matches[2])][std::stoi(matches[1])] = Own;
            } else if (matches[3] == "2") {
                board[std::stoi(matches[2])][std::stoi(matches[1])] = Opponent;
            } else {
                error << "Unsupported field value: " << matches[3] << std::endl;
            }
        } else if (s == "DONE") {
            break;
        } else {
            std::cout << "UNKNOW " << "Expected either a coordinate (three coma-separated numbers) or \"DONE\", but got \"" << s << "\"" << std::endl;
        }
    }
}

std::deque<Vector2> Brain::selectMostUse(const std::deque<Vector2> &squares)
{
    if (squares.size() < 2) return squares;
    size_t nbThreat = 1;
    std::deque<Vector2> poss;
    for (const Vector2 &pos : squares) {
        int count = 0;
        for (const Vector2 &vec : VECTORS) if (BoardReader::cellAt(board, pos + vec) == GomokuCell::Own) ++count;
        if (count < nbThreat) continue;
        GomokuCell old = board[pos.second][pos.first];
        board[pos.second][pos.first] = GomokuCell::Own;
        size_t threatsCount = BoardReader::getThreatBelonging(board, true, pos);
        board[pos.second][pos.first] = old;
        if (threatsCount > 0) continue;
        if (count > nbThreat) {
            nbThreat = count;
            poss = {pos};
        } else if (count == nbThreat)
            poss.push_back(pos);
    }
    if (poss.size() == 0) return squares;
    return poss;
}

void Brain::makeAMove()
{
    if (begin) {
        begin = false;
        std::cout << board[0].size() / 2 << "," << board.size() / 2 << std::endl;
        board[board.size() / 2][board[0].size() / 2] = Own;
        return;
    }

    std::deque<Vector2> poss;
    poss = BoardReader::findWinningSquares(board, true);
    if (poss.empty()) {
        poss = BoardReader::findWinningSquares(board, false);
        if (poss.empty()) {
            poss = defender.selectMostEnemyUse(defender.selectMostFarThreat(defender.findEnemyThreat()));
            if (poss.empty()) {
                poss = defender.selectMostEnemyUse(defender.selectMostFarThreat(tss.getNextPositions()));
                if (poss.empty()) {
                    poss = defender.selectMostEnemyUse(selectMostUse(defender.findFarEnemyThreat()));
                    if (poss.empty()) {
                        //for (size_t y = 0; y != board.size(); ++y)
                        //    for (size_t x = 0; x != board[y].size(); ++x)
                        //        if (BoardReader::cellAt(board, {x, y}) == GomokuCell::None) poss.emplace_back(x, y);
                        //poss = defender.selectMostEnemyUse(/*selectMostUse*/(poss));
                        if (poss.empty()) {
                            int x = 0, y = 0;
                            do {
                                x = rand() % board[0].size();
                                y = rand() % board.size();
                            } while (BoardReader::cellAt(board, {x, y}) != GomokuCell::None);
                            poss = {{x, y}};
                        }
                    }
                }
            }
        }
    }
    Vector2 pos = poss[rand() % poss.size()];
    tss.playerMove(pos);
    board[pos.second][pos.first] = Own;
    std::cout << pos.first << "," << pos.second << std::endl;
    //for (const auto &row : board) {
    //    for (const auto &cell : row) {
    //        if (cell == GomokuCell::Own)
    //            std::cout << "()";
    //        else if (cell == GomokuCell::Opponent)
    //            std::cout << "<>";
    //        else
    //            std::cout << "  ";
    //    }
    //    std::cout << std::endl;
    //}
}

void Brain::parseMessage(const std::string &msg)
{
    static const std::regex rBegin = std::regex("^BEGIN$");
    static const std::regex rTurn = std::regex("^TURN (\\d+),(\\d+)$");
    static const std::regex rBoard = std::regex("^BOARD$");
    static const std::regex rInfo = std::regex("^INFO (\\w+) (.+)");
    static const std::regex rEnd = std::regex("^END$");
    static const std::regex rAbout = std::regex("^ABOUT$");
    std::smatch matches;

    if (std::regex_match(msg, rBegin)) {
        begin = true;
        makeAMove();
    } else if (std::regex_match(msg, matches, rTurn)) {
        int x = std::stoi(matches[1]), y = std::stoi(matches[2]);
        board[y][x] = Opponent;
        tss.enemyMove({x, y});
        makeAMove();
    } else if (std::regex_match(msg, rBoard)) {
        initBoard();
        makeAMove();
    } else if (std::regex_match(msg, matches, rInfo)) {
        debug << matches[1] << ": " << matches[2] << std::endl;
    } else if (std::regex_match(msg, rEnd)) {
        running = false;
    } else if (std::regex_match(msg, rAbout)) {
        std::cout << "name=\"Pival & Juliettead\", version=\"0.1\", country=\"France, NCY\"" << std::endl;
    } else {
        std::cout << "UNKNOW " << msg << std::endl;
    }
}

int Brain::run()
{
    while (running && !std::cin.eof()) {
        std::string s;
        std::getline(std::cin, s);
        parseMessage(s);
    }
    if (std::cin.eof()) return 84;
    return 0;
}

bool operator==(const Vector2 &v1, const Vector2 &v2)
{
    return v1.first == v2.first && v1.second == v2.second;
}

Vector2 operator+(const Vector2 &v1, const Vector2 &v2)
{
    return {v1.first+v2.first, v1.second+v2.second};
}

Vector2 operator*(const Vector2 &v1, int c)
{
    return {v1.first*c, v1.second*c};
}
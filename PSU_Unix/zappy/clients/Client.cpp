/*
** By Kevin Pruvost, May 2020
** Client.cpp
** File description:
** client
*/

#include "Client.hpp"

bool interrupted = false;
Mutex gameMutex;

static void signalHandler(int sig)
{
    if (sig == SIGINT) {
        interrupted = true;
    }
}

Client::Client(const char * ip, uint16_t port, const std::string & teamName)
    : clientSocket(ip, port)
    , _myTeamName { teamName }
{
    signal(SIGINT, signalHandler);

    thread = std::thread([&](){
        while (!interrupted)
        {
            try {
                int ret = 0;
                if ((ret = clientSocket.readServer()) == EXIT_FAILURE)
                {
                    std::cerr << "Server connection was interrupted." << std::endl;
                    break;
                }
                if (ret == EXIT_PASS)
                    continue;
            } catch (const std::exception & e) {
                break;
            }
            _lastResponse = clientSocket.getLastResponse();
            while (!_lastResponse.empty())
            {
                while (!_lastResponse.empty() && parseWelcome(_lastResponse) == EXIT_SUCCESS)
                {
                    while (!_lastResponse.empty() && _lastResponse[0] != "\n")
                        _lastResponse.removeAt(0);
                    if (!_lastResponse.empty() && _lastResponse[0] == "\n")
                        _lastResponse.removeAt(0);
                }
                parseLastResponse();
                parsedNotified = true;
                parsed.notify_all();
                while (!_lastResponse.empty() && _lastResponse[0] != "\n")
                    _lastResponse.removeAt(0);
                if (!_lastResponse.empty() && _lastResponse[0] == "\n")
                    _lastResponse.removeAt(0);
            }
        }
        interrupted = true;
        _loggedCond.notify_all();
        closed = true;
    });
}

Client::Client(const std::string & ip, const std::string & port, const std::string & teamName)
    : Client(ip.c_str(), std::stoi(port), teamName)
{
}

Client::~Client()
{
    interrupted = true;
    thread.join();
}

// COMMANDS TO SEND ------------------------------------------------------------

Position Client::getMapSize()
{
    sendRequest("msz");
    waitForParsed();
    return _mapSize;
}

Tile Client::getTileContent(int x, int y)
{
    sendRequest("bct " + STR(x) + " " + STR(y));
    waitForParsed();
    return _tilesContent[x][y];
}

Tile Client::getTileContent(const Position & pos)
{
    return getTileContent(pos.x, pos.y);
}

KVector<KVector<Tile>> Client::getEveryTilesContent()
{
    sendRequest("mct");
    waitForParsed();
    return _tilesContent;
}

KVector<std::string> Client::getTeamsName()
{
    _teamsNames.clear();
    sendRequest("tna");
    waitForParsed();
    return _teamsNames;
}

Position Client::getPlayerPosition(int playerId)
{
    sendRequest("ppo " + STR(playerId));
    waitForParsed();
    for (auto & player : _players)
        if (player.id == playerId)
            return player.position;
    return Position();
}

int Client::getPlayerLevel(int playerId)
{
    sendRequest("plv " + STR(playerId));
    waitForParsed();
    for (auto & player : _players)
        if (player.id == playerId)
            return player.level;
    return -1;
}

InventoryData Client::getPlayerInventory(int playerId)
{
    sendRequest("pin " + STR(playerId));
    waitForParsed();
    for (auto & player : _players)
        if (player.id == playerId)
            return player.inventory;
    return InventoryData();
}

int Client::getTimeUnit()
{
    sendRequest("sgt");
    waitForParsed();
    return _timeUnit;
}

void Client::setTimeUnit(int set)
{
    sendRequest("sst " + STR(set));
}

void Client::waitForParsed()
{
    std::unique_lock<std::mutex> lock(gameMutex);
    parsedNotified = false;
    while (!parsedNotified && !interrupted)
    {
        parsed.wait_for(lock, std::chrono::milliseconds(500));
    }
}

// PARSING ---------------------------------------------------------------------

void Client::parseLastResponse()
{
    static const std::map<std::string, std::pair<void (Client::*)(const KVector<std::string> &), GraphEvent>> funcs = {
        {"msz", {&Client::parseMsz, GraphEvent::MSZ}},
        {"bct", {&Client::parseBct, GraphEvent::BCT}},
        {"tna", {&Client::parseTna, GraphEvent::TNA}},
        {"pnw", {&Client::parsePnw, GraphEvent::PNW}},
        {"ppo", {&Client::parsePpo, GraphEvent::PPO}},
        {"plv", {&Client::parsePlv, GraphEvent::PLV}},
        {"pin", {&Client::parsePin, GraphEvent::PIN}},
        {"pex", {&Client::parsePex, GraphEvent::PEX}},
        {"pbc", {&Client::parsePbc, GraphEvent::PBC}},
        {"pic", {&Client::parsePic, GraphEvent::PIC}},
        {"pie", {&Client::parsePie, GraphEvent::PIE}},
        {"pfk", {&Client::parsePfk, GraphEvent::PFK}},
        {"pdr", {&Client::parsePdr, GraphEvent::PDR}},
        {"pgt", {&Client::parsePgt, GraphEvent::PGT}},
        {"pdi", {&Client::parsePdi, GraphEvent::PDI}},
        {"enw", {&Client::parseEnw, GraphEvent::ENW}},
        {"eht", {&Client::parseEht, GraphEvent::EHT}},
        {"ebo", {&Client::parseEbo, GraphEvent::EBO}},
        {"edi", {&Client::parseEdi, GraphEvent::EDI}},
        {"sgt", {&Client::parseSgt, GraphEvent::SGT}},
        {"sst", {&Client::parseSst, GraphEvent::SST}},
        {"seg", {&Client::parseSeg, GraphEvent::SEG}},
        {"smg", {&Client::parseSmg, GraphEvent::SMG}},
        {"suc", {&Client::parseSuc, GraphEvent::SUC}},
        {"sbp", {&Client::parseSbp, GraphEvent::SBP}},
        {"dead", {&Client::parseDead, GraphEvent::DEAD}},
        {"message", {&Client::parseBroadcastMessage, GraphEvent::MESSAGE}}
    };

    gameMutex.lock(LINE());
    while (!_lastResponse.empty())
    {
        if (funcs.find(_lastResponse[0]) == funcs.end())
        {
            if (parseAi(_lastResponse) == EXIT_FAILURE)
            {
                _lastResponse.clear();
                gameMutex.unlock();
                return;
            }
        }
        else
        {
            try {
                (this->*funcs.at(_lastResponse[0]).first)(_lastResponse);
                _graphEvents.push_back(funcs.at(_lastResponse[0]).second);
            } catch (const std::exception & e) {
                std::cerr << "Event " << _lastResponse[0] << " crashed : " << e.what() << std::endl;
            }
        }

        while (!_lastResponse.empty() && _lastResponse[0] != "\n")
            _lastResponse.removeAt(0);
        if (!_lastResponse.empty() && _lastResponse[0] == "\n")
            _lastResponse.removeAt(0);
    }
    gameMutex.unlock();
}

void Client::parseMsz(const KVector<std::string> & param)
{
    _mapSize.x = std::stoi(param[1]);
    _mapSize.y = std::stoi(param[2]);

    while (_mapSize.x > (ssize_t)_tilesContent.size())
        _tilesContent.emplace_back();

    for (size_t i = 0; i < _tilesContent.size(); ++i)
    {
        while (_mapSize.y > (ssize_t)_tilesContent[i].size())
            _tilesContent[i].emplace_back();
    }

    _clientDatas.emplace_back(true);
}

void Client::parseBct(const KVector<std::string> & param)
{
    int x = std::stoi(param[1]);
    int y = std::stoi(param[2]);

    _tilesContent[x][y].inventory.food      = std::stoi(param[3]);
    _tilesContent[x][y].inventory.linemate  = std::stoi(param[4]);
    _tilesContent[x][y].inventory.deraumere = std::stoi(param[5]);
    _tilesContent[x][y].inventory.sibur     = std::stoi(param[6]);
    _tilesContent[x][y].inventory.mendiane  = std::stoi(param[7]);
    _tilesContent[x][y].inventory.phiras    = std::stoi(param[8]);
    _tilesContent[x][y].inventory.thystmane = std::stoi(param[9]);

    _clientDatas.emplace_back(Position(x, y));
}

void Client::parseTna(const KVector<std::string> & param)
{
    _teamsNames.push_back(param[1]);

    _clientDatas.emplace_back(param[1]);
}

void Client::parsePnw(const KVector<std::string> & param)
{
    _players.emplace_back();
    _players.back().id = std::stoi(param[1]);
    _players.back().position.x = std::stoi(param[2]);
    _players.back().position.y = std::stoi(param[3]);
    _players.back().orientation = PlayerData::Orientation(std::stoi(param[4]));
    _players.back().level = std::stoi(param[5]);
    _players.back().teamName = param[6];

    _clientDatas.emplace_back(_players.back());
    _clientDatas.back().integer = 1;
}

void Client::parsePpo(const KVector<std::string> & param)
{
    try {
        auto & player = findPlayerById(std::stoi(param[1]));

        player.position.x = std::stoi(param[2]);
        player.position.y = std::stoi(param[3]);
        player.orientation = PlayerData::Orientation(std::stoi(param[4]));
        _clientDatas.emplace_back(player);
    } catch (const std::exception & e) {
        std::cerr << e.what() << std::endl;
        _clientDatas.emplace_back(true);
    }

}

void Client::parsePlv(const KVector<std::string> & param)
{
    try {
        auto & player = findPlayerById(std::stoi(param[1]));

        player.level = std::stoi(param[2]);
        _clientDatas.emplace_back(player);
    } catch (const std::exception & e) {
        std::cerr << e.what() << std::endl;
        _clientDatas.emplace_back(false);
    }
}

void Client::parsePin(const KVector<std::string> & param)
{
    try {
        auto & player = findPlayerById(std::stoi(param[1]));

        player.position.x = std::stoi(param[2]);
        player.position.y = std::stoi(param[3]);
        player.inventory.food       = std::stoi(param[4]);
        player.inventory.linemate   = std::stoi(param[5]);
        player.inventory.deraumere  = std::stoi(param[6]);
        player.inventory.sibur      = std::stoi(param[7]);
        player.inventory.mendiane   = std::stoi(param[8]);
        player.inventory.phiras     = std::stoi(param[9]);
        player.inventory.thystmane  = std::stoi(param[10]);
        _clientDatas.emplace_back(player);
    } catch (const std::exception & e) {
        std::cerr << e.what() << std::endl;
        _clientDatas.emplace_back(false);
    }
}

void Client::parsePex(const KVector<std::string> & param)
{
    _clientDatas.emplace_back(std::stoi(param[1]));
}

void Client::parsePbc(const KVector<std::string> & param)
{
    _broadcastGraphicalMessage.first = std::stoi(param[1]);
    _broadcastGraphicalMessage.second.clear();
    for (size_t i = 2; i < param.size() && param[i] != "\n"; ++i)
        _broadcastGraphicalMessage.second += param[i];

    _clientDatas.emplace_back(_broadcastGraphicalMessage.first);
    _clientDatas.back().string = _broadcastGraphicalMessage.second;
}

void Client::parsePic(const KVector<std::string> & param)
{
    int x = std::stoi(param[1]);
    int y = std::stoi(param[2]);
    int level = std::stoi(param[3]);

    ClientData clData(Position(x, y));

    for (size_t i = 4; i < param.size() && param[i] != "\n"; ++i)
    {
        findPlayerById(std::stoi(param[i])).isIncanting = true;
        findPlayerById(std::stoi(param[i])).isIncantingToLvl = level;
        clData.dataSupp.emplace_back(std::stoi(param[i]));
    }
    _clientDatas.emplace_back(clData);
}

void Client::parsePie(const KVector<std::string> & param)
{
    bool result = (std::stoi(param[3]) == 1) ? true : false;
    int x = std::stoi(param[1]);
    int y = std::stoi(param[2]);

    for (auto & player : _players)
    {
        if (player.position.x == x && player.position.y == y && player.isIncanting)
        {
            player.isIncanting = false;
            if (result)
                player.level = player.isIncantingToLvl;
            player.isIncantingToLvl = 0;
        }
    }
    _clientDatas.emplace_back(Position(x, y));
    _clientDatas.back().boolean = result;
}

void Client::parsePfk(const KVector<std::string> & param)
{
    int id = std::stoi(param[1]);

    for (auto & player : _players)
    {
        if (player.id == id)
        {
            player.isLayingEgg = true;
            break;
        }
    }
    _clientDatas.emplace_back(id);
}

void Client::parsePdr(const KVector<std::string> & param)
{
    int id = std::stoi(param[1]);
    int resourceId = std::stoi(param[2]);

    _clientDatas.emplace_back(id);
    _clientDatas.back().dataSupp.emplace_back(resourceId);
}

void Client::parsePgt(const KVector<std::string> & param)
{
    int id = std::stoi(param[1]);
    int resourceId = std::stoi(param[2]);

    _clientDatas.emplace_back(id);
    _clientDatas.back().dataSupp.emplace_back(resourceId);
}

void Client::parsePdi(const KVector<std::string> & param)
{
    int id = std::stoi(param[1]);

    for (auto & player : _players)
    {
        if (player.id == id)
        {
            player.dead = true;
            break;
        }
    }
    _clientDatas.emplace_back(id);
}

void Client::parseEnw(const KVector<std::string> & param)
{
    int id = std::stoi(param[2]);
    int x = std::stoi(param[3]);
    int y = std::stoi(param[4]);

    _eggs.emplace_back();
    _eggs.back().position.x = x;
    _eggs.back().position.y = y;
    _eggs.back().id = std::stoi(param[1]);
    _eggs.back().laidBy = std::stoi(param[2]);
    for (auto & player : _players)
    {
        if (player.id == id && player.position.x == x && player.position.y == y)
        {
            player.isLayingEgg = false;
            break;
        }
    }

    _clientDatas.emplace_back(_eggs.back());
    _clientDatas.back().integer = id;
}

void Client::parseEht(const KVector<std::string> & param)
{
    int id = std::stoi(param[1]);

    for (auto egg = _eggs.begin(); egg != _eggs.end(); ++egg)
    {
        if (egg->id == id)
        {
            egg->isHatching = true;
            break;
        }
    }

    _clientDatas.emplace_back(id);
}

void Client::parseEbo(const KVector<std::string> & param)
{
    int id = std::stoi(param[1]);

    for (auto egg = _eggs.begin(); egg != _eggs.end(); ++egg)
    {
        if (egg->id == id)
        {
            _players.emplace_back(*egg);
            break;
        }
    }

    _clientDatas.emplace_back(true);
}

void Client::parseEdi(const KVector<std::string> & param)
{
    int id = std::stoi(param[1]);

    for (auto egg = _eggs.begin(); egg != _eggs.end(); ++egg)
    {
        if (egg->id == id && egg->isHatching)
        {
            _eggs.removeAt(egg);
            break;
        }
    }

    _clientDatas.emplace_back(true);
}

void Client::parseSgt(const KVector<std::string> & param)
{
    _timeUnit = std::stoi(param[1]);

    _clientDatas.emplace_back(_timeUnit);
}

void Client::parseSst(const KVector<std::string> & param)
{
    _timeUnit = std::stoi(param[1]);

    _clientDatas.emplace_back(_timeUnit);
}

void Client::parseSeg(const KVector<std::string> & param)
{
    _ended = true;
    _endingTeam = param[1];

    _clientDatas.emplace_back(_endingTeam);
}

void Client::parseSmg(const KVector<std::string> & param)
{
    _serverMsg = param[1];

    _clientDatas.emplace_back(_serverMsg);
}

void Client::parseSuc(const KVector<std::string> &)
{
    using namespace std;

    cerr << "[SERVER]: Unknown command." << endl;
    _clientDatas.emplace_back(false);
}

void Client::parseSbp(const KVector<std::string> &)
{
    using namespace std;

    cerr << "[SERVER]: Command parameter." << endl;
    _clientDatas.emplace_back(false);
}
/*******************************************************************************
***                          Parsing AI requests                             ***
*******************************************************************************/

int Client::parseAi(const KVector<std::string> & param)
{
    static const std::map<std::string, std::pair<void (Client::*)(const KVector<std::string> &), AiOrder>> funcs1 = {
        {"dead", {&Client::parseDead, AiOrder::DED}},
        {"eject:", {&Client::parseEjected, AiOrder::EJC}},
        {"Elevation", {&Client::parseStartIncantation, AiOrder::INC}}
    };

    static const std::map<AiOrder, void (Client::*)(const KVector<std::string> &)> funcs = {
        {AiOrder::FWD, &Client::parseForward},
        {AiOrder::LFT, &Client::parseLeft},
        {AiOrder::RGT, &Client::parseRight},
        {AiOrder::BDC, &Client::parseBroadcast},
        {AiOrder::UTS, &Client::parseUnusedTeamSlotsNumber},
        {AiOrder::FPL, &Client::parseForkPlayer},
        {AiOrder::EPL, &Client::parseEjectPlayers},
        {AiOrder::LAR, &Client::parseLookAround},
        {AiOrder::INV, &Client::parseInventory},
        {AiOrder::INC, &Client::parseStartIncantation},
        {AiOrder::EINC, &Client::parseEndIncantation},
        {AiOrder::TOJ, &Client::parseTakeObject},
        {AiOrder::SOJ, &Client::parseSetObjectDown}
    };

    if (funcs1.find(_lastResponse[0]) != funcs1.end())
    {
        if (!_clientWaitingOrder.empty() && _clientWaitingOrder[0] == AiOrder::INC && _lastResponse[0] == "Elevation")
            _clientWaitingOrder.removeAt(0);
        (this->*funcs1.at(_lastResponse[0]).first)(param);
        return EXIT_SUCCESS;
    }

    if (!_clientWaitingOrder.empty())
    {
        if (funcs.find(_clientWaitingOrder[0]) != funcs.end())
        {
            auto order = _clientWaitingOrder[0];
            _clientWaitingOrder.removeAt(0);
            (this->*funcs.at(order))(param);
            return EXIT_SUCCESS;
        }
    }
    return EXIT_FAILURE;
}

void Client::parseDead(const KVector<std::string> &)
{
    _dead = true;
    interrupted = true;
    _aiOrders.emplace_back(AiOrder::DED);
    _clientDatas.emplace_back(_dead);
}

void Client::parseForward(const KVector<std::string> & param)
{
    _forward = (param[0] == "ok");
    _aiOrders.emplace_back(AiOrder::FWD);
    _clientDatas.emplace_back(_forward);
}

void Client::parseLeft(const KVector<std::string> & param)
{
    _left = (param[0] == "ok");
    _aiOrders.emplace_back(AiOrder::LFT);
    _clientDatas.emplace_back(_left);
}

void Client::parseRight(const KVector<std::string> & param)
{
    _right = (param[0] == "ok");
    _aiOrders.emplace_back(AiOrder::RGT);
    _clientDatas.emplace_back(_right);
}

void Client::parseBroadcast(const KVector<std::string> & param)
{
    _broadcasted = (param[0] == "ok");
    _aiOrders.emplace_back(AiOrder::BDC);
    _clientDatas.emplace_back(_broadcasted);
}

void Client::parseBroadcastMessage(const KVector<std::string> & param)
{
    std::string tile = param[1];
    if (tile[tile.size() - 1] == ',')
        tile[tile.size() - 1] = 0;

    _broadcastMessageLocation = std::stoi(tile);
    _broadcastMessage = param[2];
    for (size_t i = 3; i < param.size() && param[i] != "\n"; ++i)
    {
        _broadcastMessage += " " + param[i];
    }

    _aiOrders.emplace_back(AiOrder::MSG);
    _clientDatas.emplace_back(_broadcastMessage);
    _clientDatas.back().integer = _broadcastMessageLocation;
}

void Client::parseUnusedTeamSlotsNumber(const KVector<std::string> & param)
{
    _unusedTeamSlotsNumber = std::stoi(param[0]);
    _aiOrders.emplace_back(AiOrder::UTS);
    _clientDatas.emplace_back(_unusedTeamSlotsNumber);
}

void Client::parseForkPlayer(const KVector<std::string> & param)
{
    _forked = (param[0] == "ok");
    _aiOrders.emplace_back(AiOrder::FPL);
    _clientDatas.emplace_back(_forked);
}

void Client::parseEjectPlayers(const KVector<std::string> & param)
{
    _ejectPlayersReturnCode = (param[0] == "ok");
    _aiOrders.emplace_back(AiOrder::EPL);
    _clientDatas.emplace_back(_ejectPlayersReturnCode);
}

void Client::parseLookAround(const KVector<std::string> & param)
{
    KVector<std::string> command;

//    std::cout << "LOOK PARAM :" << param << std::endl;

    for (size_t i = 0; i < param.size() && param[i] != "\n"; ++i)
    {
        command.push_back(param[i]);
        while (!command.back().empty() && command.back()[0] == ' ')
            command.back() = command.back().substr(1);
        if (!command.back().empty())
        {
            while (!command.back().empty() && command.back()[command.back().size() - 1] == ' ')
                command.back() = command.back().substr(0, command.back().size() - 1);
        }
    }

    std::string line;

    for (const auto & str : command)
    {
        if (!str.empty())
            line += str + " ";
    }

    line = line.substr(0, line.size() - 1);
    if (!line.empty())
    {
        while (line[0] == '[' || line[0] == ' ')
            line = line.substr(1);
    }
    if (!line.empty())
    {
        while (line[line.size() - 1] == ']' || line[line.size() - 1] == ' ')
            line = line.substr(0, line.size() - 1);
    }


//    std::cout << "LOOK STRING : \n" << line << std::endl;

    _look = splitString(line, ",");
    if (!line.empty() && line[line.size() - 1] == ',')
        _look.emplace_back();

    for (auto & part : _look)
    {
        while (!part.empty() && part[0] == ' ')
            part = part.substr(1);
        while (!part.empty() && part[part.size() - 1] == ' ')
            part = part.substr(0, part.size() - 1);
    }
//    std::cout << "LOOK RESULT : \n\n" << _look << std::endl;

    _aiOrders.emplace_back(AiOrder::LAR);
    _clientDatas.emplace_back(_look);
}

void Client::parseInventory(const KVector<std::string> & param)
{
    KVector<std::string> command;

    for (size_t i = 0; i < param.size() && param[i] != "\n"; ++i)
        command.push_back(param[i]);

    std::string line;

    for (const auto & str : command)
    {
        line += str + " ";
    }
    line = line.substr(0, line.size() - 1);
    if (line[0] == '[')
        line = line.substr(1);
    if (line[line.size() - 1] == ']')
        line = line.substr(0, line.size() - 1);

    _inventory = splitString(line, ",");

    _aiOrders.emplace_back(AiOrder::INV);
    _clientDatas.emplace_back(_inventory);
}

void Client::parseEndIncantation(const KVector<std::string> & param)
{
    _incantationReturnLevel = 0;
    _incantationReturnCode = false;
    if (param[0] == "ko")
    {
        _incantationReturnCode = false;
        _aiOrders.emplace_back(AiOrder::EINC);
        _clientDatas.emplace_back(_incantationReturnCode);
        return;
    }
    if (param[0] == "Current" && param[1] == "level:")
    {
        _incantationReturnCode = true;
        _incantationReturnLevel = std::stoi(param[2]);
    }

    _aiOrders.emplace_back(AiOrder::EINC);
    _clientDatas.emplace_back(_incantationReturnCode);
    _clientDatas.back().integer = _incantationReturnLevel;
}

void Client::parseStartIncantation(const KVector<std::string> & param)
{
    if (param[0] == "ko")
    {
        _incantationReturnCode = false;
        _aiOrders.emplace_back(AiOrder::INC);
        _clientDatas.emplace_back(_incantationReturnCode);
        return;
    }
    if (param[0] == "Elevation" && param[1] == "underway")
        _incantationReturnCode = true;

    _aiOrders.emplace_back(AiOrder::INC);
    _clientDatas.emplace_back(_incantationReturnCode);
    auto orders = _clientWaitingOrder;
    _clientWaitingOrder.clear();
    _clientWaitingOrder.push_back(AiOrder::EINC);
    for (const auto & order : orders)
        _clientWaitingOrder.push_back(order);
}

void Client::parseTakeObject(const KVector<std::string> & param)
{
    _takeObjectReturnCode = (param[0] == "ok");

    _aiOrders.emplace_back(AiOrder::TOJ);
    _clientDatas.emplace_back(_takeObjectReturnCode);
}

void Client::parseSetObjectDown(const KVector<std::string> & param)
{
    _setObjectDownReturnCode = (param[0] == "ok");

    _aiOrders.emplace_back(AiOrder::SOJ);
    _clientDatas.emplace_back(_setObjectDownReturnCode);
}

void Client::parseEjected(const KVector<std::string> & param)
{
    _ejectedByPos = std::stoi(param[1]);

    _aiOrders.emplace_back(AiOrder::EJC);
    _clientDatas.emplace_back(_ejectedByPos);
}

// AI COMMANDS -----------------------------------------------------------------

void Client::moveForward()
{
    _clientWaitingOrder.push_back(AiOrder::FWD);
    sendRequest("Forward");
}

void Client::rotateLeft()
{
    _clientWaitingOrder.push_back(AiOrder::LFT);
    sendRequest("Left");
}

void Client::rotateRight()
{
    _clientWaitingOrder.push_back(AiOrder::RGT);
    sendRequest("Right");
}

void Client::broadcastText(const std::string & str)
{
    _clientWaitingOrder.push_back(AiOrder::BDC);
    sendRequest("Broadcast " + str);
}

void Client::unusedTeamSlotsNumber()
{
    _clientWaitingOrder.push_back(AiOrder::UTS);
    sendRequest("Connect_nbr");
}

void Client::forkPlayer()
{
    _clientWaitingOrder.push_back(AiOrder::FPL);
    sendRequest("Fork");
}

void Client::ejectPlayers()
{
    _clientWaitingOrder.push_back(AiOrder::EPL);
    sendRequest("Eject");
}

void Client::takeObject(const std::string & object)
{
    _clientWaitingOrder.push_back(AiOrder::TOJ);
    sendRequest("Take " + object);
}

void Client::setObjectDown(const std::string & object)
{
    _clientWaitingOrder.push_back(AiOrder::SOJ);
    sendRequest("Set " + object);
}

void Client::lookAround()
{
    _clientWaitingOrder.push_back(AiOrder::LAR);
    sendRequest("Look");
}

void Client::inventory()
{
    _clientWaitingOrder.push_back(AiOrder::INV);
    sendRequest("Inventory");
}

void Client::startIncantation()
{
    _clientWaitingOrder.push_back(AiOrder::INC);
    sendRequest("Incantation");
}

bool Client::isDead()
{
    return _dead;
}

PlayerData & Client::findPlayerById(int id)
{
    for (auto & player : _players)
        if (player.id == id)
            return player;
    throw EXCEPTION("Wrong player id.");
}

static bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

int Client::parseWelcome(const KVector<std::string> & param)
{
    static int state = 0;

    if (state == 3)
        return EXIT_FAILURE;

    if (param[0] == "ko")
    {
        connectionFailed = true;
        interrupted = true;
    }

    if (state == 1 && _myTeamName == "GRAPHIC" && param[0] == "msz")
    {
        state = 3;
        parseMsz(param);
        _clientDatas.removeLast();
        gameMutex.lock(LINE());
        _logged = true;
        gameMutex.unlock();
        _loggedCond.notify_all();
        return EXIT_SUCCESS;
    }

    if (param[0] == "WELCOME" && state == 0)
    {
        state = 1;
        clientSocket.sendRequest(_myTeamName);
        return EXIT_SUCCESS;
    }
    if (state == 1 && is_number(param[0]))
    {
        _unusedTeamSlotsNumber = std::stoi(param[0]);
        _aiOrders.emplace_back(AiOrder::UTS);
        _clientDatas.emplace_back(_unusedTeamSlotsNumber);
        state = 2;
        return EXIT_SUCCESS;
    }
    if (state == 2 && is_number(param[0]) && is_number(param[1]))
    {
        _mapSize.x = std::stoi(param[0]);
        _mapSize.y = std::stoi(param[1]);
        _aiOrders.emplace_back(AiOrder::MPS);
        _graphEvents.emplace_back(GraphEvent::MSZ);
        _clientDatas.emplace_back(_mapSize);
        state = 3;
        gameMutex.lock(LINE());
        _logged = true;
        gameMutex.unlock();
        _loggedCond.notify_all();
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

int Client::sendRequest(const std::string & request)
{
    while (!_logged && !interrupted)
    {
        std::unique_lock<std::mutex> lock(gameMutex);
        _loggedCond.wait(lock);
    }
    if (interrupted)
        return EXIT_FAILURE;
    return clientSocket.sendRequest(request);
}

KVector<ClientData> & Client::getClientDatas()
{
    return _clientDatas;
}
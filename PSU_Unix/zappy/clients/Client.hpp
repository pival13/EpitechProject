/*
** By Kevin Pruvost, May 2020
** Client.hpp
** File description:
** client
*/

#pragma once

// Project includes
#include "ClientSocket.hpp"
#include "ClientData.hpp"
#include "Tile.hpp"
#include "EggData.hpp"
#include "Mutex.hpp"

// C++ includes
#include <thread>
#include <map>

#define STR(nb) std::to_string(nb)

extern Mutex gameMutex;

/**
 * @brief Common class managing requests from a Zappy server.
 * 
 */
class Client
{
public:
    /**
     * @brief Enum for AI orders.
     */
    enum AiOrder
    {
        FWD,
        LFT,
        RGT,
        BDC,
        MSG, // Broadcast msg received
        UTS,
        FPL,
        EPL,
        TOJ,
        SOJ,
        LAR,
        INV,
        INC, // Incantation start
        EINC, // Incantation End
        MPS, // Map Size
        EJC, // Ejected by another player
        DED,
        Nouille // Waiting nothing.
    };

    /**
     * @brief Enum for graphical events.
     */
    enum GraphEvent
    {
        MSZ,
        BCT,
        TNA,
        PNW,
        PPO,
        PLV,
        PIN,
        PEX,
        PBC,
        PIC,
        PIE,
        PFK,
        PDR,
        PGT,
        PDI,
        ENW,
        EHT,
        EBO,
        EDI,
        SGT,
        SST,
        SEG,
        SMG,
        SUC,
        SBP,
        DEAD,
        MESSAGE,
        NOOP // Nothing
    };

public:
    Client(const char * ip, uint16_t port, const std::string & teamName);
    Client(const std::string & ip, const std::string & port, const std::string & teamName);
    ~Client();

    Position getMapSize();
    /**
     * @brief Get a Tile's Content
     * @param x
     * @param y
     * @return Tile
     */
    Tile getTileContent(int x, int y);
    Tile getTileContent(const Position & pos);
    /**
     * @brief Get every tiles' content
     * @return KVector<KVector<Tile>>
     */
    KVector<KVector<Tile>> getEveryTilesContent();
    KVector<std::string> getTeamsName();
    Position getPlayerPosition(int playerId);
    int getPlayerLevel(int playerId);
    InventoryData getPlayerInventory(int playerId);
    int getTimeUnit();
    void setTimeUnit(int set);

    void moveForward();
    void rotateLeft();
    void rotateRight();
    void broadcastText(const std::string & str);
    void unusedTeamSlotsNumber();
    void forkPlayer();
    void ejectPlayers();
    bool isDead();

    void lookAround();
    void inventory();

    void startIncantation();

    void takeObject(const std::string & obj);
    void setObjectDown(const std::string & obj);

    KVector<GraphEvent> & getGraphEvents();
    KVector<ClientData> & getClientDatas();

    int sendRequest(const std::string & request);
public:
    bool _logged = false;
    std::condition_variable _loggedCond;
    bool parsedNotified = false;

public:
    ClientSocket clientSocket;

private:
    PlayerData & findPlayerById(int id);

    void parseLastResponse();

    void parseMsz(const KVector<std::string> & param);
    void parseBct(const KVector<std::string> & param);
    void parseTna(const KVector<std::string> & param);
    void parsePnw(const KVector<std::string> & param);
    void parsePpo(const KVector<std::string> & param);
    void parsePlv(const KVector<std::string> & param);
    void parsePin(const KVector<std::string> & param);
    void parsePex(const KVector<std::string> & param);
    void parsePbc(const KVector<std::string> & param);
    void parsePic(const KVector<std::string> & param);
    void parsePie(const KVector<std::string> & param);
    void parsePfk(const KVector<std::string> & param);
    void parsePdr(const KVector<std::string> & param);
    void parsePgt(const KVector<std::string> & param);
    void parsePdi(const KVector<std::string> & param);
    void parseEnw(const KVector<std::string> & param);
    void parseEht(const KVector<std::string> & param);
    void parseEbo(const KVector<std::string> & param);
    void parseEdi(const KVector<std::string> & param);
    void parseSgt(const KVector<std::string> & param);
    void parseSst(const KVector<std::string> & param);
    void parseSeg(const KVector<std::string> & param);
    void parseSmg(const KVector<std::string> & param);
    void parseSuc(const KVector<std::string> & param);
    void parseSbp(const KVector<std::string> & param);

    void parseDead(const KVector<std::string> & param);

    int parseAi(const KVector<std::string> & param);

    void parseForward(const KVector<std::string> & param);
    void parseLeft(const KVector<std::string> & param);
    void parseRight(const KVector<std::string> & param);
    void parseBroadcast(const KVector<std::string> & param);
    void parseBroadcastMessage(const KVector<std::string> & param);
    void parseUnusedTeamSlotsNumber(const KVector<std::string> & param);
    void parseForkPlayer(const KVector<std::string> & param);
    void parseEjectPlayers(const KVector<std::string> & param);
    void parseLookAround(const KVector<std::string> & param);
    void parseInventory(const KVector<std::string> & param);
    void parseStartIncantation(const KVector<std::string> & param);
    void parseEndIncantation(const KVector<std::string> & param);
    void parseTakeObject(const KVector<std::string> & param);
    void parseSetObjectDown(const KVector<std::string> & param);
    void parseEjected(const KVector<std::string> & param);

    int parseWelcome(const KVector<std::string> & param);

public:
    void waitForParsed();

public:
    std::string _myTeamName;

    std::thread thread;
    KVector<std::string> _lastResponse;
    std::condition_variable parsed;
    bool sideWorking = false;
    std::condition_variable sideWork;

    // --- Info for Ais and Graphicals.
    KVector<GraphEvent> _graphEvents;

    Position _mapSize = {0, 0};
    KVector<KVector<Tile>> _tilesContent;
    KVector<std::string> _teamsNames;
    KVector<PlayerData> _players;
    KVector<EggData> _eggs;
    int _timeUnit;
    std::string _endingTeam;
    bool _ended = false;
    std::string _serverMsg;
    std::pair<int, std::string> _broadcastGraphicalMessage;

    KVector<AiOrder> _aiOrders;
    KVector<ClientData> _clientDatas;
    bool _forked = false;
    bool _left = false;
    bool _right = false;
    bool _forward = false;
    std::string _broadcastMessage;
    int _broadcastMessageLocation;
    bool _broadcasted = false;
    int _unusedTeamSlotsNumber;
    bool _ejectPlayersReturnCode = false;
    bool _takeObjectReturnCode = false;
    bool _setObjectDownReturnCode = false;
    bool _incantationReturnCode = false;
    int _incantationReturnLevel = 0;
    int _ejectedByPos = 0;
    KVector<std::string> _inventory;
    KVector<std::string> _look;
    bool _dead = false;

    KVector<AiOrder> _clientWaitingOrder;

    bool closed = false;
    bool connectionFailed = false;
};
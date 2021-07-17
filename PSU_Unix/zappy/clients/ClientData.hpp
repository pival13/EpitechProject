/*
** By Kevin Pruvost, May 2020
** ClientData.hpp
** File description:
** client data
*/

#pragma once

// Project includes
#include "KVector.hpp"
#include "Position.hpp"
#include "InventoryData.hpp"
#include "PlayerData.hpp"

// C++ includes
#include <string>

/**
 * @brief Class designed to contain multi-types datas for events.
 */
class ClientData
{
public:
    ClientData(bool boole);
    ClientData(int boole);
    ClientData(const std::string & boole);
    ClientData(const KVector<std::string> & boole);
    ClientData(const Position & boole);
    ClientData(const PlayerData & boole);
    ClientData(const InventoryData & boole);
    ClientData(const ClientData & clData);
    ClientData & operator=(const ClientData & clData);
    ~ClientData();

public:
    /**
     * @brief Enum describing type contained by ClientData.
     */
    enum ClientDataType
    {
        CLDUB,
        CLDUI,
        CLDUS,
        CLDUKS,
        CLDUP,
        CLDUPLAYER,
        CLDUINV
    };
public:
    bool boolean = false;
    int integer = 0;
    std::string string;
    KVector<std::string> stringVector;
    Position position;
    PlayerData playerData;
    InventoryData inventoryData;
    std::vector<ClientData> dataSupp;
    ClientDataType type;
};
/*
** By Kevin Pruvost, May 2020
** ClientData.cpp
** File description:
** client data
*/

#include "ClientData.hpp"

ClientData::ClientData(bool boole)
    : boolean { boole }
    , type { ClientDataType::CLDUB }
{

}

ClientData::ClientData(int boole)
    : integer { boole }
    , type { ClientDataType::CLDUI }
{

}

ClientData::ClientData(const std::string & boole)
    : string { boole }
    , type { ClientDataType::CLDUS }
{

}

ClientData::ClientData(const KVector<std::string> & boole)
    : stringVector { boole }
    , type { ClientDataType::CLDUKS }
{

}

ClientData::ClientData(const Position & boole)
    : position { boole }
    , type { ClientDataType::CLDUP }
{

}

ClientData::ClientData(const PlayerData & boole)
    : playerData { boole }
    , type { ClientDataType::CLDUPLAYER }
{
}

ClientData::ClientData(const InventoryData & boole)
    : inventoryData { boole }
    , type { ClientDataType::CLDUINV }
{

}

ClientData::ClientData(const ClientData & clData)
    : boolean { clData.boolean }
    , integer { clData.integer }
    , string  { clData.string }
    , stringVector { clData.stringVector }
    , position { clData.position }
    , playerData { clData.playerData }
    , inventoryData { clData.inventoryData }
    , dataSupp { clData.dataSupp }
    , type { clData.type }
{
}

ClientData & ClientData::operator=(const ClientData & clData)
{
    type = clData.type;
    boolean = clData.boolean;
    integer = clData.integer;
    string = clData.string;
    stringVector = clData.stringVector;
    position = clData.position;
    dataSupp = clData.dataSupp;
    playerData = clData.playerData;
    inventoryData = clData.inventoryData;
    dataSupp = clData.dataSupp;
    return *this;
}

ClientData::~ClientData()
{
}
/*
** EPITECH PROJECT, 2020
** B-CPP-501-NCY-5-1-rtype-etienne.miltgen
** File description:
** RoomManager
*/

#include "RoomManager.hpp"

RoomManager::RoomManager(std::shared_ptr<UdpGestion> & udpGestion)
    : __udpGestion(udpGestion)
{
}

RoomManager::~RoomManager()
{
}

/**
 * @brief Write the answer inside the container.
 * 
 * @param code CS_ERROR or CS_SOK
 * @param answer container for the answer.
 * @param pos if true setData.
 */
void RoomManager::makeAnswer(Rtype::Rfc::TcpCode code, WriteMessage & answer,
        bool pos)
{
    header_t header;

    header.type = code;
    header.size = 0;
    if (pos)
        answer.setData(&header, sizeof(header_t));
    else
        answer.addData(&header, sizeof(header_t));
}

/**
 * @brief Write the answer inside the container.
 * 
 * @param code CS_ERROR or CS_SOK
 * @param answer container for the answer.
 */
void RoomManager::makeAnswer(unsigned short port,
        boost::uuids::uuid uuid, WriteMessage & answer)
{
    room_loation_t room;
    const std::string tmp = boost::lexical_cast<std::string>(uuid);

    room.header.type = Rtype::Rfc::TcpCode::SC_ROOM_LOCATION;
    room.header.size = sizeof(room) - sizeof(header_t);
    std::memset(room.roomUuid, 0, Rtype::Size::uuidLength);
    std::memcpy(room.roomUuid, tmp.data(), tmp.size());
    room.port = port;
    answer.addData(&room, sizeof(room));
}


/**
 * @brief create room structure which contain all informations about a room.
 * 
 * @param code CS_ERROR or CS_SOK
 * @param udp The room whose information will be sent.
 * @return get_room_t Struct which contain all informations about a given room.
 */
get_room_t RoomManager::makeAnswer(boost::shared_ptr<UdpServer> udp)
{
    get_room_t room;
    const std::string tmp = boost::lexical_cast<std::string>(udp->getUuid());

    room.header.type = Rtype::Rfc::TcpCode::SC_ROOM;
    room.header.size = sizeof(room) - sizeof(header_t);
    memset(room.name, 0, Rtype::Size::nameLength);
    memcpy(room.name, udp->getName().data(), udp->getName().size());
    memset(room.uuid, 0, Rtype::Size::uuidLength);
    memcpy(room.uuid, tmp.c_str(), tmp.size());
    room.port = udp->getPort();
    room.place = udp->getPlace();
    room.numberOfPlayer = udp->getNumberOfPlayer();
    room.bomb = udp->getBomb();
    room.life = udp->getLife();
    return room;
}

/**
 * @brief Send all room to the client.
 * 
 * @return WriteMessage Buffer which send to the client.
 */
WriteMessage RoomManager::sendAllRoom()
{
    get_room_t room;
    WriteMessage writeBuffer;
    std::deque<boost::shared_ptr<UdpServer>> tmp =
            this->__udpGestion->getAllServer();

    for (std::size_t i = 0; i < tmp.size(); ++i) {
        room = makeAnswer(tmp.at(i));
        if (i == 0)
            writeBuffer.setData(&room, sizeof(room));
        else
            writeBuffer.addData(&room, sizeof(room));
    }
    if (writeBuffer.getLength() == 0)
        makeAnswer(Rtype::Rfc::TcpCode::SC_OK, writeBuffer, true);
    else
        makeAnswer(Rtype::Rfc::TcpCode::SC_OK, writeBuffer, false);
    return writeBuffer;
}

/**
 * @brief Delete a player from a room.
 * 
 * @param readBuffer The buffer which contan all informations about the request.
 * @param player The player who launch the request.
 * @param answer The buffer which contains the answer of the request.
 */
void RoomManager::leaveRoom(ReadMessage & readBuffer,
        boost::shared_ptr<Participant> player,
        WriteMessage & answer)
{
    leave_room_t room = readBuffer.getLeaveRoom();
    boost::uuids::uuid roomUuid =
            boost::lexical_cast<boost::uuids::uuid>(room.uuid);

    if (this->__udpGestion->deletePlayer(roomUuid, player))
        makeAnswer(Rtype::Rfc::TcpCode::SC_OK, answer, true);
    else
        makeAnswer(Rtype::Rfc::TcpCode::SC_ERROR, answer, true);
}

/**
 * @brief Excute the client's request.
 * 
 * @param readBuffer The readbuffer which contains request.
 * @param udpGestion All game's room.
 * @param player The client's which launch the request.
 * @param answer Container for the answer.
 */
void RoomManager::createRoom(ReadMessage & readBuffer,
        boost::shared_ptr<Participant> player,
        WriteMessage & answer)
{
    boost::uuids::uuid roomUuid = boost::uuids::random_generator()();
    boost::shared_ptr<UdpServer> udp;
    create_room_t createRoom = readBuffer.getCreateRoom();

    this->__udpGestion->createRoom(player, createRoom, roomUuid);
    makeAnswer(Rtype::Rfc::TcpCode::SC_OK, answer, true);
    udp = this->__udpGestion->getServer(roomUuid);
    if (udp != nullptr)
        makeAnswer(udp->getPort(), roomUuid, answer);
}


/**
 * @brief Excute the client's request.
 * 
 * @param readBuffer The readbuffer which contains request.
 * @param udpGestion All game's room.
 * @param participant The client's which launch the request.
 * @param answer Container for the answer.
 */
void RoomManager::joinRoom(ReadMessage & readBuffer,
        boost::shared_ptr<Participant> participant,
        WriteMessage & answer)
{
    join_room_t joinRoom = readBuffer.getJoinRoom();
    boost::uuids::uuid roomUuid = boost::lexical_cast<boost::uuids::uuid>(joinRoom.uuid);
    boost::shared_ptr<UdpServer> udp;

    if (!this->__udpGestion->addPlayer(participant, roomUuid)) {
        makeAnswer(Rtype::Rfc::TcpCode::SC_ERROR, answer, true);
    } else {
        makeAnswer(Rtype::Rfc::TcpCode::SC_OK, answer, true);
        udp = this->__udpGestion->getServer(roomUuid);
        if (udp != nullptr)
            makeAnswer(udp->getPort(), roomUuid, answer);
    }
}

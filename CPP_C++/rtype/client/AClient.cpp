/*
** EPITECH PROJECT, 2020
** B-CPP-501-NCY-5-1-rtype-etienne.miltgen
** File description:
** AClient
*/

#include "AClient.hpp"

AClient::AClient(std::string ip)
	: _IP(ip)
{
}

AClient::~AClient() {}

void AClient::stopRunning()
{
    this->_running = false;
}

void AClient::stopUdpRunning()
{
    this->_udpRunning = false;
}

bool AClient::isRunning() const
{
    return this->_running;
}

bool AClient::isUdpRunning() const
{
    return this->_udpRunning;
}

std::string AClient::getIP() const
{
    return this->_IP;
}

header_t AClient::getHeader() const
{
    return this->_tcpHeader;
}

std::vector<get_room_t> AClient::getRooms() const
{
    return this->_rooms;
}

std::string AClient::getRoomUuid() const
{
    return this->_roomUuid;
}

std::vector<unsigned char> AClient::getUdpUpdate() const
{
    return this->_update;
}

void AClient::addData(void *data, std::size_t length)
{
    this->_data.resize(this->_dataSize + length);
    std::memcpy(this->_data.data() + this->_dataSize, data, length);
    this->_dataSize += length;
}

void AClient::setData(void *data, std::size_t length)
{
    this->_dataSize = length;
    this->_data.resize(length);
    std::memcpy(this->_data.data(), data, length);
}

void AClient::addUdpData(void *data, std::size_t length)
{
    this->_udpData.resize(this->_udpDataSize + length);
    std::memcpy(this->_udpData.data() + this->_udpDataSize, data, length);
    this->_udpDataSize += length;
}

void AClient::setUdpData(void *data, std::size_t length)
{
    this->_udpDataSize = length;
    this->_udpData.resize(length);
    std::memcpy(this->_udpData.data(), data, length);
}

void AClient::setTcpHeader(char buffer[sizeof(header_t)])
{
    std::memset(&this->_tcpHeader, 0, sizeof(header_t));
    std::memcpy(&this->_tcpHeader, buffer, sizeof(header_t));
}

create_room_t AClient::makeRoom(const std::string & name, const short place,
		const short bomb, const short life) {
    create_room_t room;

    room.header.type = Rtype::Rfc::TcpCode::CS_CREATE_ROOM;
    room.header.size = sizeof(room) - sizeof(header_t);
    std::memset(room.name, 0, Rtype::Size::nameLength);
    std::memcpy(room.name, name.data(), name.size());
    room.place = place;
    room.bomb = bomb;
    room.life = life;
    return room;
}

join_room_t AClient::makeJoinRoom(char roomuuid[Rtype::Size::uuidLength])
{
    join_room_t room;

    room.header.type = Rtype::Rfc::TcpCode::CS_JOIN_ROOM;
    room.header.size = sizeof(room) - sizeof(header_t);
    std::memset(room.uuid, 0, Rtype::Size::uuidLength);
    std::memcpy(room.uuid, roomuuid, Rtype::Size::uuidLength);
    return room;
}

leave_room_t AClient::makeLeaveRoom(char roomuuid[Rtype::Size::uuidLength])
{
    leave_room_t room;

    room.header.type = Rtype::Rfc::TcpCode::CS_LEAVE_ROOM;
    room.header.size = sizeof(room) - sizeof(header_t);
    std::memset(room.uuid, 0, Rtype::Size::uuidLength);
    std::memcpy(room.uuid, roomuuid, Rtype::Size::uuidLength);
    return room;
}

//
// Created by etien on 14/11/2020.
//

#include "Core.hpp"

Core::Core(std::string ip)
	: AClient(ip),
    __recipient(ip)
{
}

Core::~Core() {}

bool Core::receiveTCPMessage()
{
    std::size_t received = 0;

    std::memset(this->__body, 0, Rtype::Size::maxReadSize);
    if (this->__TCPSocket.receive(this->__body, this->_tcpHeader.size, received)
            != sf::Socket::Done)
        return false;
    if (received != (std::size_t)this->_tcpHeader.size) {
        std::cerr << "(Body) : wrong size" << std::endl;
        return false;
    }
	return true;
}

/**
 * @brief Read with header size on the client tcp socket.
 * 
 * @return bool
 */
bool Core::receiveTCPHeader()
{
	std::size_t received = 0;
    char buffer[sizeof(header_t)];

    std::memset(buffer, 0, sizeof(header_t));
	if (this->__TCPSocket.receive(buffer, sizeof(header_t), received)
            != sf::Socket::Done)
        return false;
    if (received != sizeof(header_t)) {
        std::cerr << "(Header) : wrong size" << std::endl;
        return false;
    }
    setTcpHeader(buffer);
    return true;
}

/**
 * @brief Tries to connect to the server.
 * 
 * @return true If the the connection was successful.
 * @return false If the connection failed.
 */
bool Core::initConnection()
{
    sf::Socket::Status status = this->__TCPSocket.connect(this->_IP.c_str(), 4242);
	player_uuid_t body;

    if (status == sf::Socket::Done && receiveTCPHeader()) {
	    if (this->_tcpHeader.type == Rtype::Rfc::SC_PLAYER_UUID) {
            if (receiveTCPMessage()) {
                std::memcpy((char *)&body + sizeof(header_t), this->__body, this->_tcpHeader.size);
                std::memset(this->_uuid, 0, Rtype::Size::uuidLength);
                std::memcpy(this->_uuid, body.uuid, Rtype::Size::uuidLength);
	            this->_running = true;
                return true;
            }
        }
    }
    stopRunning();
    return false;
}

bool Core::sendHeaderToTcpServer(Rtype::Rfc::TcpCode rfcCode)
{
    header_t header;
    std::vector<char> data;

    header.type = rfcCode;
    header.size = 0;
    setData(&header, sizeof(header_t));
    doTcpWrite();
    return true;
}

bool Core::setRooms()
{
    get_room_t room;

    if (!sendHeaderToTcpServer(Rtype::Rfc::TcpCode::CS_GET_ROOM)) {
        stopRunning();
        return false;
    }
    this->_rooms.clear();
    while(true) {
        if (!receiveTCPHeader()) {
            stopRunning();
            return false;
        }
        if (this->_tcpHeader.type == Rtype::Rfc::TcpCode::SC_OK) {
            break;
        }
        if (!receiveTCPMessage()) {
            stopRunning();
            return false;
        }
        if (this->_tcpHeader.type == Rtype::Rfc::TcpCode::SC_ROOM) {
            std::memset(&room, 0, sizeof(room));
            std::memcpy((char *)&room + sizeof(header_t), this->__body, this->_tcpHeader.size);
            this->_rooms.push_back(room);
        }
    }
    return true;
}

bool Core::createRoom(const std::string & name, const short place,
	    const short bomb, const short life) {
    create_room_t room = makeRoom(name, place, bomb, life);
    room_loation_t loc;

    setData(&room, sizeof(room));
    doTcpWrite();
    if (!receiveTCPHeader()) {
        return false;
    }
    if (this->_tcpHeader.type != Rtype::Rfc::TcpCode::SC_OK) {
        return false;
    }
    if (!receiveTCPHeader()) {
        return false;
    }
    if (this->_tcpHeader.type == Rtype::Rfc::TcpCode::SC_ROOM_LOCATION) {
        if (receiveTCPMessage()) {
            std::memcpy((char *)&loc + sizeof(header_t), this->__body, this->_tcpHeader.size);
            this->_port = loc.port;
            this->_roomUuid = std::string(loc.roomUuid);
            return true;
        } else {
            return false;
        }
    }
    return false;
}

bool Core::joinRoom(char roomUuid[Rtype::Size::uuidLength])
{
    join_room_t room = makeJoinRoom(roomUuid);
    room_loation_t loc;

    setData(&room, sizeof(room));
    doTcpWrite();
    if (!receiveTCPHeader()) {
        stopRunning();
        return false;
    }
    if (this->_tcpHeader.type != Rtype::Rfc::TcpCode::SC_OK)
        return false;
    if (!receiveTCPHeader()) {
        stopRunning();
        return false;
    }
    if (this->_tcpHeader.type == Rtype::Rfc::TcpCode::SC_ROOM_LOCATION) {
        if (receiveTCPMessage()) {
            std::memcpy((char *)&loc + sizeof(header_t), this->__body, this->_tcpHeader.size);
            this->_port = loc.port;
            this->_roomUuid = std::string(loc.roomUuid);
            return true;
        } else {
            return false;
        }
    }
    return false;
}

bool Core::leaveRoom(char roomUuid[Rtype::Size::uuidLength])
{
    leave_room_t room = makeLeaveRoom(roomUuid);

    setData(&room, sizeof(room));
    if (!doTcpWrite()) {
        stopRunning();
        return false;
    }
    if (!receiveTCPHeader()) {
        stopRunning();
        return false;
    }
    if (this->_tcpHeader.type == Rtype::Rfc::TcpCode::SC_OK)
        return true;
    return false;
}

bool Core::doTcpWrite()
{
    std::string ending = "\r\n";
    addData(ending.data(), ending.size());

    if (this->__TCPSocket.send((char *)this->_data.data(), this->_dataSize) != sf::Socket::Done) {
        stopRunning();
        return false;
    }
    this->_data.clear();
    this->_dataSize = 0;
    return true;
}

bool Core::initUdp()
{
    if (this->_port == 0)
        return false;
    if (this->__UDPSocket.bind(sf::Socket::AnyPort) == sf::Socket::Done) {
        this->_udpRunning = true;
        return true;
    }
    return false;
}

void Core::setUdpHeader()
{
    std::memset(&this->_udpHeader, 0, sizeof(header_udp_output_t));
    std::memcpy((char *)&this->_udpHeader, this->__udpVector.data(),
            sizeof(header_udp_output_t));
    this->__udpVector.erase(this->__udpVector.begin(),
            this->__udpVector.begin() + sizeof(header_udp_output_t));
    if (this->_udpHeader.type == Rtype::Rfc::UdpCode::SC_UPDATE) {
        this->_update = this->__udpVector;
    }
}

/**
 * @brief Read with header size on the client tcp socket.
 * 
 * @return bool
 */
bool Core::receiveUDPHeader()
{
    std::size_t received = 0;
    sf::IpAddress sender;
    unsigned short port;
	char buffer[Rtype::Size::maxReadUdpSize];

    std::memset(buffer, 0, Rtype::Size::maxReadUdpSize);
	if (this->__UDPSocket.receive(buffer, Rtype::Size::maxReadUdpSize,
            received, sender, port) != sf::Socket::Done) {
        return false;
    }
    this->__udpVector.clear();
    this->__udpVector.resize(received);
    std::memcpy(this->__udpVector.data(), buffer, received);
    setUdpHeader();
    return true;
}

bool Core::udpAction(std::vector<unsigned char> data)
{
    header_udp_input_t header;

    header.type = Rtype::Rfc::UdpCode::CS_ACTION;
    header.size = (short)data.size();
    std::memcpy(header.uuid, this->_uuid, Rtype::Size::uuidLength);
    setUdpData(&header, sizeof(header_udp_input_t));
    addUdpData(data.data(), data.size());
    if (!doUdpWrite()) {
        stopUdpRunning();
        return false;
    }
    return true;
}

bool Core::getUpdate()
{
    if (!receiveUDPHeader()) {
        stopUdpRunning();
        return false;
    }
    return true;
}

bool Core::doUdpWrite()
{
    if (this->__UDPSocket.send((char *)this->_udpData.data(),
            this->_udpDataSize, this->__recipient, this->_port) != sf::Socket::Done) {
        stopUdpRunning();
        return false;
    }
    this->_udpData.clear();
    this->_udpDataSize = 0;
    return true;
}

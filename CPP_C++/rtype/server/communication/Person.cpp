/*
** EPITECH PROJECT, 2020
** B-CPP-501-NCY-5-1-rtype-etienne.miltgen
** File description:
** Person
*/


#include "Person.hpp"

Person::Person(boost::asio::io_context& ioc,
        boost::asio::io_context::strand& strand, ChatRoom& room,
        std::shared_ptr<RoomManager> & roomManager,
        std::shared_ptr<UdpGestion> & udpGestion)
    : __socket(ioc),
    __context (ioc),
    __strand (strand),
    __room(room),
    __roomManager(roomManager),
    __udpGestion(udpGestion)
{
    this->__uuid = boost::uuids::random_generator()();
}

Person::~Person()
{
    std::cout << "The client socket has been closed" << std::endl;
}

/**
 * @brief Create a new socket for the new client.
 * 
 * @param ioc 
 * @param strand 
 * @param room 
 * @return Person::pointer 
 */
Person::pointer Person::create(boost::asio::io_context & ioc,
        boost::asio::io_context::strand & strand, ChatRoom & room,
        std::shared_ptr<RoomManager> & roomManager,
        std::shared_ptr<UdpGestion> & udpGestion)
{
    return pointer(new Person(ioc, strand, room, roomManager, udpGestion));
}

tcp::socket& Person::socket()
{
    return this->__socket;
}

/**
 * @brief Send the player's uuid to the socket.
 * 
 */
void Person::sendPlayerUuid() {
    const std::string tmp = boost::lexical_cast<std::string>(this->__uuid);
    WriteMessage writeMessage;
    player_uuid_t player;

    player.header.type = Rtype::Rfc::TcpCode::SC_PLAYER_UUID;
    player.header.size = sizeof(player_uuid_t) - sizeof(header_t);
    memset(player.uuid, 0, Rtype::Size::uuidLength);
    memcpy(player.uuid, tmp.data(), tmp.size());
    writeMessage.setData(&player, sizeof(player));
    this->__writeBuffer.push_back(writeMessage);
}

/**
 * @brief Start server's loop of the new client
 *
 */
void Person::start()
{
    this->__room.enter(shared_from_this());
    sendPlayerUuid();
    doWrite();
}

/**
 * @brief Return current client's uuid.
 *
 * @return boost::uuids::uuid client's uuid.
 */
const boost::uuids::uuid Person::getUuid() const
{
    return this->__uuid;
}

/**
 * @brief Return the name of the current player.
 * 
 * @return const std::string 
 */
const std::string Person::getName() const
{
    return this->__name;
}

void Person::runCommand()
{
    header_t header = this->__readMessage.getHeader();
    WriteMessage answer;

    if (std::find(Rtype::Rfc::List::CSTcpList.begin(),
            Rtype::Rfc::List::CSTcpList.end(), header.type) == Rtype::Rfc::List::CSTcpList.end()) {
        std::cerr << "(Tcp) : Unknown request's type" << std::endl;
        this->__room.leave(shared_from_this());
        return;
    }
    switch (header.type) {
        case Rtype::Rfc::TcpCode::CS_CREATE_ROOM:
            this->__roomManager->createRoom(this->__readMessage, shared_from_this(), answer);
            this->__writeBuffer.push_back(answer);
            break;
        case Rtype::Rfc::TcpCode::CS_GET_ROOM:
            this->__writeBuffer.push_back(this->__roomManager->sendAllRoom());
            break;
        case Rtype::Rfc::TcpCode::CS_JOIN_ROOM:
            this->__roomManager->joinRoom(this->__readMessage, shared_from_this(), answer);
            this->__writeBuffer.push_back(answer);
            break;
        case Rtype::Rfc::TcpCode::CS_LEAVE_ROOM:
            this->__roomManager->leaveRoom(this->__readMessage, shared_from_this(), answer);
            this->__writeBuffer.push_back(answer);
            break;
        default:
            break;
    }
    doWrite();
}

/**
 * @brief Read on the client's socket.
 * 
 */
void Person::doRead()
{
    boost::asio::async_read_until(this->__socket, this->__readBuffer, "\r\n",
        this->__strand.wrap(
            [this](boost::system::error_code ec, std::size_t size) {
                if (!ec && size >= sizeof(header_t)) {
                    std::vector<char> buff(size + 1);
                    std::istream is(&this->__readBuffer);
                    is.readsome(buff.data(), size);

                    this->__readMessage.addCommand(buff);
                    runCommand();
                } else {
                    std::cerr << "Read error has occured" << std::endl;
                    this->__room.leave(shared_from_this());
                }
            }
        )
    );
}

/**
 * @brief Write on the client's socket
 * 
 */
void Person::doWrite()
{
    boost::asio::async_write(this->__socket,
        boost::asio::buffer(this->__writeBuffer.front().getData(),
            this->__writeBuffer.front().getLength()),
        this->__strand.wrap(
            [this](const boost::system::error_code& ec, std::size_t size) {
                if (ec) {
                    std::cerr << "Error write" << std::endl;
                    this->__room.leave(shared_from_this());
                } else {
                    std::cout << size << " bytes send" << std::endl;
                    this->__writeBuffer.pop_front();
                    if (!this->__writeBuffer.empty())
                        doWrite();
                    else
                        doRead();
                }
            }
        )
    );
}

/*
** EPITECH PROJECT, 2020
** B-CPP-501-NCY-5-1-rtype-etienne.miltgen
** File description:
** UdpServer
*/

#include "UdpServer.hpp"

UdpServer::UdpServer(const boost::shared_ptr<Participant> & player,
        const boost::uuids::uuid uuid,
        create_room_t room, const short port,
        boost::asio::io_context & ioc,
        boost::asio::io_context::strand & strand)
    : __ioc(ioc),
    __socket(ioc, udp::endpoint(udp::v4(), port)),
    __strand(strand),
    __name(std::string(room.name)),
    __place(room.place),
    __bomb(room.bomb),
    __life(room.life)
{
    this->__roomUuid = uuid;
    this->__players.insert(player);
    this->__numberOfPlayer = 1;
    this->__port = this->__socket.local_endpoint().port();
    this->__t = std::shared_ptr<RType>(new RType(boost::lexical_cast<std::string>(player->getUuid())));
    memset(this->__readBuffer, 0, Rtype::Size::maxReadSize);
    doReceiveHeader();
}

UdpServer::~UdpServer()
{
    std::cout << "Udp server has been closed" << std::endl;
}

boost::shared_ptr<UdpServer> UdpServer::create(
        const boost::shared_ptr<Participant> & player,
        const boost::uuids::uuid uuid, create_room_t room, const short port,
        boost::asio::io_context& ioc, boost::asio::io_context::strand & strand)
{
        return boost::shared_ptr<UdpServer>(new UdpServer(
                player, uuid, room, port, ioc, strand));
}

bool UdpServer::checkUser(boost::uuids::uuid playerUuid)
{
    for (auto player : this->__players)
        if (playerUuid == player->getUuid())
            return true;
    return false;
}

void UdpServer::badRequest(Rtype::Rfc::UdpCode rfcCode)
{
    WriteUdpMessage writeMessage;
    header_udp_output_t header;

    header.size = 0;
    header.type = rfcCode;
    writeMessage.setData(&header, sizeof(header_udp_output_t));
    this->__writeBuffer.push_back(writeMessage);
    doSend();
}

void UdpServer::setEvent(WriteUdpMessage & writeMessage)
{
    header_udp_output_t header;

    auto events = this->__t->getEvents();
    header.type = Rtype::Rfc::UdpCode::SC_UPDATE;
    header.size = events.size() * sizeof(RTypeEvents);
    writeMessage.addData(&header, sizeof(header));
    for (auto event : events)
        writeMessage.addData(&event, sizeof(event));
}

void UdpServer::runCommand(char uuid[Rtype::Size::uuidLength])
{
    WriteUdpMessage writeMessage;
    header_udp_output_t header;

    header.type = Rtype::Rfc::UdpCode::SC_UPDATE;
    this->__t->receiveInputs(std::string(uuid), this->__readMessage.getInput());
    std::vector<unsigned char> out = this->__t->exportOutputs();
    header.size = out.size();
    writeMessage.setData(&header, sizeof(header_udp_output_t));
    writeMessage.addData(out.data(), out.size());
    //setEvent(writeMessage);
    this->__writeBuffer.push_back(writeMessage);
    doSend();
}

void UdpServer::doReceiveBody()
{
    header_udp_input_t header = this->__readMessage.getHeader();

    if (checkUser(boost::lexical_cast<boost::uuids::uuid>(header.uuid))) {
        if ((std::size_t)header.size <= this->__readMessage.getLength()) {
            if (std::find(Rtype::Rfc::List::CSUdpList.begin(),
                    Rtype::Rfc::List::CSUdpList.end(), header.type) != Rtype::Rfc::List::CSUdpList.end()) {
                std::cout << "(Body) : Read successfull" << std::endl;
                runCommand(header.uuid);
            } else {
                std::cerr << "(Body) : Unknown request's type" << std::endl;
                badRequest(Rtype::Rfc::UdpCode::SC_ERROR_REQUEST);
                doReceiveHeader();
            }
        } else {
            std::cerr << "(Body) : wrong size read > " <<
                    this->__readMessage.getLength() << std::endl;
            badRequest(Rtype::Rfc::UdpCode::SC_ERROR_SIZE);
            doReceiveHeader();
        }
    } else {
        std::cerr << "(Body) : User is not register" << std::endl;
        badRequest(Rtype::Rfc::UdpCode::SC_ERROR_AUTH);
        doReceiveHeader();
    }
}

void UdpServer::doReceiveHeader()
{
    if (this->__players.empty())
        return;
    memset(this->__readBuffer, 0, Rtype::Size::maxReadSize);
    this->__socket.async_receive_from(
        boost::asio::buffer(this->__readBuffer, Rtype::Size::maxReadSize), this->__remote_endpoint,
        this->__strand.wrap(
            [this](const boost::system::error_code ec, std::size_t size) {
                if (!ec) {
                    if (size >= sizeof(header_udp_input_t)) {
                        std::cout << "(Header) : Read successfull > " << size << std::endl;
                        std::vector<unsigned char> request (this->__readBuffer, this->__readBuffer + size);
                        this->__readMessage.addCommand(request);
                        doReceiveBody();
                    } else {
                        std::cerr << "(Header) : Wrong size read" << std::endl;
                        doReceiveHeader();
                    }
                } else {
                    std::cerr << "(Header) : Read error has occured" << std::endl;
                    doReceiveHeader();
                }
            }
        )
    );
}

void UdpServer::doSend()
{
    this->__socket.async_send_to(
        boost::asio::buffer(this->__writeBuffer.front().getData(),
        this->__writeBuffer.front().getLength()), this->__remote_endpoint,
        this->__strand.wrap(
            [this](const boost::system::error_code& ec, std::size_t size) {
                if (ec) {
                    std::cerr << "Error write" << std::endl;
                } else {
                    std::cout << size << " bytes send" << std::endl;
                    this->__writeBuffer.pop_front();
                    if (!this->__writeBuffer.empty())
                        doSend();
                    else
                        doReceiveHeader();
                }
            }
        )
    );
}

/**
 * @brief Delete a user from the current game.
 * 
 * @param player Player will be deleted.
 */
bool UdpServer::deletePlayer(const boost::shared_ptr<Participant> & player)
{
    if (this->__players.erase(player) > 0) {
        --this->__numberOfPlayer;
        return true;
    }
    return false;
}

/**
 * @brief Add Player to the current game.
 * 
 * @param player Player will be deleted.
 */
void UdpServer::addPlayer(const boost::shared_ptr<Participant> & player)
{
    this->__players.insert(player);
    this->__t->addPlayer(boost::lexical_cast<std::string>(player->getUuid()));
    ++this->__numberOfPlayer;
}

/**
 * @brief Return the uuid of the current udp server.
 * 
 * @return boost::uuids::uuid 
 */
boost::uuids::uuid UdpServer::getUuid() const
{
    return this->__roomUuid;
}

/**
 * @brief Get the room's name
 * 
 * @return std::string Room's Name.
 */
std::string UdpServer::getName() const
{
    return this->__name;
}

/**
 * @brief Get the number of participant.
 * 
 * @return short The number of participant.
 */
short UdpServer::getNumberOfPlayer() const
{
    return this->__numberOfPlayer;
}

/**
 * @brief 
 * 
 * @return short 
 */
short UdpServer::getPlace() const
{
    return this->__place;
}

/**
 * @brief 
 * 
 * @return short 
 */
short UdpServer::getLife() const
{
    return this->__life;
}

/**
 * @brief 
 * 
 * @return short 
 */
short UdpServer::getBomb() const
{
    return this->__bomb;
}

/**
 * @brief 
 * 
 * @return unsigned short 
 */
unsigned short UdpServer::getPort() const
{
    return this->__port;
}

/*
** EPITECH PROJECT, 2020
** B-CPP-501-NCY-5-1-rtype-etienne.miltgen
** File description:
** UdpServer
*/

#ifndef UDPSERVER_HPP_
#define UDPSERVER_HPP_

#include "../Participant.hpp"
#include "WriteUdpMessage.hpp"
#include "ReadUdpMessage.hpp"
#include "../include/room.hpp"
#include "../../game/RType.hpp"

#include <iostream>
#include <deque>
#include <set>

using boost::asio::ip::udp;

class UdpServer {
    public:
        ~UdpServer();
        std::string getName() const;
        short getNumberOfPlayer() const;
        short getPlace() const;
        short getLife() const;
        short getBomb() const;
        unsigned short getPort() const;
        void addPlayer(const boost::shared_ptr<Participant> & player);
        bool deletePlayer(const boost::shared_ptr<Participant> & player);
        static boost::shared_ptr<UdpServer> create(const boost::shared_ptr<Participant> & player,
                const boost::uuids::uuid uuid, create_room_t room, const short port,
                boost::asio::io_context& ioc, boost::asio::io_context::strand & strand);
        boost::uuids::uuid getUuid() const;

    private:
        UdpServer(const boost::shared_ptr<Participant> & player,
                boost::uuids::uuid uuid, create_room_t room,
                const short port, boost::asio::io_context& ioc,
                boost::asio::io_context::strand & strand);
        bool checkUser(boost::uuids::uuid playerUuid);
        void badRequest(Rtype::Rfc::UdpCode rfcCode);
        void runCommand(char uuid[Rtype::Size::uuidLength]);
        void setEvent(WriteUdpMessage & writeMessage);
        void doReceiveHeader();
        void doReceiveBody();
        void doSend();

    private:
        std::shared_ptr<RType> __t;
        boost::asio::io_context& __ioc;
        udp::socket __socket;
        boost::asio::io_context::strand & __strand;
        udp::endpoint __remote_endpoint;
        char __readBuffer[Rtype::Size::maxReadSize];
        boost::uuids::uuid __roomUuid;
        ReadUdpMessage __readMessage;
        std::deque<WriteUdpMessage> __writeBuffer;
        std::set<boost::shared_ptr<Participant>> __players;
        const std::string __name;
        short __numberOfPlayer;
        const short __place;
        const short __bomb;
        const short __life;
        unsigned short __port;
};

#endif /* !UDPSERVER_HPP_ */

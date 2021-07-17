/*
** EPITECH PROJECT, 2020
** B-CPP-501-NCY-5-1-rtype-etienne.miltgen
** File description:
** UdpGestion
*/

#ifndef UDPGESTIONLIST_HPP_
#define UDPGESTIONLIST_HPP_

#include "udp/UdpServer.hpp"

#include <deque>

class UdpGestion {
    public:
        UdpGestion(boost::asio::io_context & ioc,
                boost::asio::io_context::strand & strand);
        ~UdpGestion();
        void createRoom(boost::shared_ptr<Participant> player,
                create_room_t room, boost::uuids::uuid roomUuid,
                int port = 0);
        bool addPlayer(boost::shared_ptr<Participant> player,
                boost::uuids::uuid uuid);
        bool deletePlayer(boost::uuids::uuid roomUuid,
                boost::shared_ptr<Participant> & player);
        std::deque<boost::shared_ptr<UdpServer>> getAllServer() const;
        boost::shared_ptr<UdpServer> getServer(boost::uuids::uuid roomUuid) const;

    private:
        std::deque<boost::shared_ptr<UdpServer>> __udps;
        boost::asio::io_context & __ioc;
        boost::asio::io_context::strand & __strand;
};

#endif /* !UDPGESTIONLIST_HPP_ */

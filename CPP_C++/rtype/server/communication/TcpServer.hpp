/*
** EPITECH PROJECT, 2020
** B-CPP-501-NCY-5-1-rtype-etienne.miltgen
** File description:
** TcpServer
*/

#ifndef TCPSERVER_HPP_
#define TCPSERVER_HPP_

#include "Person.hpp"
#include "ChatRoom.hpp"

#include <deque>

using boost::asio::ip::tcp;

class TcpServer {
    public:
        TcpServer(boost::asio::io_context& io_context,
            boost::asio::io_context::strand& strand, int port);

    private:
        void handle_accept(Person::pointer newConnection,
            const boost::system::error_code& error);
        void startAccept();

    private:
        tcp::acceptor __acceptor;
        boost::asio::io_context& __ioc;
        boost::asio::io_context::strand& __strand;
        ChatRoom __room;
        std::shared_ptr<RoomManager> __roomManager;
        std::shared_ptr<UdpGestion> __udpGestion;
};

#endif /* !TCPSERVER_HPP_ */

/*
** EPITECH PROJECT, 2020
** B-CPP-501-NCY-5-1-rtype-etienne.miltgen
** File description:
** TcpServer
*/

#include "TcpServer.hpp"


TcpServer::TcpServer(boost::asio::io_context & io_context,
    boost::asio::io_context::strand & strand, int port)
    : __acceptor (io_context, tcp::endpoint (tcp::v4(), port)),
    __ioc (io_context),
    __strand (strand)
{
    this->__udpGestion =
            std::shared_ptr<UdpGestion>(new UdpGestion(io_context, strand));
    this->__roomManager =
            std::shared_ptr<RoomManager>(new RoomManager(this->__udpGestion));
    startAccept();
}

void TcpServer::startAccept()
{
    Person::pointer newConnection = Person::create(
        this->__ioc, this->__strand, this->__room,
        this->__roomManager, this->__udpGestion);

    this->__acceptor.async_accept(newConnection->socket(),
        this->__strand.wrap(
            boost::bind(
                &TcpServer::handle_accept,
                this,
                newConnection,
                boost::asio::placeholders::error
            )
        )
    );
}

void TcpServer::handle_accept(Person::pointer newConnection,
        const boost::system::error_code& error)
{
    if (!error) {
        newConnection->start();
        startAccept();
    }
}

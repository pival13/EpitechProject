/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** TcpServer
*/

#ifndef TCPSERVER_HPP_
#define TCPSERVER_HPP_

#include "Person.hpp"
#include "ChatRoom.hpp"

using boost::asio::ip::tcp;

class TcpServer {
    public:
        TcpServer(boost::asio::io_context& io_context,
            boost::asio::io_context::strand& strand, int port,
            const std::string &dbPath);

    private:
        void handle_accept(Person::pointer newConnection,
            const boost::system::error_code& error);
        void createDatabase(const std::string &path);
        void changedStatus(const std::string &path);
        void startAccept();

    private:
        tcp::acceptor m_acceptor;
        boost::asio::io_context& m_ioc;
        boost::asio::io_context::strand& m_strand;
        const std::string & m_dbPath;
        ChatRoom m_room;
};

#endif /* !TCPSERVER_HPP_ */

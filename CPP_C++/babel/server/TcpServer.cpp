/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** TcpServer
*/

#include "TcpServer.hpp"

void TcpServer::createDatabase(const std::string &path)
{
    MySqlite sql(path);

    std::string request = R"(
        CREATE TABLE IF NOT EXISTS users
        (username VARCHAR(64), password VARCHAR(64), mail VARCHAR(64), status INT);
        CREATE TABLE IF NOT EXISTS contacts
        (email VARCHAR(64), UserId INT, ContactId PRIMARY KEY);
        CREATE TABLE IF NOT EXISTS messages
        (Receiver VARCHAR(64), Emitter VARCHAR(64), Contain VARCHAR(260), timestamp INT);)";
    if (!sql.excuteInsert(request))
        throw std::runtime_error("Cannot find the database");
}

void TcpServer::changedStatus(const std::string &path)
{
    MySqlite sql(path);
    std::string request = "update users set status=" + std::to_string(OFFLINE);

    if (sql.excuteInsert(request) == false)
        throw std::runtime_error("Changed status failed");
}

TcpServer::TcpServer(boost::asio::io_context& io_context,
    boost::asio::io_context::strand& strand, int port,
    const std::string &dbPath)
    : m_ioc (io_context),
    m_strand (strand),
    m_acceptor (io_context, tcp::endpoint (tcp::v4(), port)),
    m_dbPath(dbPath)
{
    try {
        createDatabase(this->m_dbPath);
    } catch (std::exception & err) {
        std::cerr << err.what() << std::endl;
        return;
    }
    try {
        changedStatus(this->m_dbPath);
    } catch (const std::exception & err) {
        std::cerr << err.what() << std::endl;
    }
    startAccept();
}


void TcpServer::startAccept()
{
    Person::pointer newConnection = Person::create(m_ioc, m_strand, m_room, m_dbPath);

    m_acceptor.async_accept(newConnection->socket(),
        this->m_strand.wrap(
            boost::bind(
                &TcpServer::handle_accept,
                this,
                newConnection,
                boost::asio::placeholders::error)));
}

void TcpServer::handle_accept(Person::pointer newConnection,
        const boost::system::error_code& error)
{
    if (!error) {
        newConnection->start();
        startAccept();
    }
}
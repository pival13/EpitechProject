/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** main
*/

#include "TcpServer.hpp"
#include "PointerHandler.hpp"

int main()
{
    try {
        std::shared_ptr<boost::asio::io_context> ioc(new boost::asio::io_context);
        boost::shared_ptr<boost::asio::io_context::work> work(new boost::asio::io_context::work(*ioc));
        boost::shared_ptr<boost::asio::io_context::strand> strand(new boost::asio::io_context::strand(*ioc));

        TcpServer server(*ioc, *strand, 4242);
        (*ioc).run();
    } catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    PointerHandler::materials.clear();
    return 0;
}
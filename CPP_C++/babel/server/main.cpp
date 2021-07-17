/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** main
*/

#include "TcpServer.hpp"
#include "../GetOpt.hpp"

int help(const char *prog)
{
    std::cout << "USAGE\n\t" << prog << " [option]\n\nDESCRIPTION\n";
    std::cout << "\t-h, --help\tDisplay this help and exit\n";
    std::cout << "\t-a, --address\tUse the following address to connect with the server\n";
    std::cout << "\t-p, --port\tUse this port to start a connection with the server" << std::endl;
    return 0;
}


int main(int ac, char** av) {
    int port = 42;
    std::string dbPath = "../server/db/server";
    auto args = GetOpt(std::list<char*>(av + 1, av + ac), {
        {'h', "help", NoArg},
        {'p', "port", MandatoryArg},
        {'a', "address", MandatoryArg},
    });
    for (const auto &arg : args) {
        if (arg.shortOpt == 'p') {
            port = std::stoi(arg.value);
        } else if (arg.shortOpt == 'a') {
            dbPath.clear();
            dbPath = std::string (arg.value);
        } else if (arg.shortOpt == 'h') {
            return help(av[0]);
        }
    }
    try {
        std::shared_ptr<boost::asio::io_context> ioc(new boost::asio::io_context);
        boost::shared_ptr<boost::asio::io_context::work> work(new boost::asio::io_context::work(*ioc));
        boost::shared_ptr<boost::asio::io_context::strand> strand(new boost::asio::io_context::strand(*ioc));

        TcpServer server(*ioc, *strand, port, dbPath);
        (*ioc).run();
    } catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}

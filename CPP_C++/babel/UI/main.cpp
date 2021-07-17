#include <QApplication>

#include "UIHandler.hpp"
#include "../GetOpt.hpp"

int help(const char *prog)
{
    std::cout << "USAGE\n\t" << prog << " [option]\n\nDESCRIPTION\n";
    std::cout << "\t-h, --help\tDisplay this help and exit\n";
    std::cout << "\t-a, --address\tUse the following address to connect with the server\n";
    std::cout << "\t-p, --port\tUse this port to start a connection with the server" << std::endl;
    return 0;
}

int main(int argc, char *argv[])
{
    std::string ip = "10.18.207.216";
    size_t port = 4242;

    auto args = GetOpt(std::list<char*>(argv+1, argv+argc), {
        {'h', "help", NoArg},
        {'p', "port", MandatoryArg},
        {'a', "address", MandatoryArg}
    });
    for (const auto &arg : args)
        if (arg.shortOpt == 'h')
            return help(argv[0]);
        else if (arg.shortOpt == 'p') {
            try {
                port = std::stoull(arg.value);
            } catch (const std::exception &e) {
                std::cerr << e.what() << std::endl;
                return 84;
            }
        } else if (arg.shortOpt == 'a')
            ip = arg.value;

    try {
        QApplication a(argc, argv);
        UIHandler ui(ip, port);
        return a.exec();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
}

/*
** By Kevin Pruvost, May 2020
** main.cpp
** File description:
** main
*/

// Project includes
#include "GraphicalClient.hpp"
#include "Json/Json.hpp"
#include "MainWindow.hpp"

// C++ includes
#include <fstream>

static void helpMsg()
{
    std::ifstream file("help_message");
    if (file)
    {
        std::string str;
        while (std::getline(file, str))
            std::cerr << str << std::endl;
    }
}

int main(int ac, char ** av)
{
    srand(time(NULL));

    std::string ip;
    std::string port;

    for (char c = getopt(ac, av, "p:h:D"); c != -1; c = getopt(ac, av, "p:h:D"))
    {
        if (c == 'p' && std::all_of(optarg, optarg + strlen(optarg), isdigit) && std::stol(optarg) <= 65535)
            port = optarg;
        else if (c == 'h')
            ip = optarg;
        else if (c == 'D')
        {
            Json json = Json::fromFile("../../zappySettings.json");
            port = json["serverDefaultValues"]["port"].get<std::string>();
            ip = json["serverDefaultValues"]["ip"].get<std::string>();
        }
    }

    if (port.empty() || ip.empty())
    {
        helpMsg();
        return EXIT_FAILURE;
    }

    try
    {
        MainWindow window(ip, port);
        return window.exec();
    }
    catch(const std::exception & e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
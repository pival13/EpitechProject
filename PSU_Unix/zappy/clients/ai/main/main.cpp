/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Ubuntu]
** File description:
** main
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>
#include <getopt.h>

#include "../Trantorian.hpp"
#include "../Layer.hpp"
#include "../littleAI/CannonFodder.hpp"
#include "../littleAI/Scrambler.hpp"
#include "../littleAI/TestAI.hpp"
#include "Json/Json.hpp"

std::string connectionHost = "localhost";
std::string connectionPort;

Json getSettingsAI()
{
    Json jsonSave = {
        {"timePerFood", 126},
        {"initialFood", 10},
        {"elevationPath", {
            {{"player", 1}, {"linemate", 1}},
            {{"player", 2}, {"linemate", 1}, {"deraumere", 1}, {"sibur", 1}},
            {{"player", 2}, {"linemate", 2}, {"sibur", 1}, {"phiras", 2}},
            {{"player", 4}, {"linemate", 1}, {"deraumere", 1}, {"sibur", 2}, {"phiras", 1}},
            {{"player", 4}, {"linemate", 1}, {"deraumere", 2}, {"sibur", 1}, {"mendiane", 3}},
            {{"player", 6}, {"linemate", 1}, {"deraumere", 2}, {"sibur", 3}, {"phiras", 1}},
            {{"player", 6}, {"linemate", 2}, {"deraumere", 2}, {"sibur", 2}, {"mendiane", 2}, {"phiras", 2}, {"thystame", 1}}
        }},
        {"commandTime", {
            {"Forward", 7},
            {"Right", 7},
            {"Left", 7},
            {"Look", 7},
            {"Inventory", 1},
            {"Broadcast @@@", 7},
            {"Connect_nbr", 0},
            {"Fork", 42},
            {"Eject", 7},
            {"Take @@@", 7},
            {"Set @@@", 7},
            {"Incantation", 300},
            {"Egg hatching", 600}
        }},
        {"serverDefaultValues", {
            {"ip", "localhost"},
            {"port", 4242},
            {"name", Json::asList({"Team1","Team2"})}
        }},
    };

    Json json;
    try {
        char *s = get_current_dir_name();
        std::string str(s);
        if (str.find("PSU_zappy_2019") != std::string::npos) {
            str = str.substr(str.find("PSU_zappy_2019")+14);
            std::string s2 = "./";
            for (size_t i = std::count(str.begin(), str.end(), '/'); i != 0; i--)
                s2 += "../";
            str = s2 + "zappySettings.json";
        } else
            str.clear();
        json = Json::fromFile(str);
        free(s);
        for (const std::string &key : jsonSave.keys())
            if (!json.contain(key))
                json[key] = jsonSave[key];
    } catch (const std::invalid_argument &e) {
        std::cerr << "Cannot open zappySettings.json" << std::endl;
        json = jsonSave;
    }

    Json elems({"food"});
    for (size_t i = 0; i != json["elevationPath"].size(); i++)
        for (const std::string &key : json["elevationPath"][i].keys()) {
            if (key != "player" && !elems.contain(Json(key)))
                elems.append(key);
        }

    json["collectable"] = std::move(elems);
    return json;
}

int print_help()
{
    std::cout << "Usage:\n\t./zappy_ai [-DT] [-h host] [-p port] [-n team-name]\n\nOptions:\n";
    std::cout << "\t-h, --host\tHost name. Can be either a domain name or an ip address. Default to \"localhost\".\n";
    std::cout << "\t-p, --port\tPort used by the host.\n";
    std::cout << "\t-n, --team-name\tTeam name to rejoin. If the team doesn't have any more place or doesn't exist, exit immediatly.\n";
    std::cout << "\t-D, --debug\tLaunch the AI with default values. Any options passed after will overload default values.\n";
    std::cout << "\t-T\t\tSame as -D, but the AI enter in manual mode. Command must be enter on standart input to be send to the server.\n";
    std::cout << "\t--child-kind\tKind of AI. Accept the following values:\n";
    std::cout << "\t\tTrantorian\tAn AI which will try to reach the maximum level of elevation. Need to be synchronized for some operation.\n";
    std::cout << "\t\tLayer\t\tAn AI which will create other AI and synchronize Trantorian.\n";
    std::cout << "\t\tScrambler\tAn AI which will only repeat the message it heard from people of other teams.\n";
    std::cout << "\t\tCannonFoddder\tAn AI which will only drop its food and die.\n";
    std::cout << "\t\tTester\t\tThe manual mode AI use with the -T option.\n";
    std::cout << "\t--help\t\tDisplay this help and exit" << std::endl;
    return 0;
}

int main(int n, char **argv)
{
    std::string teamName;
    std::string childKind = "Layer";
    struct option opt[] = {
        {"debug",      0, nullptr, 'D'},
        {"port",       1, nullptr, 'p'},
        {"host",       1, nullptr, 'h'},
        {"team-name",  1, nullptr, 'n'},
        {"child-kind", 1, nullptr, 1},
        {"help",       0, nullptr, 2},
        {nullptr,      0, nullptr, 0}
    };

    for (char c = getopt_long(n, argv, "p:h:n:DT", opt, nullptr); c != -1; c = getopt_long(n, argv, "p:h:n:D", opt, nullptr)) {
        if (c == 2)
            return print_help();
        if (c == 'T') {
            childKind = "Tester";
            c = 'D';
        }
        if (c == 'D') {
            Json json = getSettingsAI();
            if (connectionHost == "localhost")
                connectionHost = json["serverDefaultValues"]["ip"].get<std::string>();
            if (connectionPort.empty())
                connectionPort = json["serverDefaultValues"]["port"].get<std::string>();
            if (teamName.empty())
                teamName = json["serverDefaultValues"]["name"][0].get<std::string>();
        } else if (c == 'p' && std::all_of(optarg, optarg+strlen(optarg), isdigit) && std::stol(optarg) <= 65535)
            connectionPort = optarg;
        else if (c == 'h')
            connectionHost = optarg;
        else if (c == 'n')
            teamName = optarg;
        else if (c == 1)
            childKind = optarg;
    }

    if (connectionPort.empty() || teamName.empty() || connectionHost.empty()) {
        print_help();
        return 84;
    }

    try {
        std::unique_ptr<AI> player;
        if (childKind == "Trantorian")
            player = std::make_unique<Trantorian>(teamName);
        else if (childKind == "Layer")
            player = std::make_unique<Layer>(teamName);
        else if (childKind == "CannonFodder")
            player = std::make_unique<CannonFodder>(teamName);
        else if (childKind == "Scrambler")
            player = std::make_unique<Scrambler>(teamName);
        else if (childKind == "Tester")
            player = std::make_unique<TestAI>(teamName);
        else {
            print_help();
            return 84;
        }
        player->launch();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return EXIT_SUCCESS;
}
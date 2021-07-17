/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019 [WSL: Ubuntu]
** File description:
** main
*/

#include "System.hpp"

static void initiate_sys(nts::System &sys, char **arg, int n)
{
    for (int i = 0; i != n; i++) {
        std::cmatch m;

        if (std::regex_match(arg[i], m, std::regex("([^=]*)=(.*)"))) {
            try {
                sys.assign(m[1].str(), m[2].str(), true);
            } catch (const std::exception &e) {
                std::cerr << e.what() << std::endl;
            }
        } else
            std::cerr << "Invalid input: " << arg[i] << std::endl;
    }
}

static void execute_loop(nts::System &sys)
{
    std::string str;
    std::cout << "> ";
    std::getline(std::cin, str);
    while (!std::cin.eof() || str.length() > 0) {
        std::smatch m;
        try {
            if (str == "exit")
                break;
            else if (str == "display")
                sys.display();
            else if (str == "simulate")
                sys.simulate();
            else if (str == "loop")
                sys.loop();
            else if (str == "dump")
                sys.dump();
            else if (std::regex_match(str, m, std::regex("([^=]+)=(.+)")))
                sys.assign(m[1].str(), m[2].str(), false);
            else
                std::cout << "Invalid command" << std::endl;
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }

        std::cout << "> ";

        if (std::cin.eof())
            break;
        std::getline(std::cin, str);
    }
}

int main(int n, char **arg)
{
    if (n < 2) {
        std::cerr << "Missing input file" << std::endl;
        return 84;
    }
    try {
        nts::System sys(arg[1]);
        initiate_sys(sys, &arg[2], n-2);
        sys.simulate();
        sys.display();
        execute_loop(sys);
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        exit(84);
    }
    return 0;
}
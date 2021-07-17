#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

#include "Ncurses/TextualDisplay.hpp"

void test_name()
{
    ModuleName module;

    std::cout << "\e[1;32m============== Test name =============\e[0m" << std::endl;
    oneTimeInfo info = module.getOneInfo();
    for (std::pair<std::string, std::string> data : info)
        std::cout << data.first << ": " << data.second << std::endl;
}
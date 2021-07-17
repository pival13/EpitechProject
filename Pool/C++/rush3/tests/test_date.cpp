#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

#include "Ncurses/TextualDisplay.hpp"

void test_datetime()
{
    ModuleDatetime module;

    std::cout << "\e[1;32m============== Test date =============\e[0m" << std::endl;
    for (int i = 0; i != 10; i++) {
        module.update();
        oneTimeInfo info = module.getOneInfo();
        std::cout << "\e[1;36m========== T " << i+1 << " =========\e[0m" << std::endl;
        for (std::pair<std::string, std::string> data : info)
            std::cout << data.first << ": " << data.second << std::endl;
        if (i != 9) {
            std::cout << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }
}
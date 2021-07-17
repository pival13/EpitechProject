#include <regex>
#include <thread>

#include "Brain.hpp"

int main(void)
{
    std::string s;
    std::getline(std::cin, s);
    std::smatch m;
    if (!std::regex_match(s, m, std::regex("^START (\\d+)$")) || m[1] == "0") {
        error << "Expected \"START {nb}\", with nb a non-null integer, but got \""<<s<<"\"" << std::endl;
        return 0;
    }

    srand(time(nullptr));
    Brain b(std::stoull(m[1]));
    return b.run();
}
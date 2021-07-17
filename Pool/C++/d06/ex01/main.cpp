    /*
** EPITECH PROJECT, 2020
** main
** File description:
** main of ex01
*/

#include <iostream>
#include <iomanip>
#include <regex>
#include <fstream>
#include <cctype>

std::string tolower(std::string &str)
{
    for (size_t i = 0; i != str.size(); i++)
        str[i] = tolower(str[i]);
    return str;
}

int main(void)
{
    std::string str;
    std::smatch re;
    float tmp;

    std::getline(std::cin, str);
    std::regex_search(str, re, std::regex("^\\s*(-?\\d+)\\s+(\\w+)"));
    tmp = atof(re[1].str().c_str());
    str = re[2].str().c_str();

    if (tolower(str) == "fahrenheit") {
        tmp = 5.0 / 9.0 * (tmp-32);
        str = "Celsius";
    } else if (tolower(str) == "celsius") {
        str = "Fahrenheit";
        tmp = tmp * 9.0 / 5.0 + 32;
    }

    std::cout << std::fixed << std::setprecision(3);
    std::cout << std::setfill(' ') << std::setw(16) << tmp;
    std::cout << std::setfill(' ') << std::setw(16) << str << std::endl;
}
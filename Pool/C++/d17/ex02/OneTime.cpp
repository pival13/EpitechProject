/*
** EPITECH PROJECT, 2020
** cpp_d17_2019 [WSL: Ubuntu]
** File description:
** OneTime
*/

#include "OneTime.hpp"

OneTime::OneTime(const std::string &key) : key(key), index(0)
{
}

OneTime::~OneTime()
{
}

void OneTime::encryptChar(char plainchar)
{
    char ikey = (key[index] >= 'a' && key[index] <= 'z' ? key[index] - 'a' : key[index] - 'A');
    
    if (plainchar >= 'a' && plainchar <= 'z')
        std::cout << (char)((plainchar - 'a' + ikey) % 26 + 'a');
    else if (plainchar >= 'A' && plainchar <= 'Z')
        std::cout << (char)((plainchar - 'A' + ikey) % 26 + 'A');
    else
        std::cout << plainchar;
    index = (index + 1) % key.size();
}

void OneTime::decryptChar(char cipherchar)
{
    char ikey = (key[index] >= 'a' && key[index] <= 'z' ? key[index] - 'a' : key[index] - 'A');
    
    if (cipherchar >= 'a' && cipherchar <= 'z')
        std::cout << (char)((cipherchar - 'a' - ikey+26) % 26 + 'a');
    else if (cipherchar >= 'A' && cipherchar <= 'Z')
        std::cout << (char)((cipherchar - 'A' - ikey+26) % 26 + 'A');
    else
        std::cout << cipherchar;
    index = (index + 1) % key.size();
}

void OneTime::reset() { index = 0; }

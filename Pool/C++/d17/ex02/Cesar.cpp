/*
** EPITECH PROJECT, 2020
** cpp_d17_2019 [WSL: Ubuntu]
** File description:
** Cesar
*/

#include "Cesar.hpp"

Cesar::Cesar() : shift(3)
{
}

Cesar::~Cesar()
{
}

void Cesar::encryptChar(char plainchar)
{
    if (plainchar >= 'a' && plainchar <= 'z')
        std::cout << (char)((plainchar - 'a' + shift) % 26 + 'a');
    else if (plainchar >= 'A' && plainchar <= 'Z')
        std::cout << (char)((plainchar - 'A' + shift) % 26 + 'A');
    else
        std::cout << plainchar;
    shift++;
    shift %= 26;
}

void Cesar::decryptChar(char cipherchar)
{
    if (cipherchar >= 'a' && cipherchar <= 'z')
        std::cout << (char)((cipherchar - 'a' - shift + 26) % 26 + 'a');
    else if (cipherchar >= 'A' && cipherchar <= 'Z')
        std::cout << (char)((cipherchar - 'A' - shift + 26) % 26 + 'A');
    else
        std::cout << cipherchar;
    shift++;
    shift %= 26;
}

void Cesar::reset() { shift = 3; }

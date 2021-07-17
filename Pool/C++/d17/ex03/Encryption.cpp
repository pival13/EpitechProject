/*
** EPITECH PROJECT, 2020
** cpp_d17_2019 [WSL: Ubuntu]
** File description:
** Encryption
*/

#include "Encryption.hpp"

Encryption::Encryption(IEncryptionMethod &meth, void (IEncryptionMethod::*f)(char))
: method(meth), ptr(f)
{
}

Encryption::~Encryption()
{
}

void Encryption::operator()(char c)
{
    (method.*ptr)(c);
}

void Encryption::encryptString(IEncryptionMethod &method, const std::string &string)
{
    method.reset();
    std::for_each(string.begin(), string.end(), Encryption(method, &IEncryptionMethod::encryptChar));
    std::cout << std::endl;
}

void Encryption::decryptString(IEncryptionMethod &method, const std::string &string)
{
    method.reset();
    std::for_each(string.begin(), string.end(), Encryption(method, &IEncryptionMethod::decryptChar));
    std::cout << std::endl;
}
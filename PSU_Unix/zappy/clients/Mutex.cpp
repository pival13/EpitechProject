/*
** By Kevin Pruvost, June 2020
** File description:
** Mutex class.
*/

#include "Mutex.hpp"

#include <iostream>

Mutex::Mutex()
{
}

Mutex::~Mutex()
{
}

void Mutex::lock(const std::string & str)
{
    locked = true;
    //std::cerr << "Lock : " << str << std::endl;
    std::mutex::lock();
}

void Mutex::unlock()
{
    locked = false;
    //std::cerr << "Unlock" << std::endl;
    std::mutex::unlock();
}
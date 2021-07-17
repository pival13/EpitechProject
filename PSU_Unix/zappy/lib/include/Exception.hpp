/*
** EPITECH PROJECT, 2020
** Exception.hpp
** File description:
** exception
*/

#pragma once

// C++ includes
#include <cassert>
#include <exception>
#include <string>
#include <sstream>
#include <iostream>

#define EXCEPTION(msg) Exception(std::string(__FILE__)\
                       + ": line " + std::to_string(__LINE__) + ": " + msg)
#define DEBUG(msg) if (Debug::mode) std::cerr << msg << std::endl;
#define DEBUG_FLUSH(msg) if (Debug::mode) std::cerr << msg << std::flush;
#define DEBUG_ON Debug::mode = true;
#define DEBUG_OFF Debug::mode = false;
#define GREEN_START "\033[1;32m"
#define RED_START "\033[1;31m"
#define YELLOW_START "\033[1;33m"
#define END_COLOR "\033[0m"
#define UNUSED(x) (void)x

namespace Debug
{
extern bool mode;
};

class Exception : virtual public std::exception
{
    public:
        explicit Exception(const std::string & message);
        virtual ~Exception() throw();

        const char * what() const throw() override;

    private:
        const std::string _msg;
};

#undef  EXIT_FAILURE
#define EXIT_FAILURE 84
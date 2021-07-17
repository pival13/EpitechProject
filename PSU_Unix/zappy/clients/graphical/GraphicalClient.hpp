/*
** By Kevin Pruvost, May 2020
** GraphicalClient.hpp
** File description:
** graphical
*/

#pragma once

// Project includes
#include "Client.hpp"

/**
 * @brief Inherits from Client, is made espcially for the graphical part.
 */
class GraphicalClient : virtual public Client
{
public:
    GraphicalClient(const char * ip, uint16_t port);
    GraphicalClient(const std::string & ip, const std::string & port);
    ~GraphicalClient();

protected:
private:
};
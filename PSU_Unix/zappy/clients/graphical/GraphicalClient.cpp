/*
** By Kevin Pruvost, May 2020
** GraphicalClient.cpp
** File description:
** g
*/

#include "GraphicalClient.hpp"

GraphicalClient::GraphicalClient(const char * ip, uint16_t port)
    : Client(ip, port, "GRAPHIC")
{

}

GraphicalClient::GraphicalClient(const std::string & ip, const std::string & port)
    : GraphicalClient(ip.c_str(), std::stoi(port))
{
}

GraphicalClient::~GraphicalClient()
{
}
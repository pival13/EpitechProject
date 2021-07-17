/*
** EPITECH PROJECT, 2020
** B-CPP-501-NCY-5-1-rtype-etienne.miltgen
** File description:
** ReadUdpMessage
*/

#include "ReadUdpMessage.hpp"

ReadUdpMessage::ReadUdpMessage()
{
}

ReadUdpMessage::ReadUdpMessage(std::string buffer)
    : data(buffer.data(), buffer.data() + buffer.size())
{
}

ReadUdpMessage::~ReadUdpMessage()
{
}

header_udp_input_t ReadUdpMessage::getHeader()
{
    header_udp_input_t header;

    std::memcpy((char *)&header, this->data.data(), sizeof(header_udp_input_t));
    deletePartOfData(sizeof(header_udp_input_t));
    return header;
}

std::vector<unsigned char> ReadUdpMessage::getInput()
{
    std::vector<unsigned char> input;

    input.resize(sizeof(RTypeNetworkInput));
    std::memcpy(input.data(), this->data.data(), sizeof(RTypeNetworkInput));

    deletePartOfData(sizeof(RTypeNetworkInput));
    return input;
}

/**
 * @brief add Command to the currently data.
 *
 * @param buffer Command to add.
 */
void ReadUdpMessage::addCommand(std::vector<unsigned char> buffer)
{
    this->data.insert(this->data.end(), buffer.begin(), buffer.end());
}


/**
 * @brief Delete n bytes of the data.
 *
 * @param length n bytes which are going to be deleted.
 */
void ReadUdpMessage::deletePartOfData(std::size_t length)
{
    this->data.erase(this->data.begin(), this->data.begin() + length);
}

std::size_t ReadUdpMessage::getLength() const
{
    return this->data.size();
}

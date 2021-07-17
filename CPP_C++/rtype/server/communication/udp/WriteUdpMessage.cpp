/*
** EPITECH PROJECT, 2020
** B-CPP-501-NCY-5-1-rtype-etienne.miltgen
** File description:
** WriteUdpMessage
*/

#include "WriteUdpMessage.hpp"

WriteUdpMessage::WriteUdpMessage()
{
    this->__length = 0;
}

WriteUdpMessage::~WriteUdpMessage()
{
}


std::vector<unsigned char> WriteUdpMessage::getData() const
{
    return this->__data;
}

std::size_t WriteUdpMessage::getLength() const
{
    return this->__length;
}

void WriteUdpMessage::addData(void *data, std::size_t length)
{
    this->__data.resize(this->__length + length);
    std::memcpy(this->__data.data() + this->__length, data, length);
    this->__length += length;
}

void WriteUdpMessage::setData(void *data, std::size_t length)
{
    this->__length = length;
    this->__data.resize(this->__length);
    std::memcpy(this->__data.data(), data, length);
}

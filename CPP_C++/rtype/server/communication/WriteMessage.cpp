/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** WriteBuffer
*/

#include "WriteMessage.hpp"

WriteMessage::WriteMessage()
{
    this->length = 0;
}

WriteMessage::~WriteMessage()
{
}

std::vector<char> WriteMessage::getData() const
{
    return this->data;
}

std::size_t WriteMessage::getLength() const
{
    return this->length;
}

void WriteMessage::addData(void *data, std::size_t length)
{
    this->data.resize(this->length + length);
    std::memcpy(this->data.data() + this->length, data, length);
    this->length += length;
}

void WriteMessage::setData(void *data, std::size_t length)
{
    this->length = length;
    this->data.resize(this->length);
    std::memcpy(this->data.data(), data, length);
}

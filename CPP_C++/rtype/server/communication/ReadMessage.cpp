/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** ReadMessage
*/

#include "ReadMessage.hpp"

ReadMessage::ReadMessage()
{
}

ReadMessage::ReadMessage(std::string buffer)
    : data(buffer.data(), buffer.data() + buffer.size())
{
}

ReadMessage::~ReadMessage()
{
}

/**
 * @brief add Command to the currently data.
 *
 * @param buffer Command to add.
 */
void ReadMessage::addCommand(std::vector<char> buffer)
{
    this->data.insert(this->data.end(), buffer.begin(), buffer.end());
}

/**
 * @brief Return the size of the data.
 *
 * @return std::size_t Size of the data.
 */
std::size_t ReadMessage::getDataLength()
{
    return this->data.size();
}

/**
 * @brief Get a header inside the data.
 *
 * @return header_t The first header found inside the data.
 */
header_t ReadMessage::getHeader()
{
    header_t header;

    std::memcpy((char *)&header, this->data.data(), sizeof(header_t));
    if (header.size == 0)
        deletePartOfData(sizeof(header_t) + 3);
    else
        deletePartOfData(sizeof(header_t));
    return header;
}

/**
 * @brief get a room send by the user
 * 
 * @return room_t All room's information.
 */
create_room_t ReadMessage::getRoom()
{
    create_room_t room;

    std::memcpy((char *)&room + sizeof(header_t),
            this->data.data(), sizeof(create_room_t) - sizeof(header_t));

    deletePartOfData(sizeof(room) - sizeof(header_t) + 3);
    return room;
}

/**
 * @brief Return the contains of the join room request.
 * 
 * @return join_room_t Contains all informations about the request
 */
join_room_t ReadMessage::getJoinRoom()
{
    join_room_t room;

    std::memcpy((char *)&room + sizeof(header_t),
            this->data.data(), sizeof(room) - sizeof(header_t));

    deletePartOfData(sizeof(room) - sizeof(header_t) + 3);
    return room;
}

/**
 * @brief Return the contains of the create room request.
 * 
 * @return create_room_t Contains all informations about the client's request.
 */
create_room_t ReadMessage::getCreateRoom()
{
    create_room_t room;

    std::memcpy((char *)&room + sizeof(header_t),
            this->data.data(), sizeof(room) - sizeof(header_t));

    deletePartOfData(sizeof(room) - sizeof(header_t) + 3);
    return room;
}

/**
 * @brief Return the contains of the leave room request.
 * 
 * @return leave_room_t Contains all informations about the client's request.
 */
leave_room_t ReadMessage::getLeaveRoom()
{
    leave_room_t room;

    std::memcpy((char *)&room + sizeof(header_t),
            this->data.data(), sizeof(room) - sizeof(header_t));

    deletePartOfData(sizeof(room) - sizeof(header_t) + 3);
    return room;
}

/**
 * @brief Delete n bytes of the data.
 *
 * @param length n bytes which are going to be deleted.
 */
void ReadMessage::deletePartOfData(std::size_t length)
{
    this->data.erase(this->data.begin(), this->data.begin() + length);
}

/**
 * @brief Return data's length.
 *
 * @return const std::size_t data's length.
 */
std::size_t ReadMessage::getLength() const
{
    return this->length;
}

/**
 * @brief Return data.
 *
 * @return const std::string data.
 */
std::vector<char> ReadMessage::getData() const
{
    return this->data;
}

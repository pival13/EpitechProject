/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** ReadMessage
*/

#ifndef READMESSAGE_HPP_
#define READMESSAGE_HPP_

#include <iostream>
#include <cstring>
#include <vector>

#include "include/room.hpp"

class ReadMessage
{
    public:
        ReadMessage();
        ReadMessage(std::string);
        ~ReadMessage();
        void addCommand(std::vector<char>);
        std::size_t getDataLength();
        header_t getHeader();
        std::size_t getLength() const;
        std::vector<char> getData() const;
        create_room_t getRoom();
        join_room_t getJoinRoom();
        create_room_t getCreateRoom();
        leave_room_t getLeaveRoom();
        void deletePartOfData(std::size_t);

    private:
        std::vector<char> data;
        std::size_t length;
};

#endif /* !READMESSAGE_HPP_ */

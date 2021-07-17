/*
** EPITECH PROJECT, 2020
** B-CPP-501-NCY-5-1-rtype-etienne.miltgen
** File description:
** ReadUdpMessage
*/

#ifndef READUDPMESSAGE_HPP_
#define READUDPMESSAGE_HPP_

#include <iostream>
#include <cstring>
#include <vector>

#include "../include/room.hpp"
#include "../../../structures/RTypeNetworkInput.hpp"
#include "../../../structures/RTypeEvents.hpp"


class ReadUdpMessage {
    public:
        ReadUdpMessage();
        ReadUdpMessage(std::string buffer);
        ~ReadUdpMessage();
        header_udp_input_t getHeader();
        std::vector<unsigned char> getInput();
        void addCommand(std::vector<unsigned char>);
        void deletePartOfData(std::size_t);
        std::size_t getLength() const;

    private:
        std::vector<unsigned char> data;
};

#endif /* !READUDPMESSAGE_HPP_ */

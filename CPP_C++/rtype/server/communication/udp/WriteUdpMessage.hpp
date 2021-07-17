/*
** EPITECH PROJECT, 2020
** B-CPP-501-NCY-5-1-rtype-etienne.miltgen
** File description:
** WriteUdpMessage
*/

#ifndef WRITEUDPMESSAGE_HPP_
#define WRITEUDPMESSAGE_HPP_

#include <cstring>
#include <iostream>
#include <vector>

class WriteUdpMessage {
    public:
        WriteUdpMessage();
        ~WriteUdpMessage();
        std::vector<unsigned char> getData() const;
        std::size_t getLength() const;
        void setData(void *data, std::size_t length);
        void addData(void *data, std::size_t length);

    private:
        std::vector<unsigned char> __data;
        std::size_t __length;
};

#endif /* !WRITEUDPMESSAGE_HPP_ */

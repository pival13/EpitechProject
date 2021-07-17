/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** WriteBuffer
*/

#ifndef WRITEBUFFER_HPP_
#define WRITEBUFFER_HPP_

#include <cstring>
#include <iostream>
#include <vector>

class WriteMessage {
    public:
        WriteMessage();
        ~WriteMessage();
        std::vector<char> getData() const;
        std::size_t getLength() const;
        void setData(void *data, std::size_t length);
        void addData(void *data, std::size_t length);

    private:
        std::vector<char> data;
        std::size_t length;
};

#endif /* !WRITEBUFFER_HPP_ */

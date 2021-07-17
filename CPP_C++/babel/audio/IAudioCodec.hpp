/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** IAudioCodec
*/

#pragma once

#include <vector>

template <typename T>
class IAudioCodec {
    public:
        virtual ~IAudioCodec() = default;

        ///@brief Encode a sound into a vector of bytes
        ///@param data 
        ///@return std::vector<uint8_t> 
        virtual std::vector<uint8_t> encodeData(const std::vector<T> &data) = 0;
        ///@brief Decode a vector of bytes into a sound
        ///@param data 
        ///@return std::vector<T> 
        virtual std::vector<T> decodeData(const std::vector<uint8_t> &data) = 0;
};

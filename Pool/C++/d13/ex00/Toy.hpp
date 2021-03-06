/*
** EPITECH PROJECT, 2020
** cpp_d13_2019 [WSL: Ubuntu]
** File description:
** Toy
*/

#pragma once

#include "Picture.hpp"

class Toy {
    public:
        enum ToyType {
            BASIC_TOY,
            ALIEN
        };

        Toy();
        Toy(const ToyType type, const std::string &name, const std::string &file);
        ~Toy();

        ToyType getType() const;
        std::string getName() const;
        std::string getAscii() const;
        void setName(const std::string &name);
        bool setAscii(const std::string &file);

    protected:
    private:
        const ToyType _type;
        std::string _name;
        Picture _pict;
};

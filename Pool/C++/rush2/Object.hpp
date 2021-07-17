/*
** EPITECH PROJECT, 2020
** rush2 [WSL: Ubuntu]
** File description:
** Object
*/

#pragma once

#include <iostream>

class Object {
    public:
        Object(const std::string &title);
        virtual ~Object() {}
    
        const std::string &getTitle() const;
        int getType() const;
        enum ClassType {
            BOX,
            GIFTPAPER,
            LITTLEPONNY,
            TEDDY
        };
    protected:
        ClassType _Type;

        const std::string _title;

    private:
};

Object **MyUnitTests();

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
            ALIEN,
            BUZZ,
            WOODY
        };

        Toy();
        Toy(const Toy &);
        Toy(const ToyType type, const std::string &name, const std::string &file);
        ~Toy();

        Toy &operator=(const Toy &);

        ToyType getType() const;
        std::string getName() const;
        std::string getAscii() const;
        void setName(const std::string &name);
        bool setAscii(const std::string &file);

        Toy &operator<<(const std::string &str);

        virtual bool speak(const std::string &str);
        virtual bool speak_es(const std::string &str);

        class Error {
            public:
                enum ErrorType {
                    UNKNOWN,
                    PICTURE,
                    SPEAK
                };

                Error(ErrorType err);
                ~Error();

                std::string what() const;
                std::string where() const;
                ErrorType type;
        };

        Error getLastError() const;

    protected:
    private:
        ToyType _type;
        std::string _name;
        Picture _pict;
        Error _error;
};

std::ostream &operator<<(std::ostream &os, const Toy &t);
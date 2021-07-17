/*
** EPITECH PROJECT, 2020
** cpp_d06_2019 [WSL: Ubuntu]
** File description:
** SickKoalaList
*/

#ifndef SICKKOALALIST_H
#define SICKKOALALIST_H

#include "SickKoala.hpp"

struct SickKoalaList {
		SickKoalaList(SickKoala *);
		~SickKoalaList();

        bool isEnd();
        void append(SickKoalaList *);
        bool contain(SickKoalaList *);
        SickKoala *getFromName(std::string);
        SickKoalaList *remove(SickKoalaList *);
        SickKoalaList *removeFromName(std::string);
        SickKoala *getContent();
        SickKoalaList *getNext();
        void dump();

        SickKoala *value;
        SickKoalaList *next;
};

#endif
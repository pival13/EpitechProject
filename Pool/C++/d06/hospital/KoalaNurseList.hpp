/*
** EPITECH PROJECT, 2020
** cpp_d06_2019 [WSL: Ubuntu]
** File description:
** KoalaNurseList
*/

#ifndef KOALANURSELIST_H
#define KOALANURSELIST_H

#include "KoalaNurse.hpp"

struct KoalaNurseList {
		KoalaNurseList(KoalaNurse *);
		~KoalaNurseList();

        bool isEnd();
        void append(KoalaNurseList *);
        bool contain(KoalaNurseList *);
        size_t size();
        KoalaNurse *getFromID(int);
        KoalaNurseList *remove(KoalaNurseList *);
        KoalaNurseList *removeFromID(int);
        KoalaNurse *getContent();
        KoalaNurse *getContent(int);
        KoalaNurseList *getNext();
        void dump();

        KoalaNurse *value;
        KoalaNurseList *next;
};

#endif
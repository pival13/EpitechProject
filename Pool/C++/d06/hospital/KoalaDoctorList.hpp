/*
** EPITECH PROJECT, 2020
** cpp_d06_2019 [WSL: Ubuntu]
** File description:
** KoalaDoctorList
*/

#ifndef KOALADOCTORLIST_H
#define KOALADOCTORLIST_H

#include "KoalaDoctor.hpp"

struct KoalaDoctorList {
		KoalaDoctorList(KoalaDoctor *);
		~KoalaDoctorList();

        bool isEnd();
        void append(KoalaDoctorList *);
        bool contain(KoalaDoctorList *);
        size_t size();
        KoalaDoctor *getFromName(std::string);
        KoalaDoctorList *remove(KoalaDoctorList *);
        KoalaDoctorList *removeFromName(std::string);
        KoalaDoctor *getContent();
        KoalaDoctor *getContent(int);
        KoalaDoctorList *getNext();
        void dump();

        KoalaDoctor *value;
        KoalaDoctorList *next;
};

#endif
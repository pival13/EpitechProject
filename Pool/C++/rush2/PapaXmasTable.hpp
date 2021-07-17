/*
** EPITECH PROJECT, 2020
** cpp_rush2_2019 [WSL: Ubuntu]
** File description:
** PapaXmasTable
*/

#pragma once

#include "ITable.hpp"

class PapaXmasTable : public ITable {
    public:
        PapaXmasTable();
        ~PapaXmasTable();

        std::string *getTitle() const;
        void addToy(Object *&);
        void addBox(Object *&);
        void addPaper(Object *&);
        Object *takeToy();
        Object *takeBox();
        Object *takePaper();
        bool toyIsEmpty();
        bool boxIsEmpty();
        bool paperIsEmpty();
        Box *getFirstBox();
        GiftPaper *getFirstPaper();

    protected:
    private:
};

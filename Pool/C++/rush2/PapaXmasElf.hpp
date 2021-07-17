/*
** EPITECH PROJECT, 2020
** cpp_rush2_2019 [WSL: Ubuntu]
** File description:
** PapaXmasElf
*/

#pragma once

#include "IElf.hpp"

class PapaXmasElf : public IElf {
    public:
        PapaXmasElf();
        ~PapaXmasElf();

        std::string *look(const ITable &) const;
        bool createGift(ITable &, IConveyorBelt &);
        
        void putObject(ITable &);
        void putObject(IConveyorBelt &);
        void takeToy(ITable &);
        void takeBox(ITable &);
        void takePaper(ITable &);
        void takeObject(IConveyorBelt &);

        void pushIN(IConveyorBelt &) const;
        void pushOUT(IConveyorBelt &) const;

    protected:
    private:
};

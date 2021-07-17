/*
** EPITECH PROJECT, 2020
** cpp_rush2_2019 [WSL: Ubuntu]
** File description:
** IElf
*/

#pragma once

#include "Object.hpp"
#include "ITable.hpp"
#include "IConveyorBelt.hpp"

class IElf {
	public:
		virtual ~IElf() {}

        virtual std::string *look(const ITable &) const = 0;
        virtual bool createGift(ITable &, IConveyorBelt &) = 0;
        
        virtual void putObject(ITable &) = 0;
        virtual void putObject(IConveyorBelt &) = 0;
        virtual void takeToy(ITable &) = 0;
        virtual void takeBox(ITable &) = 0;
        virtual void takePaper(ITable &) = 0;
        virtual void takeObject(IConveyorBelt &) = 0;

        virtual void pushIN(IConveyorBelt &) const = 0;
        virtual void pushOUT(IConveyorBelt &) const = 0;

	protected:
        Object *_hand;
	private:
};

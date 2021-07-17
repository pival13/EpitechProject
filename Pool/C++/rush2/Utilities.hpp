/*
** EPITECH PROJECT, 2020
** cpp_rush2_2019
** File description:
** Utilities
*/

#ifndef UTILITIES_HPP_
#define UTILITIES_HPP_

#include "Box.hpp"
#include "GiftPaper.hpp"
#include "Teddy.hpp"
#include "LittlePony.hpp"
#include "PapaXmasTable.hpp"
#include "TableRand.hpp"
#include "ConveyorBelt.hpp"
#include "ConveyorBeltRand.hpp"
#include "PapaXmasElf.hpp"
#include <array>

Object *MyUnitTests(Object  **);
Object **MyUnitTests();

ITable *createTable();
IConveyorBelt *createConveyorBelt();
IConveyorBelt *createConveyorBeltRand();
IElf *createElf();


#endif /* !UTILITIES_HPP_ */

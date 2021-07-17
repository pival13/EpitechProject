/*
** EPITECH PROJECT, 2020
** cpp_rush2_2019
** File description:
** Utilities
*/

#include "Utilities.hpp"

Object **MyUnitTests()
{
    static Object* newArray[3];

    newArray[2] = nullptr;
    newArray[0] = new LittlePony("happy pony");
    newArray[1] = new Teddy("cuddles");

    return (newArray);
}

Object *MyUnitTests(Object  **arr)
{
    if (arr[0] == nullptr || arr[1] == nullptr || arr[2] == nullptr || arr[3] != nullptr) {
        std::cerr << "Error in parameter" << std::endl;
        return (nullptr);
    }
    Toy *newToy = dynamic_cast<Toy *>(arr[0]);
    Box *newBox = dynamic_cast <Box *>(arr[1]);
    GiftPaper *newGiftPaper = dynamic_cast<GiftPaper *>(arr[2]);

    newToy->isTaken();
    newBox->openMe();
    newBox->wrapMeThat(arr[0]);
    newBox->closeMe();
    newGiftPaper->openMe();
    newGiftPaper->wrapMeThat(arr[1]);
    return newGiftPaper;
}

ITable *createTable()
{
    PapaXmasTable *newTable = new PapaXmasTable();

    Object *firstToy = new LittlePony("xXDark_UnicornXx");
    Object *secondToy = new Teddy("KEVINLeBG99");
    Object *firstBox = new Box();
    Object *secondBox = new Box();
    Object *firstGift = new GiftPaper();
    Object *secondGift = new GiftPaper();

    newTable->addToy(firstToy);
    newTable->addToy(secondToy);
    newTable->addBox(firstBox);
    newTable->addBox(secondBox);
    newTable->addPaper(firstGift);
    newTable->addPaper(secondGift);

    return(newTable);
}

IConveyorBelt *createConveyorBelt()
{
    PapaXmasConveyorBelt *newConveyor = new PapaXmasConveyorBelt();

    return (newConveyor);
}

IConveyorBelt *createConveyorBeltRand()
{
    ConveyorBeltRand *newConveyor = new ConveyorBeltRand();

    return (newConveyor);
}

IElf *createElf()
{
    PapaXmasElf *elf = new PapaXmasElf();
    return (elf);
}

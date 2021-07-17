/*
** EPITECH PROJECT, 2020
** cpp_rush2_2019
** File description:
** main
*/

#include "../Utilities.hpp"
/*
int main()
{
   Object *table[4];
   table[0] = new LittlePony("hi ha");
   table[1] = new Box;
   table[2] = new GiftPaper;
   table[3] = nullptr;
   auto tab = MyUnitTests();
   std::cout << tab[0]->getTitle() << " /// " << tab[1]->getTitle() << std::endl;
   std::cout << "--------------------------" << std::endl;
   GiftPaper *gift = dynamic_cast<GiftPaper *>(MyUnitTests(table));
   Wrap *box = dynamic_cast<Box *>(gift->getObject());
   auto toy = box->getObject();
   std::cout << gift->getTitle() << " /// " << box->getTitle() << " /// " << toy->getTitle() << std::endl;
   std::cout << "--------------------------" << std::endl;
   srandom(time(nullptr));
   TableRand tb;
   std::string *arr = tb.getTitle();
   for (int i = 0; !arr[i].empty(); i++)
       std::cout << arr[i] << std::endl;
}*/



int main(void)
{
    srandom(time(nullptr));
    //ITable *table = createTable();
    ITable *tableRand = new TableRand();
    //IConveyorBelt *conveyor = createConveyorBelt();
    IConveyorBelt *conveyorRand = createConveyorBeltRand();
    IElf *elf = createElf();

    std::cout << "Initial table: " << std::endl;
    std::string *arr = tableRand->getTitle();
    for (int i = 0; !arr[i].empty(); i++)
        std::cout << " * " << arr[i] << std::endl;
    std::cout << std::endl;

    while (elf->createGift(*tableRand, *conveyorRand));

    return (0);
}

/*
int main(void)
{
    PapaXmasTable *table = new PapaXmasTable();
    PapaXmasConveyorBelt *cbelt = new PapaXmasConveyorBelt();
    PapaXmasElf *elf = new PapaXmasElf();

    for (int i = 0 ; i != 5; i++) {
        Object *obj = new Teddy("Teddy Bear");
        table->addToy(obj);
    }
    for (int i = 0; i != 4; i++) {
        Object *obj = new LittlePony("Arc-En-Ciel");
        table->addToy(obj);
    }

    std::cout << "Initial table: " << std::endl;
    std::string *arr = table->getTitle();
    for (int i = 0; !arr[i].empty(); i++)
        std::cout << " * " << arr[i] << std::endl;
    std::cout << std::endl;

    while (elf->createGift(*table, *cbelt));

    //delete(arr);
    return (0);
}*/
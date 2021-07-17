/*
** EPITECH PROJECT, 2020
** cpp_rush2_2019 [WSL: Ubuntu]
** File description:
** Santa
*/

#include "Santa.hpp"

void checkListOfGift(Object **listObj)
{
    if (listObj == nullptr)
        return;
    for (int i = 0; listObj[i] != nullptr; i++) {
        Object *tmp = listObj[i];
        std::cout << "This gift is composed of ";
        while (tmp != nullptr) {
            std::cout << "a " << tmp->getTitle();
            if (tmp->getType() < Object::LITTLEPONNY) {
                tmp = dynamic_cast<Wrap *>(tmp)->openMe();
                if (tmp == nullptr) {
                    std::cout << "." << std::endl;
                    std::cerr << "Why is there a gift without a Toy?" << std::endl;
                } else {
                    std::cout << ", ";
                }
            } else {
                std::cout << "." << std::endl;
                dynamic_cast<Toy *>(tmp)->isTaken();
                tmp = nullptr;
            }
        }
    }
}

int main(int argc, char **argv)
{
    for (int i = 1; i < argc; i++) {
        checkListOfGift(readXMLGift(argv[i]));
    }
}
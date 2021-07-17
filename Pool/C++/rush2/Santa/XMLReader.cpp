/*
** EPITECH PROJECT, 2020
** cpp_rush2_2019 [WSL: Ubuntu]
** File description:
** XMLReader
*/

#include <iostream>
#include <fstream>
#include <regex>
#include "Teddy.hpp"
#include "LittlePony.hpp"
#include "Box.hpp"
#include "GiftPaper.hpp"

Object *readXMLGiftObject(std::string &content)
{
    std::smatch openBalise;
    std::smatch string;

    if (!std::regex_search(content, openBalise, std::regex("<([^>/]*)>")))
        return nullptr;
    std::string type = openBalise[1].str();
    if (std::regex_search(content, string, std::regex("<" + type + ">(.*)</" + type + ">"))) {
        std::string s = string[1].str();
        Object *obj = readXMLGiftObject(s);
        if (type == "Box") {
            Box *obj2 = new Box();
            if (obj) {
                obj2->openMe();
                obj2->wrapMeThat(obj);
            }
            return obj2;
        } else if (type == "GiftPaper") {
            GiftPaper *obj2 = new GiftPaper(); 
            if (obj)
                obj2->wrapMeThat(obj);
            return obj2;
        } else if (type == "Teddy") {
            obj = new Teddy(s);
            return obj;
        } else {
            obj = new LittlePony(s);
            return obj;
        }
    }
    return nullptr;
}

Object **readXMLGiftContent(std::string &content)
{
    Object **obj = new Object *[10];
    int i = 0;

    while (1) {
        std::string s = content.substr(0, content.find_first_of("\n"));
        obj[i] = readXMLGiftObject(s);
        i++;
        content = content.substr(content.find_first_of("\n") + 1);
        if (content.empty())
            break;
    }
    obj[i] = nullptr;
    return obj;
}

Object **readXMLGift(const std::string &filename)
{
    std::ifstream f;
    Object **obj;

    f.open(filename, std::ifstream::in);
    if (!f.is_open() || !std::regex_search(filename, std::regex("\\.xml$"))) {
        std::cerr << "I can't find your gifts" << std::endl;
        return nullptr;
    }
    std::string content;
    std::getline(f, content, '\0');
    obj = readXMLGiftContent(content);
    f.close();
    return obj;
}

void testReadXMLGift()
{
    Object **obj = readXMLGift("test.xml");
    for (int i = 0; obj[i] != nullptr; i++) {
        while (obj[i] != nullptr && (obj[i]->getTitle() == "Box" || obj[i]->getTitle() == "GiftPaper")) {
            std::cout << obj[i]->getTitle() << "->";
            obj[i] = dynamic_cast<Wrap *>(obj[i])->openMe();
        }
        if (obj[i] != nullptr)
            std::cout << obj[i]->getTitle() << std::endl;
        else
            std::cout << std::endl;
    }
}
/*
** EPITECH PROJECT, 2020
** RType_2020
** File description:
** AScene
*/

#include "AScene.hpp"

AScene::AScene(page_t page)
{
    _pageName = page;
}

AScene::~AScene()
{
}

page_t AScene::getPage()
{
    return _pageName;
}
/*
** EPITECH PROJECT, 2020
** CPP_babel
** File description:
** UIHandler
*/

#include "UIHandler.hpp"

UIHandler::UIHandler(const std::string &ip, size_t port)
: c(ip, port)
, auth(*this, c)
, chat(*this, c)
, binPop(*this)
, callPop(*this, c.getAudio())
{
    auth.show();
}

UIHandler::~UIHandler()
{
}

void UIHandler::showChatPage()
{
    auth.hide();
    binPop.hide();
    callPop.hide();
    chat.loadFriends(c.getContactList());
    chat.show();
}

void UIHandler::showAuthPage()
{
    auth.show();
    chat.hide();
}

void UIHandler::showBinaryPopUp(const std::string &msg, const std::function<void()> &actionOk, const std::function<void()> &actionKo)
{
    binPop.preparePopUp(msg, actionOk, actionKo);
    binPop.show();
}

void UIHandler::showCallPopUp(const std::function<void()> &actionKo)
{
    callPop.preparePopUp(actionKo);
    callPop.show();
}
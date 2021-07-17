/*
** EPITECH PROJECT, 2020
** CPP_babel
** File description:
** UIHandler
*/

#pragma once

#include "authmenu.h"
#include "chatwidget.h"
#include "popupbinary.h"
#include "callpop.h"
#include "../Client/Client.hpp"

class UIHandler {
    public:
        UIHandler(const std::string &ip, size_t port);
        ~UIHandler();

        void showChatPage();
        void showAuthPage();
        void showBinaryPopUp(const std::string &msg, const std::function<void()> &actionOk, const std::function<void()> &actionKo=nullptr);
        void showCallPopUp(const std::function<void()> &actionEndCall);

    protected:
    private:
        Client c;
        AuthMenu auth;
        ChatWidget chat;
        PopupBinary binPop;
        CallPopUp callPop;
};

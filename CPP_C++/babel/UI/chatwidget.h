#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QMainWindow>
#include <QString>
#include <QMovie>
#include <QListWidget>
#include <ctime>

#include "styledialog.h"
#include "data_user/userdata.h"
#include "../Client/Client.hpp"

class UIHandler;

namespace Ui {
class ChatWidget;
}

class ChatWidget : public QMainWindow
{
    Q_OBJECT

public:

    explicit ChatWidget(UIHandler &handl, Client &client, QWidget *parent = 0);
    ~ChatWidget();

    void loadFriends(const std::vector<Contact> &friends);
    void receiveMessage(const std::string &message, size_t timestamp, bool isFriend, bool addEnd);
    void updatePersonalInfo();

public slots:
    void sendMessage();
    void disconnect();
    void onStyleChanged(QFont &font, QColor &color);
    void changeStatus(status_t status);
    void friendClicked(const Contact &_friend);
    void callFriend();
    void addFriend();
    void deleteFriend();

private:
    Ui::ChatWidget *ui;
    StyleDialog dlg;
    UserData style;

    UIHandler &handler;
    Client &client;

    const Contact *_contact;
};

#endif // CHATWIDGET_H
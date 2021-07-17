#ifndef AUTHMENU_H
#define AUTHMENU_H

#include <QMainWindow>
#include <QString>
#include <QMovie>

#include "../Client/Client.hpp"

class UIHandler;

namespace Ui {
class AuthMenu;
}

class AuthMenu : public QMainWindow
{
    Q_OBJECT

public:

    explicit AuthMenu(UIHandler &handl, Client &client, QWidget *parent = 0);
    ~AuthMenu();

    void setStatus(const QString &status);
    void changePage();

private slots:

    void tryToLogin();
    void tryToSignup();

private:
    Ui::AuthMenu *ui;
    
    UIHandler &handler;
    Client &client;
};

#endif // AUTHMENU_H

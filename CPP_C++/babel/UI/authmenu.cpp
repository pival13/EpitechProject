#include "authmenu.h"
#include "UIHandler.hpp"
#include "ui_authmenu.h"
#include "ui_chatwidget.h"
#include <QDebug>


AuthMenu::AuthMenu(UIHandler &handl, Client &_client, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AuthMenu)
    , handler(handl)
    , client(_client)
{
    ui->setupUi(this);

    ui->Login->setFont(QFont("Gadugi", 12));
    ui->Password->setEchoMode(QLineEdit::Password);
    ui->Username->setFont(QFont("Gadugi", 12));
    ui->Email->setFont(QFont("Gadugi", 12));
    ui->Passwordcreate->setEchoMode(QLineEdit::Password);
    ui->Passwordcreate_2->setEchoMode(QLineEdit::Password);
    QObject::connect(ui->SignButton, SIGNAL(clicked()), this, SLOT(tryToLogin()));
    QObject::connect(ui->SignupButton, SIGNAL(clicked()), this, SLOT(tryToSignup()));
}

AuthMenu::~AuthMenu()
{
    delete ui;
}

void AuthMenu::tryToLogin()
{
    ui->SignButton->setEnabled(false);
    ui->SignupButton->setEnabled(false);

    auto preloader = new QMovie("/Image/46.gif");
    preloader->start();
    ui->Status->setMovie(preloader);

    std::string mail = ui->Login->text().toUtf8().data();
    std::string pwd = ui->Password->text().toUtf8().data();
    client.login(mail, pwd, [this, &preloader](bool result) {
        ui->SignButton->setEnabled(true);
        ui->SignupButton->setEnabled(true);
    

        //preloader->stop();

        if (!result) {
            setStatus("Email / password incorrect.");
        } else {
            setStatus("");
            changePage();
            //page->setEnabled(true);
            //ui->setEnabled(false);
        }
    });
}

void AuthMenu::tryToSignup()
{
    ui->SignButton->setEnabled(false);
    ui->SignupButton->setEnabled(false);

    auto preloader = new QMovie("/Image/46.gif");
    preloader->start();
    ui->Status->setMovie(preloader);

    std::string username = ui->Username->text().toUtf8().data();
    std::string mail = ui->Email->text().toUtf8().data();
    std::string pwd = ui->Passwordcreate->text().toUtf8().data();
    std::string pwd2 = ui->Passwordcreate_2->text().toUtf8().data();

    if (mail.empty() || username.empty() || pwd.empty())
        setStatus("Fill all fields to create an account.");
    else if (pwd != pwd2)
        setStatus("Passwords are differents.");
    else {
        client.signUp(mail, pwd, username, [this, &preloader](bool result) {
            ui->SignButton->setEnabled(true);
            ui->SignupButton->setEnabled(true);

            //preloader->stop();

            if (!result) {
                setStatus("Email already exist.");
            } else {
                setStatus("");
                changePage();
                //page->setEnabled(true);
                //ui->setEnabled(false);
            }
        });
    }
}

void
AuthMenu::setStatus(const QString &status)
{
    ui->Status->setText(status);
    ui->SignButton->setEnabled(true);
    ui->SignupButton->setEnabled(true);
    ui->Login->setEnabled(true);
    ui->Password->setEnabled(true);
}

void AuthMenu::changePage()
{
    handler.showChatPage();
}
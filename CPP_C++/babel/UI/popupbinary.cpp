
#include "popupbinary.h"
#include "UIHandler.hpp"
#include "ui_popupbinary.h"

PopupBinary::PopupBinary(UIHandler &handl, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PopupBinary)
    , handler(handl)
{
    ui->setupUi(this);

    QObject::connect(ui->AcceptButton, &QPushButton::clicked, this, [this]() {
        if (_actionOk) _actionOk();
        hide();
    });
    QObject::connect(ui->RefuseButton, &QPushButton::clicked, this, [this]() {
        if (_actionKo) _actionKo();
        hide();
    });
}

PopupBinary::~PopupBinary()
{
    delete ui;
}

void PopupBinary::preparePopUp(const std::string &msg, const std::function<void()> &actionOk, const std::function<void()> &actionKo)
{
    ui->MessageLabel->setText(QString(msg.data()));
    _actionOk = actionOk;
    _actionKo = actionKo;
}

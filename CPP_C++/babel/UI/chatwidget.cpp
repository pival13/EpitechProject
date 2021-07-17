
#include "chatwidget.h"
#include "UIHandler.hpp"
#include "ui_chatwidget.h"
#include <QDebug>


ChatWidget::ChatWidget(UIHandler &handl, Client &_client, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ChatWidget)
    , handler(handl)
    , client(_client)
    , _contact(nullptr)
{
    client.setAudioCallback([this](const std::string &mail) {
        handler.showBinaryPopUp(mail + "\nwant to call you.\nDo you want to accept the call?", [this]() {
            client.acceptCall();
            if (_contact) {
                ui->CallButton->setText("Invite");
                ui->CallButton->setEnabled(_contact->getStatus() == ONLINE);
            }
            handler.showCallPopUp([this]() { client.endCurrentCall(); ui->CallButton->setText("Call"); });
        }, [this]() {
            client.refuseCall();
        });
    });
    client.setFriendListUpdateCallback([this](const std::vector<Contact> &c) { loadFriends(c); });

    ui->setupUi(this);

    ui->MessageLine->setFont(QFont("Gadugi", 12));
    ui->MessageLine->setReadOnly(true);
    QObject::connect(ui->actionStyle, SIGNAL(triggered(bool)), &dlg, SLOT(open()));
    QObject::connect(&dlg, SIGNAL(styleChanged(QFont &, QColor &)), this, SLOT(onStyleChanged(QFont &, QColor &)));
    QObject::connect(ui->SendButton, SIGNAL(clicked()), this, SLOT(sendMessage()));
    QObject::connect(ui->actionDisconnect_2, &QAction::triggered, this, [this]() { handler.showBinaryPopUp("Are you sure you want to logout?", [this]() {disconnect();}); });
    QObject::connect(ui->actionOnline, &QAction::triggered, this, [this]() {changeStatus(ONLINE);});
    QObject::connect(ui->actionDo_Not_Disturb, &QAction::triggered, this, [this]() {changeStatus(NODISTURB);});
    QObject::connect(ui->actionOffline, &QAction::triggered, this, [this]() {changeStatus(OFFLINE);});
    QObject::connect(ui->Users, &QAbstractItemView::clicked, this, [this](const QModelIndex &index) { this->friendClicked(client.getContactList()[index.row()+1]);});
    QObject::connect(ui->CallButton, SIGNAL(clicked()), this, SLOT(callFriend()));
    QObject::connect(ui->AddFriendButton, SIGNAL(clicked()), this, SLOT(addFriend()));
    QObject::connect(ui->DeleteFriend, SIGNAL(clicked()), this, SLOT(deleteFriend()));
}

ChatWidget::~ChatWidget()
{
    client.setFriendListUpdateCallback(nullptr);
    client.setAudioCallback(nullptr);
    client.endCurrentCall();
    delete ui;
}

void ChatWidget::loadFriends(const std::vector<Contact> &friends)
{
    ui->Users->clear();
    for (const Contact &c : friends) {
        if (c.getMail() == client.getClientMail())
            continue;

        auto item = new QListWidgetItem;
        item->setForeground(QBrush(QColor(c.getStatus() == OFFLINE ? "Grey" : (c.getStatus() == ONLINE ? "Green" : "Red"))));
        item->setFont(QFont("Gadugi", 12));
        item->setText(QString(c.getUsername().data()));
        item->setFlags(item->flags() & ~Qt::ItemIsSelectable);
        ui->Users->addItem(item);
    }
    ui->CallButton->setEnabled(_contact != nullptr && _contact->getStatus() == ONLINE);
    updatePersonalInfo();
}

void ChatWidget::friendClicked(const Contact &_friend)
{
    ui->Dialog_2->clear();
    ui->MessageLine->setReadOnly(false);
    ui->MessageLine->clear();

    _contact = &_friend;
    ui->CallButton->setText(client.getCallList().empty() ? "Call" : "Invite");
    ui->CallButton->setEnabled(_contact->getStatus() == ONLINE);
    updatePersonalInfo();
    client.getContactMessage(_contact->getMail(), 25, [this](const std::list<Message> &msg) {
        for (const Message &m : msg)
            receiveMessage(m.getMessage(), m.getTime(), m.getReceiver() == _contact->getMail(), false);
    }, [this](const std::string &emitter, const std::string &message, size_t timestamp) {
        if (emitter == _contact->getMail())
            receiveMessage(message, timestamp, true, true);
    });
}

void ChatWidget::receiveMessage(const std::string &message, size_t timestamp, bool isFriend, bool addEnd)
{
    auto item = new QListWidgetItem;
    item->setForeground(QBrush(style.getColor()));
    //item->setTextColor(style.getColor());
    item->setFont(style.getFont());
    char time[21] = {0};
    tm *_tm = std::localtime((time_t*)&timestamp);
    std::strftime(time, 21, "%Y-%m-%d %H:%M:%S", _tm);
    item->setText(QString(time) + ":\n" + QString(message.data()));
    item->setTextAlignment(isFriend ? Qt::AlignLeft : Qt::AlignRight);

    // Disable selecting message in dialog
    item->setFlags(item->flags() & ~Qt::ItemIsSelectable);
    if (addEnd)
        ui->Dialog_2->addItem(item);
    else
        ui->Dialog_2->insertItem(0, item);
}

void ChatWidget::sendMessage()
{
    std::string msg = ui->MessageLine->toPlainText().toUtf8().data();

    if (msg.empty() || _contact == nullptr)
        return;

    client.addMessage(_contact->getMail(), msg, std::time(0), [this, msg](bool result) {
        if (result)
            receiveMessage(msg, std::time(0), false, true);
        else {
            for (const Message &m : _contact->getMessageList())
                receiveMessage(m.getMessage(), m.getTime(), m.getSender() == _contact->getMail(), false);
        }
    });
    ui->MessageLine->clear();
}

void ChatWidget::callFriend()
{
    if (_contact->getStatus() != ONLINE)
        return;
    client.startCall(_contact->getMail(), [this](bool result) {
        if (result)
            handler.showCallPopUp([this]() { client.endCurrentCall(); ui->CallButton->setText("Invite"); });
    });
}

void ChatWidget::addFriend()
{
    std::string people = ui->AddFriendText->toPlainText().toUtf8().data();

    if (people.empty())
        return;

    client.addFriend(people, [this](bool success) {
        if (success)
            loadFriends(client.getContactList());
    });
    ui->AddFriendText->clear();
}

void ChatWidget::deleteFriend()
{
    if (!_contact)
        return;
    client.deleteFriend(_contact->getMail(), [this](bool result) {
        if (!result) return;
        ui->Dialog_2->clear();
        ui->MessageLine->setReadOnly(true);
        ui->MessageLine->clear();
        loadFriends(client.getContactList());
    });
}

void ChatWidget::disconnect()
{
    client.endCurrentCall();
    ui->Dialog_2->clear();
    ui->MessageLine->clear();
    ui->MessageLine->setReadOnly(true);

    client.setFriendListUpdateCallback(nullptr);
    client.setAudioCallback(nullptr);

    client.disconnect();
    handler.showAuthPage();
}

void ChatWidget::changeStatus(status_t status)
{
    client.changeStatus(status);
}

void ChatWidget::updatePersonalInfo()
{
    auto status = client.getContactList()[0];
    ui->UsersStatus->setStyleSheet("QLabel { color : "+QString(status.getStatus() == OFFLINE ? "Grey" : (status.getStatus() == ONLINE ? "Green" : "Red"))+"; }");
    ui->UsersStatus->setText(QString(status.getUsername().data()) + " (" + QString(status.getMail().data()) + ")");
    
    if (_contact) {
        ui->label_2->setStyleSheet("QLabel { color : "+QString(_contact->getStatus() == OFFLINE ? "Grey" : (_contact->getStatus() == ONLINE ? "Green" : "Red"))+"; }");
        ui->label_2->setText(QString(_contact->getUsername().data()) + " (" + QString(_contact->getMail().data()) + ")");
    } else {
        ui->label_2->setStyleSheet("QLabel { color : Grey; }");
        ui->label_2->setText("");
    }
}

void ChatWidget::onStyleChanged(QFont &font, QColor &color)
{
    style.setFont(font);
    style.setColor(color);
}
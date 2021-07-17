/*
** EPITECH PROJECT, 2020
** Client
** File description:
** Client
*/

#include "Client.hpp"

Client::Client(const std::string & ip, size_t port)
    : UDPsocket ( 0 )
    , TCPsocket ( 0, ip, port )
{
    TCPsocket.receiveDataCallback([this](const std::vector<uint8_t> &data, const std::string &, size_t) {
        this->organizeData(data);
    });

    readed = 0;

    audio.sendAudioCallback([this](const std::vector<uint8_t> &data) {
        for (const auto &p : callList)
            getUDPSocket().sendData(data, p.first, p.second);

    });
    UDPsocket.receiveDataCallback([this](const std::vector<uint8_t> &data, const std::string &ip, size_t port) {
        audio.receiveAudio(data, ip + ':' + std::to_string(port));
    });
}

Client::~Client()
{
    audio.sendAudioCallback(nullptr);
    UDPsocket.receiveDataCallback(nullptr);
}

void Client::deleteFriendList(const std::string & mail)
{
    for (int i = 0; i < contactList.size(); ++i)
        if (contactList[i].getMail() == mail) {
            contactList.erase(contactList.begin() + i);
            return;
        }
}

bool Client::checkContactAlreadyExist(const std::string & mail)
{
    for (int i = 0; i < contactList.size(); ++i)
        if (contactList[i].getMail() == mail)
            return true;
    return false;
}

Contact & Client::getContactDependingOnMail(const std::string & mail)
{
    for (int i = 0; i < contactList.size(); ++i) {
        if (contactList[i].getMail() == mail)
            return contactList[i];
    }
    return contactList.front();
}

void Client::addMessageToPendingList(const std::string & mail, const std::string & message, unsigned long time)
{
    Message m(mail, std::string(email_adr), message, time);
    Contact &c = getContactDependingOnMail(mail);
    if (c.getMail().empty())
        return;
    c.getPendingMessage().emplace_back(m);
}

void Client::addMessageToMessageListFront(const std::string & sender, const std::string & receiver, const std::string & message, unsigned long time)
{
    Message m(sender, receiver, message, time);
    Contact &c = getContactDependingOnMail(email_adr);
    if (!(receiver == email_adr))
        c = getContactDependingOnMail(receiver);
    else
        c = getContactDependingOnMail(sender);
    if (c.getMail().empty())
        return;
    c.getMessageList().emplace_front(m);
    if (c.getMessageList().size() == 26)
        c.getMessageList().pop_back();
}

void Client::addMessageToMessageListBack(const std::string & sender, const std::string & receiver, const std::string & message, unsigned long time)
{
    Message m(sender, receiver, message, time);
    Contact &c = getContactDependingOnMail(receiver == email_adr ? sender : receiver);
    if (c.getMail().empty())
        return;
    c.getMessageList().emplace_back(m);
}

void Client::addMessage(const std::string & mail, const std::string & message, unsigned long time, const std::function<void(bool)> &callback)
{
    message_t m;
    std::string rn("\r\n");

    if (this->email_adr.empty())
        return;

    _callbacks["addMessage"] = callback;

    m.header.func = MESSAGE;
    m.header.size = sizeof(message_t) - sizeof(header_t);

    std::memset(&m.mail, 0, LOGIN_LENGTH);
    std::memset(&m.message, 0, MESSAGE_LENGTH);
    m.timestamp = time;

    std::memcpy(&m.mail, mail.c_str(), mail.size());
    std::memcpy(&m.message, message.c_str(), message.size());

    addMessageToPendingList(mail, message, time);

    TCPsocket.sendData(std::vector<uint8_t> ((char *)&m, (char *)&m + sizeof(m)), name, 4242);
    TCPsocket.sendData(std::vector<uint8_t> (rn.c_str(), rn.c_str() + rn.size()), name, 4242);
}

void Client::addFriend(const std::string & mail, const std::function<void(bool)> &callback)
{
    add_friend_t a;
    std::string rn("\r\n");

    if (checkContactAlreadyExist(mail))
        return;
    
    _callbacks["addFriend"] = callback;

    a.header.func = ADD_FRIEND;
    a.header.size = sizeof(add_friend_t) - sizeof(header_t);

    std::memset(&a.mail, 0, LOGIN_LENGTH);
    std::memcpy(&a.mail, mail.c_str(), LOGIN_LENGTH);

    TCPsocket.sendData(std::vector<uint8_t> ((char *)&a, (char *)&a + sizeof(a)), name, 4242);
    TCPsocket.sendData(std::vector<uint8_t> (rn.c_str(), rn.c_str() + rn.size()), name, 4242);
}

void Client::deleteFriend(const std::string & mail, const std::function<void(bool)> &callback)
{
    delete_friend_t d;
    std::string rn("\r\n");

    _callbacks["deleteFriend"] = callback;

    d.header.func = DELETE_FRIEND;
    d.header.size = sizeof(delete_friend_t) - sizeof(header_t);

    std::memset(&d.mail, 0, LOGIN_LENGTH);
    std::memcpy(&d.mail, mail.c_str(), LOGIN_LENGTH);

    TCPsocket.sendData(std::vector<uint8_t> ((char *)&d, (char *)&d + sizeof(d)), name, 4242);
    TCPsocket.sendData(std::vector<uint8_t> (rn.c_str(), rn.c_str() + rn.size()), name, 4242);
}

void Client::addFriendList(get_contact_t & contact)
{
    if (contact.mail[0] == '\0')
        return;
    Contact c(std::string(contact.mail), std::string(contact.username), contact.status);
    contactList.emplace_back(c);
}

void Client::signUp(std::string mail, const std::string & pwd, std::string username, const std::function<void(bool)> &callback)
{
    header_t h;
    signup_t s;
    std::string rn("\r\n");

    _callbacks["signUp"] = callback;

    h.func = SIGN_UP;
    h.size = sizeof(signup_t) - sizeof(header_t);
    s.header = h;

    std::memset(&s.mail, 0, LOGIN_LENGTH);
    std::memcpy(&s.mail, mail.c_str(), mail.size());
    std::memset(&s.password, 0, LOGIN_LENGTH);
    std::memcpy(&s.password, pwd.c_str(), pwd.size());
    std::memset(&s.username, 0, LOGIN_LENGTH);
    std::memcpy(&s.username, username.c_str(), username.size());
    s.port = UDPsocket.getUdpPort();

    TCPsocket.sendData(std::vector<uint8_t> ((char *)&s, (char *)&s + sizeof(s)), name, 4242);
    TCPsocket.sendData(std::vector<uint8_t> (rn.c_str(), rn.c_str() + rn.size()), name, 4242);
}

void Client::login(const std::string & mail, const std::string & pwd, const std::function<void(bool)> &callback)
{
    header_t h;
    login_t l;
    std::string rn("\r\n");

    _callbacks["login"] = callback;

    h.func = LOGIN;
    h.size = sizeof(login_t) - sizeof(header_t);
    l.header = h;

    std::memset(&l.mail, 0, LOGIN_LENGTH);
    std::memcpy(&l.mail, mail.c_str(), mail.size());
    std::memset(&l.password, 0, LOGIN_LENGTH);
    std::memcpy(&l.password, pwd.c_str(), pwd.size());
    l.port = UDPsocket.getUdpPort();

    std::vector<uint8_t> a ((char *)&l, (char *)&l + sizeof(l));

    TCPsocket.sendData(std::vector<uint8_t> ((char *)&l, (char *)&l + sizeof(l)), name, 4242);
    TCPsocket.sendData(std::vector<uint8_t> (rn.c_str(), rn.c_str() + rn.size()), name, 4242);
}

void Client::loadingContactFinished()
{
    std::cout << "encule" << std::endl;
    if (this->contactList.empty())
        return;
    Contact c = contactList.front();
    email_adr = c.getMail();
    name = c.getUsername();
    std::cout << "Bonjourno" << std::endl;

    if (_callbacks.count("login")) {
        _callbacks["login"](true);
        std::cout << "login" << std::endl;
        _callbacks.erase(_callbacks.find("login"));
    }
    else if (_callbacks.count("signUp")){
        std::cout << "signUp" << std::endl;
        _callbacks["signUp"](true);
        _callbacks.erase(_callbacks.find("signUp"));
    } else {
        if (_callbacks.count("addFriend")) {
            std::cout << "addFriend" << std::endl;
            _callbacks["addFriend"](true);
            _callbacks.erase(_callbacks.find("addFriend"));
        }
    }
}

void Client::receiveContact(char *buffer)
{
    get_contact_t g;
    std::memset(&g, 0, sizeof(get_contact_t));

    g.header.func = GET_CONTACT;
    g.header.size = sizeof(get_contact_t) - sizeof(header_t);

    std::memcpy(&g.mail, buffer + sizeof(g.header), LOGIN_LENGTH);
    std::memcpy(&g.username, buffer + sizeof(g.header) + LOGIN_LENGTH, LOGIN_LENGTH);
    std::memcpy(&g.status, buffer + sizeof(g.header) + LOGIN_LENGTH + LOGIN_LENGTH, sizeof(status_t));

    addFriendList(g);
    std::cout << "Sender : " << g.mail << std::endl;
    readed -= sizeof(get_contact_t);
    if (g.mail[0] == '\0')
        return loadingContactFinished();
}

void Client::disconnect()
{
    header_t d;
    std::string rn("\r\n");

    if (email_adr.empty())
        return;

    d.func = DISCONNECT;  
    d.size = 0;

    _data.clear();
    contactList.clear();
    email_adr.clear();
    name.clear();
    _callbackUpdateMessage = nullptr;
    _callbacks.clear();
    
    TCPsocket.sendData(std::vector<uint8_t> ((char *)&d, (char *)&d + sizeof(d)), name, 4242);
    TCPsocket.sendData(std::vector<uint8_t> (rn.c_str(), rn.c_str() + rn.size()), name, 4242);
}

void Client::changeStatus(status_t status)
{
    new_status_t t;
    std::string rn("\r\n");
    std::memset(&t, 0, sizeof(new_status_t));

    t.header.func = NEW_STATUS;
    t.header.size = sizeof(new_status_t) - sizeof(header_t);

    t.status = status;
    if (!email_adr.empty())
        getContactDependingOnMail(email_adr).setStatus(status);
    if (signalUpdateFriendList)
        signalUpdateFriendList(contactList);

    TCPsocket.sendData(std::vector<uint8_t> ((char *)&t, (char *)&t + sizeof(t)), name, 4242);
    TCPsocket.sendData(std::vector<uint8_t> (rn.c_str(), rn.c_str() + rn.size()), name, 4242);
}

void Client::loginError()
{
    readed -= sizeof(header_t);
    
    if (_callbacks.count("login")) {
        _callbacks["login"](false);
        _callbacks.erase(_callbacks.find("login"));
    }
}

void Client::signupError()
{
    readed -= sizeof(header_t);

    if (_callbacks.count("signUp")) {
        _callbacks["signUp"](false);
        _callbacks.erase(_callbacks.find("signUp"));
    }
}

void Client::updateStatus(const std::string & mail, status_t stat)
{
    for (int i = 0; i < contactList.size(); ++i)
        if (contactList[i].getMail() == mail) {
            contactList[i].setStatus(stat);
            return;
        }
}

void Client::getChangedStatus(char *buffer)
{
    status_changed_t s;
    std::memset(&s, 0, sizeof(status_changed_t));

    s.header.func = STATUS_CHANGED;
    s.header.size = sizeof(status_changed_t) - sizeof(header_t);

    std::memcpy(&s.mail, buffer + sizeof(s.header), LOGIN_LENGTH);
    std::memcpy(&s.status, buffer + sizeof(s.header) + LOGIN_LENGTH, sizeof(status_t));

    updateStatus(s.mail, s.status);

    if (signalUpdateFriendList)
        signalUpdateFriendList(contactList);
    readed -= sizeof(status_changed_t);
}

void Client::addFriendError(char *buffer)
{
    add_friend_t a;
    std::memset(&a, 0, sizeof(add_friend_t));
    
    a.header.func = ADD_FRIEND_ERROR;
    a.header.size = sizeof(add_friend_t) - sizeof(header_t);

    std::memcpy(&a.mail, buffer + sizeof(header_t), LOGIN_LENGTH);

    readed -= sizeof(add_friend_t);

    if (_callbacks.count("addFriend")) {
        _callbacks["addFriend"](false);
        _callbacks.erase(_callbacks.find("addFriend"));
    }
}

void Client::messageFailed(char *buffer)
{
    mail_t m;
    std::memset(&m, 0, sizeof(mail_t));

    m.header.func = MESSAGE_FAILED;
    m.header.size = sizeof(mail_t) - sizeof(header_t);

    std::memcpy(&m.mail, buffer + sizeof(header_t), LOGIN_LENGTH);

    Contact &c = getContactDependingOnMail(m.mail);
    if (c.getMail().empty()) {
        readed -= sizeof(mail_t);
        return;
    }
    c.getPendingMessage().pop_front();    
    readed -= sizeof(mail_t);
    if (_callbacks.count("addMessage")) {
        _callbacks["addMessage"](false);
        _callbacks.erase(_callbacks.find("addMessage"));
    }
}

void Client::messageSucces(char *buffer)
{
    mail_t m;
    std::memset(&m, 0, sizeof(mail_t));

    m.header.func = MESSAGE_FAILED;
    m.header.size = sizeof(mail_t) - sizeof(header_t);

    std::memcpy(&m.mail, buffer + sizeof(header_t), LOGIN_LENGTH);
    Contact &c = getContactDependingOnMail(m.mail);
    if (c.getMail().empty()) {
        readed -= sizeof(mail_t);
        return;
    }
    Message message = c.getPendingMessage().front();
    c.getPendingMessage().pop_front();
    c.getMessageList().emplace_front(message);
    if (c.getMessageList().size() == 26)
        c.getMessageList().pop_back();
    readed -= sizeof(mail_t);

    if (_callbacks.count("addMessage")) {
        _callbacks["addMessage"](true);
        _callbacks.erase(_callbacks.find("addMessage"));
    }
}

void Client::receiveMessage(char *buffer)
{
    message_t m;
    std::memset(&m, 0, sizeof(message_t));

    m.header.func = MESSAGE;
    m.header.size = sizeof(message_t) - sizeof(header_t);

    std::memcpy(&m.mail, buffer + sizeof(header_t), LOGIN_LENGTH);
    std::memcpy(&m.message, buffer + sizeof(header_t) + LOGIN_LENGTH, MESSAGE_LENGTH);
    std::memcpy(&m.timestamp, buffer + sizeof(header_t) + LOGIN_LENGTH + MESSAGE_LENGTH, sizeof(int));

    addMessageToMessageListFront(m.mail, email_adr, m.message, m.timestamp);

    if (_callbackUpdateMessage)
        _callbackUpdateMessage(m.mail, m.message, m.timestamp);

    readed -= sizeof(message_t);
}

void Client::finishedLoadingAllContactMessage()
{
    if (listUpdateCallback)
        listUpdateCallback(getContactDependingOnMail(friendClicked).getMessageList());
}

void Client::getAllContactMessage(char *buffer)
{
    get_contact_message_answer_t g;
    std::memset(&g, 0, sizeof(get_contact_message_answer_t));

    g.header.func = GET_CONTACT_MESSAGE_ANSWER;
    g.header.size = sizeof(get_contact_message_answer_t) - sizeof(header_t);

    std::memcpy(&g.receiver, buffer + sizeof(header_t) + LOGIN_LENGTH, LOGIN_LENGTH);
    std::memcpy(&g.sender, buffer + sizeof(header_t), LOGIN_LENGTH);
    std::memcpy(&g.message, buffer + sizeof(header_t) + (2 * LOGIN_LENGTH), MESSAGE_LENGTH);
    std::memcpy(&g.timestamp, buffer + sizeof(header_t) + (2 * LOGIN_LENGTH) + MESSAGE_LENGTH, sizeof(unsigned long));

    readed -= sizeof(get_contact_message_answer_t);

    if (g.sender[0] == '\0')
        return finishedLoadingAllContactMessage();
    addMessageToMessageListBack(g.sender, g.receiver, g.message, g.timestamp);
}


void Client::getContactMessage(const std::string & mail, int wanted, const std::function<void(const std::list<Message> &)> &callback, const std::function<void(const std::string &, const std::string &, unsigned long)> &callbackUpdate)
{
    get_contact_message_t g;
    std::string rn("\r\n");

    listUpdateCallback = callback;
    _callbackUpdateMessage = callbackUpdate;
    friendClicked = mail;

    g.header.func = GET_CONTACT_MESSAGE;
    g.header.size = sizeof(get_contact_message_t) - sizeof(header_t);

    g.number = wanted;
    std::memset(&g.mail, 0, LOGIN_LENGTH);
    std::memcpy(&g.mail, mail.c_str(), mail.size());

    getContactDependingOnMail(mail).getMessageList().clear();

    TCPsocket.sendData(std::vector<uint8_t> ((char *)&g, (char *)&g + sizeof(g)), name, 4242);
    TCPsocket.sendData(std::vector<uint8_t> (rn.c_str(), rn.c_str() + rn.size()), name, 4242);    
}

void Client::deleteFriendError(char *buffer)
{
    delete_friend_t d;
    std::memset(&d, 0, sizeof(delete_friend_t));

    d.header.func = DELETE_FRIEND_ERROR;
    d.header.size = sizeof(delete_friend_t) - sizeof(header_t);

    std::memcpy(&d.mail, buffer + sizeof(header_t), LOGIN_LENGTH);

    readed -= sizeof(delete_friend_t);
    if (_callbacks.count("deleteFriend")) {
        _callbacks["deleteFriend"](false);
        _callbacks.erase(_callbacks.find("deleteFriend"));
    }
    std::cout << "delete friend error for : " << d.mail << std::endl;
}

void Client::deleteFriendSuccess(char *buffer)
{
    delete_friend_t d;
    std::memset(&d, 0, sizeof(delete_friend_t));

    d.header.func = DELETE_FRIEND_ERROR;
    d.header.size = sizeof(delete_friend_t) - sizeof(header_t);

    std::memcpy(&d.mail, buffer + sizeof(header_t), LOGIN_LENGTH);

    deleteFriendList(d.mail);

    readed -= sizeof(delete_friend_t);

    if (_callbacks.count("deleteFriend")) {
        _callbacks["deleteFriend"](true);
        _callbacks.erase(_callbacks.find("deleteFriend"));
    }
    std::cout << "delete friend success for : " << d.mail << std::endl;
}

void Client::refuseCall()
{
    mail_t h;
    std::string rn("\r\n");

    h.header.func = REFUSE_CALL;
    h.header.size = sizeof(mail_t) - sizeof(header_t);
    std::memset(&h.mail, 0, LOGIN_LENGTH);
    std::memcpy(&h.mail, email_calling.c_str(), email_calling.size());

    TCPsocket.sendData(std::vector<uint8_t> ((char *)&h, (char *)&h + sizeof(h)), name, 4242);
    TCPsocket.sendData(std::vector<uint8_t> (rn.c_str(), rn.c_str() + rn.size()), name, 4242);  
}

void Client::acceptCall()
{
    mail_t h;
    std::string rn("\r\n");

    h.header.func = ACCEPT_CALL;
    h.header.size = sizeof(mail_t) - sizeof(header_t);
    std::memset(&h.mail, 0, LOGIN_LENGTH);
    std::memcpy(&h.mail, email_calling.c_str(), email_calling.size());

    stat = contactList[0].getStatus();
    changeStatus(NODISTURB);

    TCPsocket.sendData(std::vector<uint8_t> ((char *)&h, (char *)&h + sizeof(h)), name, 4242);
    TCPsocket.sendData(std::vector<uint8_t> (rn.c_str(), rn.c_str() + rn.size()), name, 4242); 
}

void Client::eraseParticipantFromCall(const std::string & ip)
{
    for (auto it = callList.begin(); it != callList.end(); ++it)
        if (it->first == ip) {
            callList.erase(it);
            return;
        }
}

void Client::someoneLeftCall(char *buffer)
{
    left_call_t l;

    l.header.func = LEFT_CALL;
    l.header.size = sizeof(left_call_t) - sizeof(header_t);

    std::memset(&l.ip, 0, IP_LENGTH);
    std::memcpy(&l.ip, buffer + sizeof(header_t), IP_LENGTH);

    eraseParticipantFromCall(l.ip);

    readed -= sizeof(left_call_t);
}

void Client::endCurrentCall()
{
    header_t h;
    std::string rn("\r\n");

    h.func = END_CALL;
    h.size = 0;

    changeStatus(stat);
    callList.clear();

    TCPsocket.sendData(std::vector<uint8_t> ((char *)&h, (char *)&h + sizeof(h)), name, 4242);
    TCPsocket.sendData(std::vector<uint8_t> (rn.c_str(), rn.c_str() + rn.size()), name, 4242); 
}

void Client::startCall(const std::string & mail, const std::function<void(bool)> &callback)
{
    call_t c;
    std::string rn("\r\n");

    c.header.func = CALL;
    c.header.size = sizeof(call_t) - sizeof(header_t);

    memset(&c.mail, 0, LOGIN_LENGTH);
    memcpy(&c.mail, mail.c_str(), mail.size());

    stat = contactList[0].getStatus();
    changeStatus(status_t::NODISTURB);
    _callbacks["startCall"] = callback;

    TCPsocket.sendData(std::vector<uint8_t> ((char *)&c, (char *)&c + sizeof(c)), name, 4242);
    TCPsocket.sendData(std::vector<uint8_t> (rn.c_str(), rn.c_str() + rn.size()), name, 4242); 
}

void Client::connectToAnotherClient(char *buffer)
{
    call_answer_t c;
    c.header.func = JOIN_CALL;
    c.header.size = sizeof(call_answer_t) - sizeof(header_t);

    std::memset(&c.ip, 0, IP_LENGTH);
    std::memcpy(&c.ip, buffer + sizeof(header_t), IP_LENGTH);
    std::memcpy(&c.port, buffer + sizeof(header_t) + IP_LENGTH, sizeof(short));
    
    callList.emplace_back(std::pair<std::string, short>(c.ip, c.port));

    std::cout << "IP : " << c.ip << " port : " << c.port << std::endl;

    readed -= sizeof(call_answer_t);
}

void Client::getCall(char *buffer)
{
    got_call_t g;

    g.header.func = GOT_CALL;
    g.header.size = sizeof(got_call_t) - sizeof(header_t);
    
    std::memset(&g.mail, 0, LOGIN_LENGTH);
    std::memset(&g.ip, 0, IP_LENGTH);
    std::memcpy(&g.mail, buffer + sizeof(header_t), LOGIN_LENGTH);
    std::memcpy(&g.ip, buffer + sizeof(header_t) + LOGIN_LENGTH, IP_LENGTH);
    std::memcpy(&g.port, buffer + sizeof(header_t) + LOGIN_LENGTH + IP_LENGTH, sizeof(short));

    email_calling = g.mail;

    if (gotCallCallback)
        gotCallCallback(g.mail);

    readed -= sizeof(got_call_t);
}

void Client::gotCallRefuse(char *buffer)
{
    if (_callbacks.count("startCall")) {
        _callbacks["startCall"](false);
        _callbacks.erase(_callbacks.find("startCall"));
    }
    readed -= sizeof(header_t);
}

void Client::callSuccess(char *buffer)
{
    header_t c;
    c.func = ACCEPT_CALL;
    c.size = 0;

    if (_callbacks.count("startCall")) {
        _callbacks["startCall"](true);
        _callbacks.erase(_callbacks.find("startCall"));
    }
    readed -= sizeof(header_t);
}

void Client::setAudioCallback(const std::function<void(const std::string & mail)> &callback)
{
    gotCallCallback = callback;
}

void Client::setFriendListUpdateCallback(const std::function<void(const std::vector<Contact> &)> & callback)
{
    signalUpdateFriendList = callback;
}

void Client::organizeData(std::vector<uint8_t> data)
{
    header_t h;

    readed += data.size();
    _data.insert(_data.end(), data.begin(), data.end());

    std::cout << readed << std::endl;

    while (readed > 0) {        
        std::memset(&h, 0, sizeof(header_t));
        std::memcpy(&h, _data.data(), sizeof(header_t));
        if (h.size > readed)
            return;
        std::cout << "je suis func " << h.func << std::endl;
        switch (h.func) {
            case GET_CONTACT:
                receiveContact((char *)_data.data());
                break;
            case LOGIN_ERROR:
                loginError();
                break;
            case SIGN_UP_ERROR:
                signupError();
                break;
            case ADD_FRIEND_ERROR:
                addFriendError((char *)_data.data());
                break;
            case STATUS_CHANGED:
                getChangedStatus((char *)_data.data());
                break;
            case MESSAGE_FAILED:
                messageFailed((char *)_data.data());
                break;
            case MESSAGE_SUCCESS:
                messageSucces((char *)_data.data());
                break;
            case MESSAGE:
                receiveMessage((char *)_data.data());
                break;
            case GET_CONTACT_MESSAGE_ANSWER:
                getAllContactMessage((char *)_data.data());
                break;
            case DELETE_FRIEND_ERROR:
                deleteFriendError((char *)_data.data());
                break;
            case DELETE_FRIEND_SUCCESS:
                deleteFriendSuccess((char *)_data.data());
                break;
            case GOT_CALL:
                getCall((char *)_data.data());
                break;
            case ACCEPT_CALL:
                callSuccess((char *)_data.data());
                break;
            case LEFT_CALL:
                someoneLeftCall((char *)_data.data());
                break;
            case JOIN_CALL:
                connectToAnotherClient((char *)_data.data());
                break;
            case REFUSE_CALL:
                gotCallRefuse((char *)_data.data());
                break;
            default:
                std::cout << "problème dans le switch" << std::endl;
                return;
        }
        _data = std::vector<uint8_t>(_data.begin() + h.size + sizeof(header_t), _data.end());
    }
}
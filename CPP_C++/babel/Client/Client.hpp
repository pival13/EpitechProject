/*
** EPITECH PROJECT, 2020
** Client
** File description:
** Client
*/

#pragma once

//Basic includes
#include <string>
#include <list>
#include <ctime>

//Project includes
#include "TCPConnection.hpp"
#include "UDPConnection.hpp"
#include "Contact.hpp"

class Client {
    public:
        Client(const std::string & ip, size_t port);
        ~Client();

        //UI
        void signUp(std::string mail, const std::string & password, std::string username, const std::function<void(bool)> &callback);
        void login(const std::string & mail, const std::string & password, const std::function<void(bool)> &callback);
        void addFriend(const std::string & mail, const std::function<void(bool)> &callback);
        void deleteFriend(const std::string & mail, const std::function<void(bool)> &callback);
        void addMessage(const std::string & mail, const std::string & message, unsigned long time, const std::function<void(bool)> &callback);
        void refuseCall();
        void acceptCall();
        void endCurrentCall();
        void updateStatus(const std::string & mail, status_t stat);
        void startCall(const std::string & mail, const std::function<void(bool)> &callback);
        void disconnect();
        void getContactMessage(const std::string & mail, int wanted, const std::function<void(const std::list<Message> &)> &callback, const std::function<void(const std::string &, const std::string &, unsigned long)> &callbackUpdate);

        //ping UI
        void loadingContactFinished();
        void finishedLoadingAllContactMessage();

        //read from server
        void loginError();
        void signupError();
        void getChangedStatus(char *data);
        void receiveContact(char *buffer);
        void getCall(char *buffer);
        void gotCallRefuse(char *buffer);
        void callSuccess(char *buffer);
        void deleteFriendError(char *buffer);
        void addFriendError(char *buffer);
        void messageSucces(char *buffer);
        void receiveMessage(char *buffer);
        void getAllContactMessage(char *buffer);
        void deleteFriendSuccess(char *buffer);
        void messageFailed(char *buffer);
        void someoneLeftCall(char *buffer);
        void connectToAnotherClient(char *buffer);
        void organizeData(std::vector<uint8_t> buffer);

        //get
        UDPConnection & getUDPSocket() {return UDPsocket;};
        TCPConnection & getTCPSocket() {return TCPsocket;};
        Contact & getContactDependingOnMail(const std::string & mail);
        const std::string & getClientMail() {return email_adr;};
        const std::string & getClientName() {return name;}; 
        const std::vector<Contact> & getContactList () {return contactList;};
        Babel::Audio & getAudio() {return audio;};
        const std::list<std::pair<std::string, short>> & getCallList() {return callList;};

        //Intern
        void setAudioCallback(const std::function<void(const std::string & mail)> &callback);
        void setFriendListUpdateCallback(const std::function<void(const std::vector<Contact> &)> & callback);
        void addFriendList(get_contact_t & contact);
        void changeStatus(status_t stat);
        bool checkContactAlreadyExist(const std::string & mail);
        void addMessageToPendingList(const std::string & mail, const std::string & message, unsigned long time);
        void addMessageToMessageListFront(const std::string & mail, const std::string &receiver, const std::string & message, unsigned long time);
        void addMessageToMessageListBack(const std::string & mail, const std::string &receiver, const std::string & message, unsigned long time);
        void deleteFriendList(const std::string & mail);
        void eraseParticipantFromCall(const std::string & ip);

    private:
        //Socket
        UDPConnection UDPsocket;
        TCPConnection TCPsocket;
        Babel::Audio audio;
        //Status
        std::string name;
        std::string email_adr;
        status_t stat;
        std::function<void(const std::vector<Contact> & list)> signalUpdateFriendList;
        //Contact
        std::vector<Contact> contactList;
        std::map<std::string, std::function<void(bool)>> _callbacks;
        std::function<void(const std::list<Message> & list)> listUpdateCallback;
        std::string friendClicked;
        //Read
        std::vector<uint8_t> _data;
        std::function<void(const std::string &, const std::string &, unsigned long)> _callbackUpdateMessage;
        int readed;
        //Call
        std::function<void(const std::string & mail)> gotCallCallback;
        std::list<std::pair<std::string, short>> callList;
        std::string email_calling;
};

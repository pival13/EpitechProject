/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Ubuntu]
** File description:
** AI
*/

#pragma once

#include "Client.hpp"
#include "Json/Json.hpp"
#include <deque>
#include <array>
#include <regex>
#include <map>
#include <list>

///@file

extern std::string connectionHost; ///< Host name or IP adress used for connection.
extern std::string connectionPort; ///< Port used for connection.

typedef std::array<ssize_t, 2> pos_t; ///< Position (x,y) as array
typedef std::pair<std::string, size_t> obj_t; ///< Object pair, with its name on `first`, and its amount on `second`
typedef std::map<std::string, size_t> inv_t; ///< Inventory object, as a list of Object (map)

class AI : private Client {
    ///@brief Direction
    protected: enum Direction {
        Self,
        Front,
        FrontLeft,
        Left,
        BackLeft,
        Back,
        BackRight,
        Right,
        FrontRight
    };
    ///@brief Code of the functions an IA can call
    public: enum FunctionsCode {
        Moving = Client::AiOrder::FWD,
        MovingRight = Client::AiOrder::RGT,
        MovingLeft = Client::AiOrder::LFT,
        Looking = Client::AiOrder::LAR,
        CheckingInventory = Client::AiOrder::INV,
        Talking = Client::AiOrder::BDC,
        CheckingPlaceTeam = Client::AiOrder::UTS,
        LayingEgg = Client::AiOrder::FPL,
        Ejecting = Client::AiOrder::EPL,
        TakingObject = Client::AiOrder::TOJ,
        PuttingObject = Client::AiOrder::SOJ,
        Incantating = Client::AiOrder::INC
    };

    public:
        ///@brief Create a new AI with the team name in which connect.
        ///@details Use the globals variables `connectionPort` and `connectionHost` to establish the connection.
        ///`connectionHost` and `connectionPort` must be defined that for.
        ///
        ///@param name Name of the team to connect.
        AI(const std::string &name);
        ///@brief Create a new AI with the team name, the host and the port used for the connection.
        ///@param name Name of the team to connect.
        ///@param host Host name or IP adress use for connection.
        ///@param port Port use for connection.
        AI(const std::string &name, const std::string &host, size_t port);
        virtual ~AI();

        ///@brief Main loop of the AI.
        ///@details Must be implemented with a similar form:\n
        ///`while (this->_isAlive) {`\n`    // Do some things...`\n`}`
        virtual void launch() = 0;

    public:
        /* 
            Some function that must be call to perform actions.
            They are asynchronous, so callback functions are defined and call in time.
        */

        inline void move() { _pendingActions.push_back(FWD); _pendingActionsParameters.push_back(""); Client::moveForward(); } ///< Send "Forward" to the server. When the server will respond, the callback `actionCallback()` will be called with `FunctionsCode::Moving`.
        inline void turnRight() { _pendingActions.push_back(RGT); _pendingActionsParameters.push_back(""); Client::rotateRight(); } ///< Send "Right" to the server. When the server will respond, the callback `actionCallback()` will be called with `FunctionsCode::MovingRight`.
        inline void turnLeft() { _pendingActions.push_back(LFT); _pendingActionsParameters.push_back(""); Client::rotateLeft(); } ///< Send "Left" to the server. When the server will respond, the callback `actionCallback()` will be called with `FunctionsCode::MovingLeft`.
        inline void look() { _pendingActions.push_back(LAR); Client::lookAround(); } ///< Send "Look" to the server. When the server will respond, the callback `lookCallback()` will be called.
        inline void getInventory() { _pendingActions.push_back(INV); Client::inventory(); } ///< Send "Inventory" to the server. When the server will respond, the callback `inventoryCallback()` will be called.
        inline void eject() { _pendingActions.push_back(EPL); _pendingActionsParameters.push_back(""); Client::ejectPlayers(); } ///< Send "Eject" to the server. When the server will respond, the callback `actionCallback()` will be called with `FunctionsCode::Ejecting`.
        inline void layEgg() { _pendingActions.push_back(FPL); _pendingActionsParameters.push_back(""); Client::forkPlayer(); } ///< Send "Fork" to the server. When the server will respond, the callback `actionCallback()` will be called with `FunctionsCode::LayingEgg`.
        inline void incantate() { _pendingActions.push_back(INC); _pendingActionsParameters.push_back(""); Client::startIncantation(); } ///< Send "Incantation" to the server. When the server will signaled the begining of the incantation, the callback `inIncantation()` will be called. When it will signaled its end, the callback `actionCallback()` will be called with `FunctionsCode::Incantating`.
        inline void talk(const std::string &msg) { _pendingActions.push_back(BDC); _pendingActionsParameters.push_back(msg); Client::broadcastText(msg); } ///< Send "Broadcast " and \@msg to the server. When the server will respond, the callback `actionCallback()` will be called with `FunctionsCode::Talking`.
        inline void take(const std::string &obj) { _pendingActions.push_back(TOJ); _pendingActionsParameters.push_back(obj); Client::takeObject(obj); } ///< Send "Take " and \@obj to the server. When the server will respond, the callback `actionCallback()` will be called with `FunctionsCode::TakingObject`.
        inline void drop(const std::string &obj) { _pendingActions.push_back(SOJ); _pendingActionsParameters.push_back(obj); Client::setObjectDown(obj); } ///< Send "Set " and \@obj to the server. When the server will respond, the callback `actionCallback()` will be called with `FunctionsCode::PuttingObject`.
        
        inline void getRemainingPlace() { Client::unusedTeamSlotsNumber(); } ///< Send "GetRemainingPlace" to the server. When the server will respond, the callback `remainingPlace()` will be called.

    protected:
        /*
            Here are the response/callback of those actions.
            Remember! As they are callback, they are threaded
            actionCallback will be called after the use of:
                move, turnRight, turnLeft, eject, layEgg, talk, take, drop and incantate
                The function called will be passed in parameter, as well as its result
            In case of incantation, at the beginning of the incantation, inIncantation 
            will be called, and at the end, actionCallback with the result of the incantation
        */

        ///@brief Callback functions for boolean action.
        ///@details Below is a list of all case this function is called:
        /// * After a `move()`, with `FunctionsCode::Moving` and True, as a move always succed.
        /// * After a `turnRight()`, with `FunctionsCode::MovingRight` and True, as a move always succed.
        /// * After a `turnLeft()`, with `FunctionsCode::MovingLeft` and True, as a move always succed.
        /// * After a `talk()`, with `FunctionsCode::Talking` and True, as a talk always succed. The message talked can be retrieve in `AI::callbackedActionParameter`.
        /// * After a `layEgg()`, with `FunctionsCode::LayingEgg` and True, as laying an egg always succed.
        /// * After a `eject()`, with `FunctionsCode::Ejecting` and True if someone was eject, False otherwise.
        /// * After a `take()`, with `FunctionsCode::TakingObject` and True if the object mentionned in `AI::callbackedActionParameter` has been take, False otherwise.
        /// * After a `drop()`, with `FunctionsCode::PuttingObject` and True if the object mentionned in `AI::callbackedActionParameter` has been drop, False otherwise.
        /// * At the end of an incantation, with `FunctionsCode::Incantating` and True if the incantation succed, False otherwise. The actual level can be retrieve in `AI::_currentLevel`.
        ///
        ///@param funct FunctionsCode containing the action callbacked.
        ///@param result The result of the action.
        virtual void actionCallback(FunctionsCode funct, bool result) = 0;
        ///@brief Callbacked function of `look()`.
        ///@details Describe the cell at the place of the AI and in front of it.
        ///
        ///Cell are ordered as follow:
        /// * The cell where is the AI.
        /// * The three cells in front of the AI, from left to right.
        /// * The five cells after, and so on, with one more cell to the left and to the right for each depth level.
        ///
        ///At level 1 only the three cells in front of the AI and its own cell are describe, and one level in depth is add per level.
        ///
        ///Exemple of a level 2 `look`:\n`[4][5][6][7][8]`\n`[ ][1][2][3][ ]`\n`[ ][ ][0][ ][ ]`
        ///
        ///@param content Array of `inv_t`
        virtual void lookCallback(const std::deque<inv_t> &content) = 0;
        ///@brief Callbacked function of `getInventory()`.
        ///@details Indicate the content of the inventory as an `inv_t`. Only elements hold are contained.
        ///
        ///@param inventory An `inv_t` embodying the content of the inventory.
        virtual void inventoryCallback(const inv_t &inventory) = 0;
        ///@brief Callback function called when a message is heard.
        ///@details Any message are heard, no matter the team of the speaker. Even your own message may be receive.
        ///
        ///@param orig The origin of the message, as a `Direction`.
        ///@param msg The content of the message.
        virtual void messageReceived(Direction orig, const std::string &msg) = 0;
        ///@brief Callback function called when you are ejected.
        ///
        ///@param orig `Direction` where you come from.
        virtual void beenEject(Direction orig) = 0;
        ///@brief Callback function called when you are dead.
        ///@details This is the last callback called. After this `AI::_isAlive` is set at False.
        virtual void isDead() = 0; 
        ///@brief Callback function of `incantate()`.
        ///@details This function will be called at the begining of the incantation. Therefore, `actionCallback()` will be called when the incantation will end. However this may not happens if `isDead()` is call before.
        virtual void inIncantation() = 0;
        ///@brief Callback function of `getRemainingPlace()`.
        ///
        ///@param remainingPlaces Number of free place remaining in the team.
        virtual void remainingPlace(size_t remainingPlaces) = 0;

    private:
        void responseParser();


    protected:
        bool _isConnect; ///< Set at True when the AI successfully connect to the server.
        bool _isAlive; ///< Set at False when the AI receive the `dead` message.
        bool _constructed; ///< Boolean which can be set at True when everything is constructed. Useful to avoid called of Callback before they are instanciate. After one second, automatically set at True.

        bool _inIncantation; ///< Boolean representing whether an AI currently incantate.
        size_t _currentLevel; ///< Current level of the AI.
        pos_t _mapSize; ///< Size of the map.

        std::string callbackedActionParameter; ///< Parameter of the current callbacked function.

    private:
        std::deque<Client::AiOrder> _pendingActions;
        std::deque<std::string> _pendingActionsParameters;
        std::thread _thread;
};

bool operator>(const pos_t &p1, const pos_t &p2);
bool operator<(const pos_t &p1, const pos_t &p2);
bool operator==(const pos_t &p1, const pos_t &p2);
bool operator!=(const pos_t &p1, const pos_t &p2);
pos_t operator+(const pos_t &p1, const pos_t &p2);
inv_t operator+(const inv_t &i1, const inv_t &i2);
std::ostream &operator<<(std::ostream &os, const pos_t &pos);
std::ostream &operator<<(std::ostream &os, const AI::FunctionsCode &pos);

Json getSettingsAI(); ///< Create default settings if none can be found, or retrieve those ar `zappySettings.json`

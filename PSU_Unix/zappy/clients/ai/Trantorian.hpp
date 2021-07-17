/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Ubuntu]
** File description:
** Trantorian
*/

#pragma once

#include "Process.hpp"
#include "AI.hpp"

#include <queue>
#include <vector>
#include <map>
#include <chrono>
#include <cmath>

class Trantorian : public AI {
    protected: struct OtherPlayer {
        size_t number;
        uint8_t level;
        size_t lastMsgNb;
        pos_t pos;
        bool incantate;
    };
    protected: enum Orientation {
        North,
        West,
        South,
        East
    };
    private: enum Circumstance {
        GatherObject,
        RallyLayer,
        WaitLayer,
        WaitAscend,
        RallyAscend,
        HelpAscend
    };

    public:
        Trantorian(const std::string &teamName);
        virtual ~Trantorian();

        virtual void launch();

    protected:
        ///@brief Prepare a move. Should be prefer at `move()`
        ///@param timeout Number of turn before executing the action.
        void prepareMove(size_t timeout=0) { addActionToDo([this]() { move(); }, timeout); }
        ///@brief Prepare a rotation to the right. Should be prefer at `turnRight()`
        ///@param timeout Number of turn before executing the action.
        void prepareTurnRight(size_t timeout=0) { addActionToDo([this]() { turnRight(); }, timeout); }
        ///@brief Prepare a rotation to the left. Should be prefer at `turnLeft()`
        ///@param timeout Number of turn before executing the action.
        void prepareTurnLeft(size_t timeout=0) { addActionToDo([this]() { turnLeft(); }, timeout); }
        ///@brief Prepare a look. Should be prefer at `look()`
        ///@param timeout Number of turn before executing the action.
        void prepareLook(size_t timeout=0) { addActionToDo([this]() { look(); }, timeout); }
        ///@brief Prepare a lookback of the inventory. Should be prefer at `getInventory()`
        ///@param timeout Number of turn before executing the action.
        void prepareGetInventory(size_t timeout=0) { addActionToDo([this]() { getInventory(); }, timeout); }
        ///@brief Prepare an eject. Should be prefer at `eject()`
        ///@param timeout Number of turn before executing the action.
        void prepareEject(size_t timeout=0) { addActionToDo([this]() { eject(); }, timeout); }
        ///@brief Prepare the creation of an egg. Should be prefer at `layEgg()`
        ///@param timeout Number of turn before executing the action.
        void prepareLayEgg(size_t timeout=0) { addActionToDo([this]() { layEgg(); }, timeout); }
        ///@brief Prepare an incantation. Should be prefer at `incantate()`
        ///@param timeout Number of turn before executing the action.
        void prepareIncantate(size_t timeout=0) { addActionToDo([this]() { incantate(); }, timeout); }
        ///@brief Prepare a talk. Moreover, will transform the message as a Trantorian message. Should be prefer at `talk()`
        ///@param timeout Number of turn before executing the action.
        void prepareTalk(const std::string &msg, size_t timeout=0) { addActionToDo([this, msg]() { trantorianTalk(msg); }, timeout); }
        ///@brief Prepare taking an object. Should be prefer at `take()`
        ///@param timeout Number of turn before executing the action.
        void prepareTake(const std::string &obj, size_t timeout=0) { addActionToDo([this, obj]() { take(obj); }, timeout); }
        ///@brief Prepare droping an object. Should be prefer at `drop()`
        ///@param timeout Number of turn before executing the action.
        void prepareDrop(const std::string &obj, size_t timeout=0) { addActionToDo([this, obj]() { drop(obj); }, timeout); }

        ///@brief Overload of `AI::actionCallback`. If a Trantorian is not intended to be used, should be overload as well.
        ///@details Update the map, the inventory, the position and the orientation according to the function callbacked.
        virtual void actionCallback(FunctionsCode funct, bool result);
        ///@brief Overload of `AI::lookCallback`. If a Trantorian is not intended to be used, should be overload as well.
        ///@details Update the map according to the parameter.
        virtual void lookCallback(const std::deque<inv_t> &content);
        ///@brief Overload of `AI::inventoryCallback`. If a Trantorian is not intended to be used, should be overload as well.
        ///@details Update the inventory according to the parameter.
        virtual void inventoryCallback(const inv_t &inventory);
        ///@brief Overload of `AI::messageReceived`. If a Trantorian is not intended to be used, should be overload as well.
        ///@details Update the players of the teams according to the parameter.
        virtual void messageReceived(Direction orig, const std::string &msg);
        ///@brief Overload of `AI::beenEject`. If a Trantorian is not intended to be used, should be overload as well.
        ///@details Update the position.
        virtual void beenEject(Direction orig);
        ///@brief Overload of `AI::isDead`. If a Trantorian is not intended to be used, should be overload as well.
        ///@details Do nothing.
        virtual void isDead();
        ///@brief Overload of `AI::inIncantation`. If a Trantorian is not intended to be used, should be overload as well.
        ///@details Do nothing.
        virtual void inIncantation();
        ///@brief Overload of `AI::remainingPlace`. If a Trantorian is not intended to be used, should be overload as well.
        ///@details Do nothing, because `getRemainingPlace()` is never call by a `Trantorian` AI.
        virtual void remainingPlace(size_t remainingPlaces);
    
    protected:
        ///@brief Number of action to reach a place, given a certain position and orientation.
        ///
        ///@param destination 
        ///@param origin Default to the current position.
        ///@param direction Default to the current orientation.
        ///@return Number of action needed to reach \@destination.
        size_t actionToReach(const pos_t &destination, const pos_t &origin=pos_t({-1,-1}), const pos_t &direction=pos_t({0,0}));
        ////@brief Check whether a position is in front of you, given a certain direction.
        ///
        ///@param pos 
        ///@param dir Default to the current orientation.
        ///@return True if the position is in front of you.
        bool isFront(const pos_t &pos, const pos_t &dir=pos_t({0,0}));
        bool isObjectFront(const std::string &obj, bool checkOnYou=true);
        ///@brief Check whether any object of \@obj is in front of you.
        bool isObjectFront(const inv_t &obj, bool checkOnYou=true);
        bool isObjectNear(const std::string &obj, bool checkOnSelf=true);
        ///@brief Check whether any object of \@obj is on the map.
        bool isObjectNear(const inv_t &obj, bool checkOnSelf=true);
        ///@brief Return the position of the closest object of \@obj. If assigneAsTarget is set at true, fill _wantedObject with the closest object.
        pos_t posClosestObject(const inv_t &obj, bool frontOnly, bool checkOnSelf=true, bool assignAsTarget=true);
        pos_t posClosestObject(const std::string &obj, bool frontOnly, bool checkOnSelf=true, bool assignAsTarget=true);
        ///@brief Convert the current orientation to a vector `pos_t`, following the given rules.
        pos_t orientationToVector(ssize_t forward=1, ssize_t lateral=0);
        ///@brief Convert a `AI::Direction` to a vector `pos_t`
        pos_t directionToVector(Direction dir);
        pos_t directionToWorldMax(Direction dir);
        ///@brief Check whether the current position is the same as the origin of the last `look()`.
        bool isAtOriginLook();

        void goToPos(const pos_t &pos, bool usePrepare=true);
        ///@brief Update the content of `Trantorian::_world` with the result of a look, according to the current Orientation.
        void updateWorld(const std::deque<inv_t> &lookResult, bool resetWorld=true);
        ///@brief Variant of `talk()`, which add your number, team-name, message number and position to the message.
        void trantorianTalk(const std::string &msg);
        ///@brief Check whether a message belongs to a member of the team other than yourself. Edit the message to let only the talker and the original message.
        bool preParseMessage(std::string &msg);
        ///@brief Get the time needed to execute a given action.
        size_t getActionTime(FunctionsCode action);
        size_t getActionTime(const std::string &action);
        ///@brief Add an action to do.
        void addActionToDo(const std::function<void()> &funct, size_t timeout=0);
        
        void changeCircumstance(Circumstance newCircumstance);
        ///@brief Create a new `Process` which will try to connect on the same team.
        ///@details Use the globals variable `connectionHost` and `connectionPort` as well as `Trantorian::_teamName` to connect the new AI.
        ///
        ///The new process will execute the below command to launch the new AI. Make sure this is possible before using this function.
        /// * `./zappy_ai -h connectionHost -p connectionPort -n Trantorian::_teamName --child-kind=@kind`
        ///
        ///@param kind The kind of AI to create.
        void createNewChild(const std::string &kind);
        
        ///@brief Initial action use for Trantorian.
        ///@details Implied the emission of a welcome message, an initial `look()`, the set of `Trantorian::_timePerAction` and the first `loopTrantorianTalk()`.
        void initialActionLaunch();
        ///@brief Action to execute at each turn of the main loop.
        ///@details Implied the handling of food, some call to `getInventory()` when weird things happens, and the execution of passed actions of `Trantorian::_todoActions`.
        void executePerTurnAction();
        ///@brief Call `trantorianTalk()` with the string in `Trantorian::_whatToSay` and prepare another `loopTrantorianTalk()` for 50 actions later.
        void loopTrantorianTalk();

    protected:
        const size_t _personalNumber; ///< Pid of the AI.
        size_t _msgNumber = 0;        ///< Id tof the next message.
        const std::string _teamName;  ///< Name of the team.

        size_t _currentAction = 0; ///< More or less the current action index.
        std::chrono::nanoseconds _timePerAction; ///< More or less the time for one action. Must not be used when possible.

        pos_t _pos = {0, 0};    ///< The current position
        pos_t _targetPos = {0, 0}; ///< The position of the target.
        std::string _wantedObject = ""; ///< The name of the targeted object, if any.
        Orientation _orientation = North; ///< The current orientation.
        bool _posSynchronized = false;
        inv_t _targetObjects;
        inv_t _optionalObjects;
        std::string _whatToSay; ///< String passed as parameter of `trantorianTalk()` on `loopTrantorianTalk()`.

        inv_t _inventory; ///< The current inventory.
        std::map<pos_t, inv_t> _world; ///< The current world, not dependant of its size.

        std::list<OtherPlayer> _otherPlayers; ///< All the other players of the teams.

        Json _settings; ///< The settings present in `zappySettings.json`
    
    private:
        Circumstance _currentCircumstance = GatherObject;
        std::queue<Process> _childs;
        std::recursive_mutex _todoMutex;
        std::map<size_t, std::list<std::function<void()>>> _todoActions;

    private:
        const std::map<Circumstance, void (Trantorian::*)()> _updateGoalCircumstance = {
            {GatherObject, &Trantorian::updateGoalGatherObject},
            {RallyLayer, &Trantorian::updateGoalRallyLayer},
            {RallyAscend, &Trantorian::updateGoalRallyAscend},
            {WaitAscend, &Trantorian::updateGoalWaitAscend}
        };
        const std::map<Circumstance, void (Trantorian::*)(FunctionsCode,bool)> _actionCallbackCircumstance = {
            {GatherObject, &Trantorian::actionCallbackGatherObject},
            {RallyLayer, &Trantorian::actionCallbackRallyLayer},
            {RallyAscend, &Trantorian::actionCallbackRallyAscend},
            {WaitAscend, &Trantorian::actionCallbackWaitAscend}
        };
        const std::map<Circumstance, void (Trantorian::*)(Direction, const std::string &)> _msgReceivedCircumstance = {
            {GatherObject, &Trantorian::messageReceivedGatherObject},
            {RallyLayer, &Trantorian::messageReceivedRallyLayer},
            {RallyAscend, &Trantorian::messageReceivedRallyAscend},
            {WaitAscend, &Trantorian::messageReceivedWaitAscend}
        };

    /**********************************/
    /*          GatherObject          */
    /**********************************/

        void selectNextTargetGatherObject();
        
        void updateGoalGatherObject();
        void actionCallbackGatherObject(FunctionsCode funct, bool result);
        void messageReceivedGatherObject(Direction orig, const std::string &msg);

    /**********************************/
    /*           WaitAscend           */
    /**********************************/

        std::map<size_t,pos_t> _supportingAlliesAscend;
        bool _givingUpWaitAscend;
        
        void goToClosestFood();
        void askHelpWaitAscend();
        bool isCellReadyAscend();
        void prepareCellAscend();
        void waitForAscendWaitAscend(FunctionsCode code);
        void givingUpAscendWaitAscend();

        void updateGoalWaitAscend();
        void actionCallbackWaitAscend(FunctionsCode funct, bool result);
        void messageReceivedWaitAscend(Direction orig, const std::string &msg);

    /**********************************/
    /*           RallyAscend          */
    /**********************************/

        size_t _ascenderToRally;

        void updateStockRallyAscend();

        void updateGoalRallyAscend();
        void actionCallbackRallyAscend(FunctionsCode funct, bool result);
        void messageReceivedRallyAscend(Direction orig, const std::string &msg);

    /**********************************/
    /*           RallyLayer           */
    /**********************************/

        bool _actionPlannedRallyLayer;
        bool _ejectedLastRL = false;
        bool _isWithPlayerRallyLayer = false;

        void goToTargetRallyLayer();
        void beenEjectRallyLayer();

        void updateGoalRallyLayer();
        void actionCallbackRallyLayer(FunctionsCode funct, bool result);
        void messageReceivedRallyLayer(Direction orig, const std::string &msg);
};

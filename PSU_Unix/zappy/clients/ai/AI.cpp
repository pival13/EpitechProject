/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Ubuntu]
** File description:
** AI
*/

#include "AI.hpp"

static sighandler_t oldSig = nullptr;
static bool *globalAlive = NULL;

static void signalHandler(int sig)
{
    if (sig == SIGINT) {
        *globalAlive = false;
        if (oldSig && oldSig != SIG_DFL)
            oldSig(sig);
    }
}

AI::AI(const std::string &name) : AI(name, connectionHost, std::stoul(connectionPort)) {}

AI::AI(const std::string &name, const std::string &host, size_t port)
: Client(host, std::to_string(port), name), _isConnect(false), _isAlive(true), _constructed(false), _inIncantation(false), _currentLevel(1), _mapSize({0, 0})
{
    globalAlive = &_isAlive;
    oldSig = signal(SIGINT, SIG_DFL);
    signal(SIGINT, signalHandler);
    _thread = std::thread([this]() { this->responseParser(); });
}

AI::~AI()
{
    _isAlive = false;
    parsed.notify_all();
    _thread.join();
}

void AI::responseParser()
{
    std::list<AiOrder> booleanAction({FWD, LFT, RGT, BDC, FPL, EPL, TOJ, SOJ, INC});
    auto wordCounter = [](const std::string &s, const std::string &re) {
        size_t n = 0;
        for (size_t pos = 0; (pos = s.find(re, pos)) != std::string::npos; pos += re.length())
            n++;
        return n;
    };
    auto numberReader = [](const KVector<std::string> &list, const std::string &re) {
        size_t n = 0;
        std::for_each(list.begin(), list.end(), [&re, &n](const std::string &s) {
            std::smatch m;
            if (std::regex_search(s, m, std::regex(re)))
                n += stoul(m[1].str());
        });
        return n;
    };

    while(!_logged && _isAlive && !connectionFailed);
    if (connectionFailed)
        _isAlive = false;
    else
        _isConnect = true;

    for (size_t i = 0; _isAlive && !_constructed && i < 100; i++)
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::mutex mutex;
    std::unique_lock<std::mutex> lock(mutex);
    while (_isAlive && !closed) {
        while (!_aiOrders.empty()) {
            std::array<AiOrder, 2> kinds = {_aiOrders[0], _pendingActions.size() > 0 ? _pendingActions[0] : _aiOrders[0]};
    
            ClientData data = _clientDatas[0];
            _aiOrders.eraseAt(0);
            _clientDatas.eraseAt(0);

            if (kinds[0] == DED) { // is dead
                _isAlive = false;
                isDead();
                return;
            } else if (kinds[0] == EJC) { // has been ejected
                beenEject(Direction(data.integer));
                _pendingActions.push_front(EJC);
            } else if (kinds[0] == MSG) { // received a message
                messageReceived(Direction(data.integer), data.string);
                _pendingActions.push_front(MSG);
            } else if (kinds[0] == MPS) { // received map size (signed of connection established)
                _mapSize = pos_t({data.position.x, data.position.y});
                _pendingActions.push_front(MPS);
            
            } else if ((kinds[0] == UTS && _mapSize[0] == 0) || kinds[1] == UTS) { // number of client that can still connect
                remainingPlace(data.integer);
                if (_mapSize[0] == 0)
                    _pendingActions.push_front(UTS);
            } else if (kinds[0] == INC || (kinds[1] == INC && !_inIncantation)) { // beginning of incantation
                if (data.boolean) {
                    _inIncantation = true;
                    inIncantation();
                    _pendingActions.push_front(INC);
                    _pendingActionsParameters.push_front("");
                } else {
                    _inIncantation = false;
                    actionCallback(FunctionsCode(INC), false);
                }
                if (kinds[1] != INC)
                    _pendingActions.push_front(INC);
                else
                    _pendingActionsParameters.pop_front();

            } else if (std::count(booleanAction.begin(), booleanAction.end(), kinds[1])) { // one of the boolean function
                if (kinds[1] == INC) {
                    _inIncantation = false;
                    if (data.boolean)
                        _currentLevel = data.integer;
                }
                callbackedActionParameter = _pendingActionsParameters.front();
                actionCallback(FunctionsCode(kinds[1]), data.boolean);
                callbackedActionParameter.clear();
                _pendingActionsParameters.pop_front();
            } else if (kinds[1] == INV) { // inventory
                inventoryCallback(inv_t({
                    {"food", numberReader(data.stringVector, "food (\\d+)")},
                    {"linemate", numberReader(data.stringVector, "linemate (\\d+)")}, 
                    {"deraumere", numberReader(data.stringVector, "deraumere (\\d+)")},
                    {"sibur", numberReader(data.stringVector, "sibur (\\d+)")},
                    {"mendiane", numberReader(data.stringVector, "mendiane (\\d+)")},
                    {"phiras", numberReader(data.stringVector, "phiras (\\d+)")}, 
                    {"thystame", numberReader(data.stringVector, "thystame (\\d+)")}
                }));
            } else if (kinds[1] == LAR) { // Look
                std::deque<inv_t> inv;
                for (auto &detail : data.stringVector) {
                    inv.push_back(inv_t({
                        {"player", wordCounter(detail, "player")},
                        {"food", wordCounter(detail, "food")},
                        {"linemate", wordCounter(detail, "linemate")},
                        {"deraumere", wordCounter(detail, "deraumere")},
                        {"sibur", wordCounter(detail, "sibur")},
                        {"mendiane", wordCounter(detail, "mendiane")},
                        {"phiras", wordCounter(detail, "phiras")},
                        {"thystame", wordCounter(detail, "thystame")}
                    }));
                }
                lookCallback(inv);
            }

            _pendingActions.pop_front();
        }
        parsed.wait_for(lock, std::chrono::milliseconds(100));
    }
    _isAlive = false;
}
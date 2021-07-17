/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019 [WSL: Ubuntu]
** File description:
** Kitchen
*/

#include "Kitchen.hpp"

using namespace Plazza;

Kitchen::Kitchen(size_t nbCooker, size_t refreshTimeout)
: cookerState(nbCooker, cookerStatus::Waiting), cookersPizza(nbCooker), cooker(nbCooker)
, fridge(PizzaFactory::getIngredientNumber(), refreshTimeout), lastAction(std::chrono::system_clock::now())
{
}

Kitchen::~Kitchen()
{
    _closure = true;
    fridge.close();
    cvEnd.notify_all();
    for (std::thread &t : cooker)
        if (t.joinable())
            t.join();
}

void Kitchen::addOrder(std::unique_ptr<Pizza> pizza)
{
    size_t index = std::find_if(cookerState.begin(), cookerState.end(), [](cookerStatus a) { return a == cookerStatus::Waiting; }) - cookerState.begin();
    if (index != cookerState.size()) {
        cookerState[index] = cookerStatus::TakingOrder;
        cookersPizza[index] = std::move(pizza);
        if (cooker[index].joinable())
            cooker[index].join();
        cooker[index] = std::thread([this, index]() { this->completeOrder(index); });
    } else {
        mWaitingList.lock();
        waitingPizzas.push_back(std::move(pizza));
        mWaitingList.unlock();
    }
}

void Kitchen::completeOrder(size_t cookerNb)
{
    std::mutex m;
    std::unique_lock<std::mutex> lck(m);
    cookerState[cookerNb] = cookerStatus::TakingIngredients;
    fridge.takeIngredient(cookersPizza[cookerNb]->getIngredients());
    cookerState[cookerNb] = cookerStatus::Cooking;
    if (_closure || cvEnd.wait_for(lck, std::chrono::milliseconds(cookersPizza[cookerNb]->getCookTime())) != std::cv_status::timeout)
        return;
    cookerState[cookerNb] = cookerStatus::Delivering;
    mCompleteList.lock();
    readyPizzas.push_back(std::move(cookersPizza[cookerNb]));
    mCompleteList.unlock();

    if (!waitingPizzas.empty() && !_closure) {
        cookerState[cookerNb] = cookerStatus::TakingOrder;
        mWaitingList.lock();
        if (!waitingPizzas.empty()) {
            cookersPizza[cookerNb] = std::move(waitingPizzas.front());
            waitingPizzas.pop_front();
            mWaitingList.unlock();
            completeOrder(cookerNb);
        } else
            mWaitingList.unlock();
    }

    lastAction = std::chrono::system_clock::now();
    cookerState[cookerNb] = cookerStatus::Waiting;
}

void Kitchen::communicater(Process &reception)
{
    while (!_closure) {
        if (lastAction + std::chrono::seconds(5) <= std::chrono::system_clock::now() && waitingPizzas.empty() && readyPizzas.empty() &&
            std::all_of(cookerState.begin(), cookerState.end(), [](cookerStatus s) { return s == cookerStatus::Waiting; }))
            _closure = true;
        else if (!readyPizzas.empty()) {
            reception.sendData(*readyPizzas.front());
            readyPizzas.pop_front();
        }

        IPData msgData = reception.tryReceiveData();
        if (!msgData.isType(typeid(IPInt))) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }

        size_t task = IPInt(msgData.getData());
        if (task == IPCMessageKind::addRecipe) {
            msgData = reception.receiveData();
            if (msgData.isType(typeid(IPString)))
                PizzaFactory::addNewPizza(IPString(msgData.getData()));
        } else if (task == IPCMessageKind::getNbOrder) {
            IPInt result = getCurrentOrder();
            reception.sendData(result);
        } else if (task == IPCMessageKind::addOrder) {
            msgData = reception.receiveData();
            if (msgData.isType(typeid(Pizza)))
                addOrder(std::make_unique<Pizza>(msgData.getData()));
        } else if (task == IPCMessageKind::closure)
            _closure = true;
    }
}
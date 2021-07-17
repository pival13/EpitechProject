/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019 [WSL: Ubuntu]
** File description:
** Reception
*/

#include "Reception.hpp"

using namespace Plazza;

Reception::Reception(size_t nbCooker, size_t refreshTimeout)
: _end(false), _nbChief(nbCooker), _refreshTime(refreshTimeout)
{
}

Reception::~Reception()
{
    _end = true;
    if (waiter.joinable())
        waiter.join();
    for (auto &p : kitchens) {
        IPInt task(IPCMessageKind::closure);
        p.sendData(task);
        if (p.joinable())
            p.join();
    }
}

std::list<Process>::iterator Reception::getKitchen(size_t index)
{
    auto kitchen = kitchens.begin();
    for (size_t i = 0; i != index && kitchen != kitchens.end(); i++)
        ++kitchen;
    if (kitchen == kitchens.end() || !kitchen->isAlive())
        return kitchens.end();
    return kitchen;
}

size_t Reception::getNbKitchen()
{
    for (auto p = kitchens.begin(); p != kitchens.end(); ++p)
        if (!p->isAlive()) {
            p->join();
            kitchens.erase(p);
            p = kitchens.begin();
        }
    return kitchens.size();
}

size_t Reception::getKitchenOrder(size_t index)
{
    auto kitchen = getKitchen(index);
    if (kitchen == kitchens.end())
        return _nbChief * 2;

    IPInt task(IPCMessageKind::getNbOrder);
    mWaiter.lock();
    kitchen->sendData(task);

    IPData data = kitchen->receiveData();
    while (data.isType(typeid(Pizza))) {
        std::cout << Pizza(data.getData()) << " is ready" << std::endl;
        data = kitchen->receiveData();
    }
    mWaiter.unlock();
    if (!data.isType(typeid(IPInt)))
        return _nbChief * 2;
    IPInt result(data.getData());

    return result;
}

void Reception::addNewKitchen()
{
    size_t nbChief = this->_nbChief;
    size_t refreshTime = this->_refreshTime;
    kitchens.emplace_back([nbChief, refreshTime](Process &reception) {
        Kitchen k(nbChief, refreshTime);
        k.communicater(reception);
        return 0;
    });
}

void Reception::addOrder(size_t index, std::unique_ptr<Pizza> &order)
{
    auto kitchen = getKitchen(index);
    if (kitchen == kitchens.end())
        throw std::runtime_error("Try to add order to a close kitchen");

    IPInt task(IPCMessageKind::addOrder);
    kitchen->sendData(task);
    kitchen->sendData(*order);
}

void Reception::splitOrders()
{
    size_t nbKitchen = getNbKitchen();
    size_t remainingPlace = 0;
    std::deque<size_t> arr(nbKitchen);

    for (size_t i = 0; i != nbKitchen; i++)
        arr[i] = getKitchenOrder(i);
    for (size_t v : arr) remainingPlace += _nbChief * 2 - v;
    while (remainingPlace < orders.size()) {
        addNewKitchen();
        remainingPlace += _nbChief * 2;
        arr.push_back(0);
    }

    while (!orders.empty()) {
        size_t index = std::min_element(arr.begin(), arr.end()) - arr.begin();
        addOrder(index, orders.front());
        orders.pop();
        arr[index]++;
    }
}

void Reception::parseOrder(const std::smatch &sm)
{
    if (!PizzaFactory::knownPizza(sm[1].str()))
        std::cerr << "Unknow order \e[3m" << sm[1].str() << "\e[0m" << std::endl;
    else {
        for (size_t i = 0; i != std::stoul(sm[3].str()); i++) {
            orders.emplace(PizzaFactory::createPizza(sm[1].str(), (sm[2].str() == "S"? PizzaSize::S:
                                                                (sm[2].str() == "M"? PizzaSize::M:
                                                                (sm[2].str() == "L"? PizzaSize::L:
                                                                (sm[2].str() == "XL"? PizzaSize::XL: PizzaSize::XXL))))));
        }
    }
    if (sm[4].length())
        parseOrder(sm[4].str());
    else
        splitOrders();
}

void Reception::parseOrder(const std::string &line)
{
    std::smatch sm;

    if (std::regex_match(line, sm, std::regex("\\s*(\\w+)\\s+(S|M|L|XL|XXL)\\s+x(\\d+)(?:\\s*;\\s*(.+))?\\s*", std::regex_constants::icase)))
        parseOrder(sm);
    else
        std::cerr << "Invalid order: \e[3m" << line << "\e[0m" << std::endl;
}

void Reception::parseLine(const std::string &line)
{
    std::smatch sm;
    if (std::regex_match(line, std::regex("\\s*status\\s*", std::regex_constants::icase))) {
        std::cout << PizzaFactory::status() /*<< "\n" << fridge.status()*/ << std::endl;
        for (size_t i = 0; i < getNbKitchen(); i++)
            std::cout << "Kitchen " << i+1 << ": " << getKitchenOrder(i) << " orders" << std::endl;
    } else if (line.empty() || std::regex_match(line, std::regex("\\s*(exit|quit|q|close)\\s*", std::regex_constants::icase))) {
        throw CompletionException();
    } else if (std::regex_match(line, std::regex("\\s*clear\\s*", std::regex_constants::icase))) {
        std::cout << "\e[3J\e[H\e[2J";
    } else if (std::regex_match(line, sm, std::regex("\\s*(?:new|add)(?:\\s+pizza)?\\s+(\\w+\\s+\\d+\\s+(?:\\s*\\w+)+)\\s*", std::regex_constants::icase))) {
        try {
            PizzaFactory::addNewPizza(sm[1].str());
            for (auto &p : kitchens) {
                IPInt task(IPCMessageKind::addRecipe);
                p.sendData(task);
                IPString recipe(sm[1].str());
                p.sendData(recipe);
            }
            std::cout << "New order register! Thank you very much!" << std::endl;
        } catch (const std::runtime_error &e) {
            std::cerr << e.what() << std::endl;
        }
    } else if (std::regex_match(line, sm, std::regex("\\s*(\\w+)\\s+(S|M|L|XL|XXL)\\s+x(\\d+)(?:\\s*;\\s*(.+))?\\s*"))) {
        parseOrder(sm);
    } else {
        std::cout << "Unknow operation" << std::endl;
    }
}

void Reception::deliverOrders()
{
    while (!_end) {
        for (auto &p: kitchens) {
            mWaiter.lock();
            IPData data = p.tryReceiveData();
            if (data.isType(typeid(Pizza)))
                std::cout << Pizza(data.getData()) << " is ready" << std::endl;
            mWaiter.unlock();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int Reception::newDay()
{
    std::string s;

    waiter = std::thread([this]() { this->deliverOrders(); });
    try {
        while (1) {
            std::getline(std::cin, s);
            parseLine(s);
        }
    } catch (const CompletionException &e) {
        std::cout << e.what() << std::endl;
        return 0;
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        return 84;
    }
    return 0;
}
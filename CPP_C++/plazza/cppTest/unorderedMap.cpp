/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019 [WSL: Ubuntu]
** File description:
** Kitchen
*/

#include <unordered_map>
#include <iostream>
#include <algorithm>

template<class T> class scasecmp {
    public: bool operator() (const T& x, const T& y) const {
        return std::equal(x.begin(), x.end(), y.begin(), y.end(),
            [](const auto a, const auto b) { return tolower(a) == tolower(b); });
    }
};

template<class T> class ihash {
    public: size_t operator() (const T& y) const {
        std::hash<T> h;
        T s = y;
        for (auto &a : s)
            a = tolower(a);
        return h(s);
    }
};

int main()
{
    scasecmp<std::string> a;
    std::cout << a("Regina", "Regina") << ", " << a("regina", "Regina") << ", " <<
                 a("REGINA", "Regina") << ", " << a("Reginae", "Regina") << std::endl;

    std::unordered_map<std::string, int, ihash<std::string>, scasecmp<std::string>> m;
    m["Regina"] = 3;
    m["regina"] = 1;
    for (auto i : m)
        std::cout << i.first << ":" << i.second << " ";
    std::cout << std::endl;
}
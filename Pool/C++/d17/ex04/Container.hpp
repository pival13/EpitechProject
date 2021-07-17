/*
** EPITECH PROJECT, 2020
** cpp_d17_2019 [WSL: Ubuntu]
** File description:
** Container
*/

#pragma once

#include <iostream>
#include <algorithm>
#include <array>

template<class T, template<typename, typename> class U>
class contain {
	public:
		contain() : cont() {}
		~contain() {}

        void push(const T &data) { cont.emplace(cont.end(), data); }
        void aff() { for (T value : cont) std::cout << "Value: " << value << std::endl; }
        void add() { for (T &value : cont) ++value; }

	private:
        U<T, std::allocator<T>> cont;
};

template<class T>
void aff(T &b) { std::cout << "Value: " << b << std::endl; }

template<class T>
void add(T &b) { ++b; }
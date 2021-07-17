/*
** EPITECH PROJECT, 2020
** cpp_d16_2019 [WSL: Ubuntu]
** File description:
** Parser
*/

#pragma once

#include <iostream>
#include <stack>
#include <cctype>

class Parser {
	public:
		Parser();
		~Parser();

        void reset();
        int result() const;
        void feed(const std::string &);

	private:
        void calculate();

        std::stack<char> _operator;
        std::stack<int> _operand;
};

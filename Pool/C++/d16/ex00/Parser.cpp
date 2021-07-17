/*
** EPITECH PROJECT, 2020
** cpp_d16_2019 [WSL: Ubuntu]
** File description:
** Parser
*/

#include "Parser.hpp"

Parser::Parser() : _operator(), _operand()
{
}

Parser::~Parser()
{
}

void Parser::feed(const std::string &expr)
{
    std::string str(expr);

    while (str.length() > 0) {
        char c = str[0];
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%')
            _operator.push(c);
        else if (c == ')')
            calculate();
        else if (std::isdigit(c)) {
            _operand.push(atoi(str.c_str()));
        }

        if (std::isdigit(c)) {
            while (std::isdigit(str[0]))
                str = str.substr(1);
        } else
            str = str.substr(1);
    }

    while (_operand.size() > 1) {
        if (_operator.size() == 0)
            _operator.push('+');
        calculate();
    }
}

void Parser::calculate()
{
    int b = _operand.top();
    _operand.pop();
    int a = _operand.top();
    _operand.pop();

    if (_operator.top() == '+')
        _operand.push(a+b);
    else if (_operator.top() == '-')
        _operand.push(a-b);
    else if (_operator.top() == '*')
        _operand.push(a*b);
    else if (_operator.top() == '/')
        _operand.push(a/b);
    else
        _operand.push(a%b);
    _operator.pop();
}

int Parser::result() const { return _operand.top(); }

void Parser::reset() { _operand.pop(); }
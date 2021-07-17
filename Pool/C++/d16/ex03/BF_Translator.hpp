/*
** EPITECH PROJECT, 2020
** cpp_d16_2019 [WSL: Ubuntu]
** File description:
** BF_Translator
*/

#pragma once

#include <map>
#include <iostream>
#include <fstream>

class BF_Translator {
	public:
        BF_Translator();
        ~BF_Translator();

        int translate(const std::string &in, const std::string &out);

	protected:
	private:
        std::map<char,std::string> bfChar;
};

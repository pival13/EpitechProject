/*
** EPITECH PROJECT, 2020
** cpp_d17_2019 [WSL: Ubuntu]
** File description:
** OneTime
*/

#pragma once

#include "IEncryptionMethod.hpp"

#include <iostream>

class OneTime : public IEncryptionMethod {
	public:
		OneTime(const std::string &key);
		~OneTime();
        
		void encryptChar(char plainchar);
		void decryptChar(char cipherchar);
		void reset();

	protected:
	private:
        const std::string key;
        int index;
};

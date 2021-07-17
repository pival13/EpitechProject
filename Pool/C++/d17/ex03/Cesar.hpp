/*
** EPITECH PROJECT, 2020
** cpp_d17_2019 [WSL: Ubuntu]
** File description:
** Cesar
*/

#pragma once

#include "IEncryptionMethod.hpp"
#include <iostream>

class Cesar : public IEncryptionMethod {
	public:
		Cesar();
		~Cesar();

		void encryptChar(char plainchar);
		void decryptChar(char cipherchar);
		void reset();

	protected:
	private:
        int shift;
};

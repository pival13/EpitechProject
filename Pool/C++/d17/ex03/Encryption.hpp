/*
** EPITECH PROJECT, 2020
** cpp_d17_2019 [WSL: Ubuntu]
** File description:
** Encryption
*/

#pragma once

#include "IEncryptionMethod.hpp"
#include <algorithm>
#include <functional>
#include <iostream>

class Encryption {
	public:
		Encryption(IEncryptionMethod &meth, void (IEncryptionMethod::*f)(char));
		~Encryption();

        void operator()(char);
        
        static void encryptString(IEncryptionMethod &, const std::string &);
        static void decryptString(IEncryptionMethod &, const std::string &);

	protected:
	private:
        IEncryptionMethod &method;
        void (IEncryptionMethod::*ptr)(char);
};

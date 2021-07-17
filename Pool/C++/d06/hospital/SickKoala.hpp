/*
** EPITECH PROJECT, 2020
** cpp_day06_2019 [WSL: Ubuntu]
** File description:
** SickKoala
*/

#ifndef SICKKOALA_H
#define SICKKOALA_H

#include <string>
#include <cstdlib>

struct SickKoala {
	SickKoala(std::string name);
	~SickKoala();

	void poke();
	bool takeDrug(std::string drug);
	void overDrive(std::string str);
	std::string getName();

	std::string name;
};

#endif
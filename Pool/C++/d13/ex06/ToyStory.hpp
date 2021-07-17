/*
** EPITECH PROJECT, 2020
** cpp_d13_2019 [WSL: Ubuntu]
** File description:
** ToyStory
*/

#pragma once

#include "Toy.hpp"

class ToyStory {
	public:
		ToyStory();
		~ToyStory();

        static void tellMeAStory(const std::string &file, 
                                Toy &a, bool (Toy::*f1)(const std::string &), 
                                Toy &b, bool (Toy::*f2)(const std::string &));

	protected:
	private:
};

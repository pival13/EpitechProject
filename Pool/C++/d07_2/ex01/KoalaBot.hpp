/*
** EPITECH PROJECT, 2020
** cpp_d07a_2019 [WSL: Ubuntu]
** File description:
** KoalaBot
*/

#pragma once

#include "Parts.hpp"

class KoalaBot {
	public:
		KoalaBot(const std::string &name="Bob-01");
		~KoalaBot();

        void setParts(const Arms &part);
        void setParts(const Legs &part);
        void setParts(const Head &part);
        void swapParts(Arms &part);
        void swapParts(Legs &part);
        void swapParts(Head &part);
        bool status() const;
        void informations() const;
        
        const std::string string;

	protected:
	private:
        Arms _arm;
        Legs _leg;
        Head _head;
};

/*
** EPITECH PROJECT, 2020
** cpp_d16_2019 [WSL: Ubuntu]
** File description:
** DomesticKoala
*/

#pragma once

#include <iostream>
#include <vector>
#include "KoalaAction.hpp"
/*
class KoalaAction {
    void (std::string &);
};
*/
class DomesticKoala {
    using methodPointer_t = void (KoalaAction::*)(const std::string &);
	public:
		explicit DomesticKoala(KoalaAction &);
        DomesticKoala(const DomesticKoala &);
		~DomesticKoala();

        DomesticKoala &operator=(const DomesticKoala &);

        const std::vector<unsigned char> &getCommand() const;
        const std::vector<methodPointer_t> *getAction() const;
        const KoalaAction &getKoalaAction() const;
        void setKoalaAction(KoalaAction &);

        void learnAction(unsigned char command, methodPointer_t action);
        void unlearnAction(unsigned char command);
        void doAction(unsigned char command, const std::string &param);
        

	protected:
	private:
        KoalaAction _ka;
        std::vector<unsigned char> _char;
        std::vector<methodPointer_t> *_action;
};

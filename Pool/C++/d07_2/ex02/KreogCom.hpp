/*
** EPITECH PROJECT, 2020
** cpp_d07a_2019 [WSL: Ubuntu]
** File description:
** KreogCom
*/

#pragma once

#include <vector>
#include <iostream>

class KreogCom {
	public:
		KreogCom(int x, int y, int serial);
		~KreogCom();

        void addCom(int x, int y, int serial);
        void removeCom();
        KreogCom *getCom();

        void ping() const;
        void locateSquad() const;

	protected:
	private:
        const int m_serial;
        int pos[2];
        KreogCom *next;
};

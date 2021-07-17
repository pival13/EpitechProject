/*
** EPITECH PROJECT, 2020
** cpp_d07a_2019 [WSL: Ubuntu]
** File description:
** Parts
*/

#pragma once

#include <iostream>

class Parts {
    public:
        Parts(const std::string &part, const std::string &serial, bool functional);
        ~Parts();
        bool isFunctional() const;
        std::string serial() const;
        void informations() const;

		Parts &operator=(Parts const &p);

        std::string _name;
        bool _functional;
        const std::string _part;

    private:
};

class Arms : public Parts {
	public:
		Arms(const std::string &serial="A-01", bool functional=true);
		~Arms();

	protected:
	private:
};

class Legs : public Parts {
	public:
		Legs(const std::string &serial="L-01", bool functional=true);
		~Legs();

	protected:
	private:
};

class Head : public Parts {
	public:
		Head(const std::string &serial="H-01", bool functional=true);
		~Head();

	protected:
	private:
};

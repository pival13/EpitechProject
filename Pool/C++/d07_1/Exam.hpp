/*
** EPITECH PROJECT, 2020
** cpp_d07m_2019 [WSL: Ubuntu]
** File description:
** Exam
*/

#ifndef EXAM_H
#define EXAM_H

class Exam {
	public:
		Exam(bool *);
		~Exam();

        void (Exam::*kobayashiMaru)(int);
        static bool cheat;

        void start(int);
        bool isCheating();

	protected:
	private:
        bool *_cheat;
};

#endif
/*
** By Kevin Pruvost, June 2020
** File description:
** BottomTarget class.
*/

#pragma once

// Project includes
#include "BottomButton.hpp"

/**
 * @brief Target designed for bottom bar buttons.
 */
class BottomTarget
{
public:
	BottomTarget();
	~BottomTarget();

	BottomTarget & operator=(int i) { index = i; return *this; }
	BottomTarget & operator=(const std::string tN) { teamName = tN; return *this; }

public:
	std::string teamName;
	int index = 0;
};
/*
** By Kevin Pruvost, May 2020
** File description:
** Page class.
*/

#pragma once

// Project includes
#include "IPage.hpp"

enum PageId
{
	MENU_PAGE = 1,
	GAME_PAGE,
	TOTAL_PAGE
};

class Page : virtual public IPage
{
public:
	Page();
	~Page();
private:
};
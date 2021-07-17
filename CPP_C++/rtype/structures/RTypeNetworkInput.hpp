/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** RTypeNetworkInput
*/

#pragma once
/*
enum Movement {
	NOTHING = 0,
	TOP = 10,
	TOPRIGHT,
	TOPLEFT,
	RIGHT = 20,
	BOTTOM = 30,
	BOTRIGHT,
	BOTLEFT,
	LEFT = 30
};

enum Shoot {
	NOTHING = 0,
	BASIC = 10,
	ULTIMATE = 20
};
*/
struct RTypeNetworkInput {
	int moveX;
	int moveY;
	bool isShooting:1;
	bool useBomb:1;
};
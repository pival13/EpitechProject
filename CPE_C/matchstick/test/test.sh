#!/usr/bin/env bash
##
## EPITECH PROJECT, 2019
## test.sh
## File description:
## test of matchstick
##

color='\033[1;36m'
color2='\033[1;32m'
neutre='\033[0;m'

test()
{
    clear
    echo -e "${color}Test $1: ${color2}size $2 bloc $3${neutre}"
    cat $4 | ../matchstick $2 $3
    echo "Return value: $?"
    read
}

make re -C..

test "initial display" 4 5 "no_match"

test "lost of ia" 2 3 "match_lose"

test "win of ia" 2 3 "match_win"

test "invalid input" 2 3 "invalid_input"

test "your turn small" 4 5

test "your turn big" 8 10 

make fclean -C..
clear

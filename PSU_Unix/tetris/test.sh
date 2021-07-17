#!/usr/bin/env bash
##
## EPITECH PROJECT, 2019
## test
## File description:
## test
##

grey='\e[1;30m'
red='\e[1;31m'
green='\e[1;32m'
yellow='\e[1;33m'
blue='\e[1;34m'
pink='\e[1;35m'
cyan='\e[1;36m'
white='\e[1;37m'
back='\e[0m'

test_84()
{
    echo -e "${yellow}Test $1:\t${white}./tetris $2${back}"
    $3
    $5
    echo "q" | ./tetris $2 2> test
    if [ $? -eq 84 ]
    then
        echo -e "${green}OK${back}\n"
    else
        echo -e "${red}KO${back}\n" 
    fi
    $4
    $6
    sleep 1
}

test_TERM()
{
    echo -e "${yellow}Test $1:${back}"
    echo "q" | TERM=$2 ./tetris > test 2> test
    res=$?
    if [ $res -eq 0 ]; then
        echo -e "${green}OK${back}\n"
    elif [ $res -eq 84 ] && [ "$2" == "''" ]; then
        echo -e "${green}OK${back}\n"
    else
        echo -e "${red}KO${back}\n" 
    fi
    sleep 1
}

test_TERM_empty()
{
    echo -e "${yellow}Test $1:${back}"
    echo "q" | TERM=$2 ./tetris > test 2> test
    res=$?
    if [ $res -eq 84 ]; then
        echo -e "${green}OK${back}\n"
    else
        echo -e "${red}KO${back}\n" 
    fi
    sleep 1
}

test_env()
{
    echo -e "${yellow}Test $1:${back}"
    echo "q" | env -i ./tetris 2> test
    if [ $? -eq 84 ]; then
        echo -e "${green}OK${back}\n"
    else
        echo -e "${red}KO${back}\n" 
    fi
    sleep 1
}

test_error()
{
    echo -e "${yellow}Test $1:${back}"
    cp "bonus/$2" "tetriminos/$2"
    echo "q" | ./tetris -D | grep Error > test
    if [ $? -eq 0 ]; then
        echo -e "${green}OK${back}\n"
    else
        echo -e "${red}KO${back}\n" 
    fi
    rm -f "tetriminos/$2"
    sleep 1
}

test_tetrimino()
{
    echo -e "${yellow}Test $1:${back}"
    cp "bonus/$2.tetrimino" "tetriminos/$2.tetrimino"
    echo "q" | ./tetris -D | grep "Name $2 :" > test
    if [ $? -eq 0 ]; then
        echo -e "${green}OK${back}\n"
    else
        echo -e "${red}KO${back}\n" 
    fi
    rm -f "tetriminos/$2.tetrimino"
    sleep 1
}

make
clear

echo -e "${pink}\tBad Parameters\n${back}"
test_84 "Missing key" "--key-left="
test_84 "Unknow option" "-l z -d e -a f"
test_84 "Bad use of simple option" "-l=r"
test_84 "Missing '--'" "key-left"

echo -e "${pink}\tRead Tetriminos\n${back}"
test_error "Too big piece" "big.tetrimino"
test_error "Without piece" "empty.tetrimino"
test_error "Error tetrimino 1" "1.tetrimino"
test_error "Error tetrimino 2" "2.tetrimino"
test_error "Error tetrimino 3" "3.tetrimino"
test_error "Error tetrimino 4" "4.tetrimino"
test_error "Error tetrimino 5" "5.tetrimino"
test_error "Error tetrimino 6" "6.tetrimino"
test_tetrimino "Filename .h.tetrimino" ".h"
test_tetrimino "Filename .tetrimino" ""
test_tetrimino "Filename .tetrimino.tetrimino" ".tetrimino"
test_tetrimino "Filename a.tetrimino.b.tetrimino" "a.tetrimino.b"
test_84 "File not a tetrimino" "" "mv bonus/file tetriminos/file" "mv tetriminos/file bonus/file"
#test_tetrimino "Only 1 tetrimino" #"tetriminos" "tetrimino"
#test_tetrimino "Only 1 tetrimino without '\\\\n'" #"tetriminos" "tetrimino"
test_84 "Without tetriminos directory" "" "mv tetriminos tetrimino" "mv tetrimino tetriminos"
test_84 "Empty folder tetriminos" "" "mv tetriminos ./tetrimino" "rm -rf tetriminos" "mkdir tetriminos" "mv tetrimino tetriminos"

echo -e "${pink}\tRead capacities\n${back}"
test_TERM_empty "Without TERM" ""
test_TERM "With TERM vt200" "vt200"
test_TERM "With TERM vt52" "vt52"
test_TERM "With TERM vterm" "vterm"
test_TERM "With TERM xterm" "xterm"
test_env "Without env"

rm test
make fclean
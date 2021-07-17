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

test_asm()
{
    echo -e "${cyan}Test bytecode of $1.s${back}"
    ./assembler tests/$1.s > test
    if [ $? -eq 0 ]; then
        hexdump -C $1.cor > test
        hexdump -C tests/correct/$1.cor > test2
        diff test test2
        if [ $? -eq 0 ]; then
            echo -e "${green}OK\n${back}"
        else
            echo -e "${red}KO\n${back}"
        fi
    else
        echo -e "${red}KO\n${back}"
    fi
    rm -f test test2 $1.cor
}

test_error()
{
    echo -e "${cyan}Test $1${back}"
    ./assembler tests/$2 > test
    if [ $? -eq 84 ]; then
        echo -e "${green}OK\n${back}"
    else
        echo -e "${red}KO\n${back}"
    fi
    rm -f test $2.cor
}

test_funct()
{
    echo -e "${cyan}Test $1${back}"
    ./assembler tests/$2 > test
    if [ $? -eq 0 ]; then
        echo -e "${green}OK\n${back}"
    else
        echo -e "${red}KO\n${back}"
    fi
    rm -f test $2.cor
}

make assembler
if [ $? != 0 ]; then
    exit
fi
clear

echo -e "${yellow}\tTest assemblage\n${back}"
test_asm tyron
test_asm bill
test_asm abel
test_asm pdd

echo -e "${yellow}\tTest functional\n${back}"
test_funct "with a comment on file" error10
test_funct "with only header" only_header
test_funct "with complex label" label
test_funct "with a comment at end of a command" comment_on_line
test_funct "with negativ number" negativ_number
test_funct "only label on the line" label_alone

echo -e "${yellow}\tTest error\n${back}"
test_error "not existing file" erro
test_error "no .name" error1
test_error "too much .name" error7
test_error "no .comment" error
test_error "too much .comment" error8
test_error "unknow label" error2
test_error "same label" error21
test_error "unknow function" error3
test_error "not enough parameters" error4
test_error "too much parameters" error5
test_error "bad type of parameters" error6
test_error "forbid characters on label" error9
test_error "empty file" empty
test_error "no cote in .name" error11
test_error "no cote .comment" error12
test_error "char after cote in .name" error13
test_error "char after cote in .comment" error14
test_error "char before cote in .name" error15
test_error "char before cote in .comment" error16
test_error "cote inside cote in .name" error18
test_error "cote inside cote in .comment" error17
test_error "too long .name" error19
test_error "too long .comment" error20

#make fclean 
#!/bin/bash

grey='\e[1;30m'
red='\e[1;31m'
green='\e[1;32m'
yellow='\e[1;33m'
blue='\e[1;34m'
pink='\e[1;35m'
cyan='\e[1;36m'
white='\e[1;37m'
back='\e[0m'

test_funct() # funct file
{
    echo -e "${cyan}Test $2${back}"
    funct="$1"
    shift
    ./my_$funct "$@" > my
    if [ "$funct" == "objdump" ]; then
        $funct -sf "$@" > correct
    else
        $funct "$@" > correct
    fi
    diff my correct
    if [ $? -eq 0 ]; then
        echo -e "${green}OK\n${back}"
        rm -f my correct $1.cor
    else
        echo -e "${red}KO\n${back}"
    fi
}

if [ $# -lt 2 ]; then
    echo "USAGE ./test.sh [nm|objdump] [test file ...]"
    exit
fi

make
test_funct "$@"
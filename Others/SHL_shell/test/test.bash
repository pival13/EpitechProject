#!/bin/bash

red='\e[1;31m'
green='\e[1;32m'
back='\e[0m'
cyan='\e[1;36m'

echo -e "${red}Functional test${back}"

test_error_create ()
{
    echo -e "${cyan}$1${back}"
    ../bdsh $1 > $2
    if [ ! -f $2 ] && [ $? -eq 1 ]; then
        echo -e "${red}KO\n${back}"
    else
        diff $2 $3
        if [ $? -eq 0 ]; then
            echo -e "${green}OK\n${back}"
        else
            echo -e "${red}KO\n${back}"
        fi
    fi
}

test_usage ()
{   
    echo -e "\n${cyan}Print usage${back}"
    ../bdsh $1 > testfile
    diff testfile $2
    if [ $? -eq 0 ]; then
        echo -e "${green}OK\n${back}"
    else
        echo -e "${red}KO\n${back}"
    fi

}

test_error_insert ()
{
    echo -e "${cyan}$1${back}"
    ../bdsh $1
    if [ $? -eq 0 ]; then
        diff $2 $3
        if [ $? -eq 0 ]; then
            echo -e "${green}OK\n${back}"
        else
            echo -e "${red}KO\n${back}"
        fi
    else
        echo -e "${red}KO\n${back}"
    fi
    cat .test.json > test4.json
}

test_error_describe ()
{
    echo -e "${cyan}$1${back}"
    ../bdsh $1 > testfile
    if [ $? -eq 0 ]; then
        diff testfile $3
        if [ $? -eq 0 ]; then
            echo -e "${green}OK\n${back}"
        else
            echo -e "${red}KO\n${back}"
        fi
    else
        echo -e "${red}KO\n${back}"
    fi
    rm testfile
}

test_error_select ()
{
    echo -e "${cyan}$1${back}"
    ../bdsh $1 > testfile
    if [ $? -eq 0 ]; then
        diff testfile $3
        if [ $? -eq 0 ]; then
            echo -e "${green}OK\n${back}"
        else
            echo -e "${red}KO\n${back}"
        fi
    else
        echo -e "${red}KO\n${back}"
    fi
    rm testfile
}

test_error_update ()
{
    echo -e "${cyan}$1${back}"
    ../bdsh $1
    if [ $? -eq 0 ]; then
        diff $2 $3
        if [ $? -eq 0 ]; then
            echo -e "${green}OK\n${back}"
        else
            echo -e "${red}KO\n${back}"
        fi
    else
        echo -e "${red}KO\n${back}"
    fi
    cat .test.json > test5.json
}

test_error_delete ()
{
    echo -e "${cyan}$1${back}"
    ../bdsh $1
    if [ $? -eq 0 ]; then
        diff $2 $3
        if [ $? -eq 0 ]; then
            echo -e "${green}OK\n${back}"
        else
            echo -e "${red}KO\n${back}"
        fi
    else
        echo -e "${red}KO\n${back}"
    fi
    cat .test.json > test5.json
}

test_usage "-h" "test_usage"

echo -e "${cyan}Test command create:${back}"
test_error_create "-f test1.json create database" "test1.json" ".test1.json"
test_error_create "-f test2.json create table user id,firstname,lastname" "test2.json" ".test2.json"
test_error_create "-f test3.json create table age id,age" "test3.json" ".test3.json"

echo -e "${cyan}\nTest command insert:${back}"
test_error_insert "-f test4.json insert user id=9999,firstname=Archi,lastname=ESTGENIAL" "test4.json" ".test4.json"

echo -e "${cyan}\nTest command describe:${back}"
test_error_describe "-f test5.json describe user" "test5.json" ".test5.json"

echo -e "${cyan}\nTest command select:${back}"
test_error_select "-f test5.json select user firstname,lastname" "test5.json" ".test6.json"

echo -e "${cyan}\nTest command where:${back}"
test_error_select "-f test5.json select user firstname,id where lastname=SMITH" "test5.json" ".test7.json"

echo -e "${cyan}\nTest command update:${back}"
test_error_update "-f test5.json update user firstname=Marry where firstname=John" "test5.json" ".test8.json"

echo -e "${cyan}\nTest command delete:${back}"
test_error_delete "-f test5.json delete user where lastname=SMITH" "test5.json" ".test9.json"
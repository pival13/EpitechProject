#!/usr/bin/env bash
##
## EPITECH PROJECT, 2018
## error handling
## File description:
## handle wrong map
##

make multi -C..

echo
echo "Test 1: No Player"
../my_sokoban map/without_player
if [ $? -eq 84 ]
then
    echo "OK"
else
    echo "KO, the ouput should be 84 but it was" $?
fi

echo
echo "Test 2: Two Player"
../my_sokoban map/with_two_players
if [ $? -eq 84 ]
then
    echo "OK"
else
    echo "KO, the ouput should be 84 but it was" $?
fi

echo
echo "Test 3: Without goal"
../my_sokoban map/without_goal
if [ $? -eq 84 ]
then
    echo "OK"
else
    echo "KO, the ouput should be 84 but it was" $?
fi

echo
echo "Test 4: With too many boxes"
../my_sokoban map/with_too_many_boxes
if [ $? -eq 84 ]
then
    echo "OK"
else
    echo "KO, the ouput should be 84 but it was" $?
fi


echo
echo "Test 5: With not enough boxes"
../my_sokoban map/with_not_enough_boxes
if [ $? -eq 84 ]
then
    echo "OK"
else
    echo "KO, the ouput should be 84 but it was" $?
fi

echo
echo "Test 6: Without file"
../my_sokoban
if [ $? -eq 84 ]
then
    echo "OK"
else
    echo "KO, the ouput should be 84 but it was" $?
fi

echo
echo "Test 7: Empty file"
../my_sokoban map/empty_file
if [ $? -eq 84 ]
then
    echo "OK"
else
    echo "KO, the ouput should be 84 but it was" $?
fi

echo
echo "Test 8: With unknow character"
../my_sokoban error_handling.sh
if [ $? -eq 84 ]
then
    echo "OK"
else
    echo "KO, the ouput should be 84 but it was" $?
fi

echo
echo "Test 9: Not existing file"
../my_sokoban happy_birthday
if [ $? -eq 84 ]
then
    echo "OK"
else
    echo "KO, the ouput should be 84 but it was" $?
fi

echo
echo "Test 10: Print usage"
../my_sokoban -h | if [ $? -eq 0 ]
then
    echo "OK"
else
    echo "KO, the ouput should be 0 but it was" $?
fi

echo
echo "Test 11: Put box on a target"
echo "q" | ../my_sokoban map/1
if [ $? -eq 0 ]
then
    echo "OK"
else
    echo "KO, the ouput should be 0 but it was" $?
fi

echo
echo "Test 12: Put box on a corner"
echo "z" | ../my_sokoban map/2
if [ $? -eq 1 ]
then
    echo "OK"
else
    echo "KO, the ouput should be 1 but it was" $?
fi

echo
make fclean -C..

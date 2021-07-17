#!/usr/bin/env bash
##
## EPITECH PROJECT, 2018
## test
## File description:
## test bash of pushswap
##

make bonus && clear

echo "Little list: "
echo "1 4 -3 3"
sleep 3
./push_swap -v 1 4 -3 3

time ./push_swap 1 4 -3 3

sleep 3
echo

clear

echo "Sort list: "
echo $(cat tests/sort)
sleep 3
./push_swap -v $(cat tests/sort)

time ./push_swap $(cat tests/sort)

sleep 3
echo

clear

echo "Sort list but rotate: "
echo $(cat tests/almost_sort)
sleep 3
./push_swap -v $(cat tests/almost_sort)

time ./push_swap $(cat tests/almost_sort)

sleep 3
echo

clear

echo "Almost sort list: "
echo $(cat tests/almost_sort_2)
sleep 3
./push_swap -v $(cat tests/almost_sort_2)

time ./push_swap $(cat tests/almost_sort_2)

sleep 3
echo

clear

echo "Unsort list: "
echo $(cat tests/unsort)
sleep 3
./push_swap -v $(cat tests/unsort)

time ./push_swap $(cat tests/unsort)

sleep 3
echo

clear

echo "One number: "
echo "0"
sleep 3
./push_swap -v 0

time ./push_swap 0

sleep 3
echo

clear

echo "list of 1,000 numbers"
sleep 3

time ./push_swap $(cat tests/1000_nb)

sleep 3
echo

clear

echo "list of 5,000 numbers"
sleep 3

time ./push_swap $(cat tests/5000_nb)

sleep 3
echo

clear

echo "list of 10,000 numbers"
sleep 3

time ./push_swap $(cat tests/10000_nb)

sleep 3
echo

clear && make fclean && clear

#!/usr/bin/env bash
##
## EPITECH PROJECT, 2019
## test.sh
## File description:
## test getnextline
##

Test()
{
    gcc -I.. -DREAD_SIZE=$3 $1 ../get_next_line.c
    test=$(strace ./a.out)
    sol=$2
    if [ "$test" = "$sol" ]
    then
        echo "OK"
    else
        echo "$test"
    fi
}

echo "Reading the four first line"

Test main.c "#!/usr/bin/env bash
##
## EPITECH PROJECT, 2019
## test.sh" 100

echo "Reading only the third line"

Test main1.c "## EPITECH PROJECT, 2019" 100

echo "Reading a small file"

Test main2.c "$(cat test.sh)" 100

echo "Reading a big file"

Test main3.c "$(cat ../get_next_line.c)" 100

echo "Read_size of 1 with one line"

Test main1.c "## EPITECH PROJECT, 2019" 1

echo "Read_size of 100000 with one line"

Test main1.c "## EPITECH PROJECT, 2019" 100000

#!/usr/bin/env bash
##
## EPITECH PROJECT, 2019
## test.sh
## File description:
## test getnextline
##

Test()
{
    echo -e "\e[1;33m$1\e[0m"
    gcc -I.. -DREAD_SIZE=$4 $2 ../get_next_line.c
    test=$(./a.out)
    sol=$3
    if [ "$test" = "$sol" ]
    then
        echo "OK"
    else
        echo "$test"
    fi
    read
    echo
}

Test "Reading the four first line" main.c "#!/usr/bin/env bash
##
## EPITECH PROJECT, 2019
## test.sh" 100

Test "Reading only the third line" main1.c "## EPITECH PROJECT, 2019" 100

Test "Reading a small file" main2.c "$(cat test.sh)" 100

Test "Reading a big file" main3.c "$(cat ../get_next_line.c)" 100

Test "Read_size of 1 with one line" main1.c "## EPITECH PROJECT, 2019" 1

Test "Read_size of 100000 with one line" main1.c "## EPITECH PROJECT, 2019" 100000

rm a.out

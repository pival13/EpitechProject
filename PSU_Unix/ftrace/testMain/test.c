/*
** EPITECH PROJECT, 2020
** ftrace [WSL: Ubuntu]
** File description:
** test
*/

#include <stdio.h>
#include <stdlib.h>
#include <libelf.h>

void toto()
{
    printf("Je suis dans toto()\n");
}

void titi()
{
    printf("Je suis dans titi()\n");
}

int main()
{
    printf("%p\n", &main);
    toto();
    titi();
    sleep(10);
    exit(0);
}
/*
** EPITECH PROJECT, 2019
** test_printf
** File description:
** test my printf
*/

#include "my.h"
#include "lemin.h"
#include <stdlib.h>
#include <criterion/criterion.h>

Test(printf, printf)
{
    my_printf("Hello World, %s are you? %d %d number\n", "how", 23, 12343);
}

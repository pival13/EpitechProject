/*
** EPITECH PROJECT, 2019
** functions 1 test
** File description:
** tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdio.h>
#include "my.h"

void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(tests, isneg_test, .init = redirect_all_stdout)
{
    cr_assert_eq(my_strlen("coucou"), 6);
    cr_assert_eq(my_strcpy("coucou"), "coucou");
    cr_assert_eq(my_strcmp("coucou", "coucou"), 0);
    cr_assert_eq(my_strcmp("toto", "et tata"),"toto", "et tata" );
    cr_assert_eq(my_pow(2, 2), 4);
    cr_asser_eq(my_getnbr("1234"), 1234);
}

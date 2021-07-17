/*
** EPITECH PROJECT, 2018
** test
** File description:
** test my_printf 2
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

int my_printf(char *, ...);

Test(my_printf, test_pointeur, .init = cr_redirect_stdout)
{
    my_printf("%p, %p, %p, %p, %p, %p", 100, 1000000000000000, 887, 986543, \
-3456, 34567876543);
    cr_assert_stdout_eq_str("0x64, 0x38d7ea4c68000, 0x377, 0xf0daf, \
0xfffff280, 0x80c67efbf");
}

Test(my_printf, test_unknow, .init = cr_redirect_stdout)
{
    my_printf("%%d, %%%d, %k", 9);
    cr_assert_stdout_eq_str("%d, %9, %k");
}

Test(my_printf, test_float, .init = cr_redirect_stdout)
{
    my_printf("%f, %f, %f, %f", 123.0, 12362736842.563783, 485.56424732, 213);
    cr_assert_stdout_eq_str("123.000000, 12362736842.563783, 485.564247, \
0.000000");
}

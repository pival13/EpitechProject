/*
** EPITECH PROJECT, 2018
** test
** File description:
** test my_printf
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

int my_printf(char *, ...);

Test(my_printf, easy_test, .init = cr_redirect_stdout)
{
    my_printf("This is a test\0");
    cr_assert_stdout_eq_str("This is a test");
}

Test(my_printf, test_char_string, .init = cr_redirect_stdout)
{
    my_printf("Hello %s world.\n%s%s %s%c %S", "my dear", "How", " are", \
"you", '?', "That's beautifull\n");
    cr_assert_stdout_eq_str("Hello my dear world.\nHow are you? That's \
beautifull\\012");
}

Test(my_printf, test_signed_int, .init = cr_redirect_stdout)
{
    my_printf("%d, %d, %d, %i, %d, %d, %i, %d, %d, %i, %d, %d, %d, %d", 0, \
1, 10, 123456789, -1, -10, -123456789, 2147483646, 2147483647, 2147483648, \
2147483649, -2147483647, -2147483648, -2147483649);
    cr_assert_stdout_eq_str("0, 1, 10, 123456789, -1, -10, -123456789, \
2147483646, 2147483647, -0, -2147483647, -2147483647, -0, 2147483647");
}

Test(my_printf, test_unsigned_int, .init = cr_redirect_stdout)
{
    my_printf("%u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u", 0, \
1, 10, 123456789, -1, -10, -123456789, 4294967295, 2147483647, 2147483648, \
4294967294, 4294967296, -2147483648, -4294967295);
    cr_assert_stdout_eq_str("0, 1, 10, 123456789, 4294967295, 4294967286, \
4171510507, 4294967295, 2147483647, 2147483648, 4294967294, 0, 2147483648, 1");
}

Test(my_printf, test_base_int, .init = cr_redirect_stdout)
{
    my_printf("%b, %b, %b, %o, %o, %o, %x, %x, %X, %X\0", 214, -1, 2147483647, \
214, -1, 2147483647, 214, 100, 2147483647, -1);
    cr_assert_stdout_eq_str("11010110, 11111111111111111111111111111111, \
1111111111111111111111111111111, 326, 37777777777, 17777777777, d6, 64, \
7FFFFFFF, FFFFFFFF");
}

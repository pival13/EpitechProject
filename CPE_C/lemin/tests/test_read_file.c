/*
** EPITECH PROJECT, 2019
** test_read_file
** File description:
** test read_file
*/

#include <criterion/criterion.h>
#include "my.h"
#include "lemin.h"
#include <stdlib.h>

Test(read_file, read_a_file)
{
    char **buff = read_file("toto");

    cr_assert_null(buff);
    buff = read_file("../main.c");
    cr_assert_not_null(buff);
}
/*
Test(read_file, read_terminal)
{
    char **buff = read_file(NULL);

    cr_assert_not_null(buff);
}

*/

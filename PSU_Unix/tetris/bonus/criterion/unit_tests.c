/*
** EPITECH PROJECT, 2019
** tests.c
** File description:
** tests criterion
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/my.h"
#include "../include/tetris.h"

char *load_file_in_mem(char const *filepath)
{
    struct stat *statbuff = malloc(sizeof(struct stat));
    int size = 0;
    char *buffer = 0;
    int fd;

    stat(filepath, statbuff);
    size = statbuff->st_size;
    buffer = malloc(sizeof(char) * (size + 1));
    fd = open(filepath, O_RDONLY);
    if (read(fd, buffer, size) == (-1))
        return (NULL);
    buffer[size] = 0;
    free(statbuff);
    close(fd);
    return (buffer);
}

void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

test1(tests, display_test1)
{
    char *result = load_file_in_mem("./criterion/result1");
    int ac = 2;
    char **av = {"./tetris", "-D"};

    cr_assert_eq(main(ac, av), result);
    free(result);
}

test2(tests, display_test2)
{
    char *result = load_file_in_mem("./criterion/result2");
    int ac = 2;
    char **av = {"./tetris", "-D"};

    cr_assert_eq(main(ac, av), result);
    free(result);
}

test3(tests, display_test3)
{
    char *result = load_file_in_mem("./criterion/result3");
    int ac = 2;
    char **av = {"./tetris", "-D"};

    cr_assert_eq(main(ac, av), result);
    free(result);
}

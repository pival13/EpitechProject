/*
** EPITECH PROJECT, 2018
** get_next_line
** File description:
** return the line
*/

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int strlength(char *str)
{
    int i = 0;

    if (str == NULL)
        return (0);
    for (; str[i] != '\0'; i++);
    return (i);
}

char *strconcat(char *dest, char *src)
{
    int i = strlength(dest);
    int j = strlength(src);

    for (int k = 0; k != j; k++)
        dest[i+k] = src[k];
    dest[i+j] = '\0';
    return (dest);
}

int get_next_line3(char ***str, int a, char **result, char (*mem)[100+1])
{
    *result = malloc(sizeof(char) * (strlength(*mem) \
+ strlength(str[0][1]) + strlength(str[0][0])) + 1);
    if (*result == NULL) return (-1);
    *result[0] = '\0';
    *result = strconcat(*result, *mem);
    *mem[0] = '\0';
    for (int i = 0; i < a; i++)
        if (str[0][0][i] == '\n') {
            strconcat(*mem, &str[0][0][i+1]);
            str[0][0][i] = '\0';
            a = -1;
        }
    *result = strconcat(*result, str[0][1]);
    *result = strconcat(*result, str[0][0]);
    free(str[0][1]);
    free(str[0][0]);
    str[0][1] = *result;
    return (a);
}

char *get_next_line2(char (*mem)[100+1], char **result, int fd)
{
    char **str = malloc(sizeof(char *) * 2);
    int a = 0;

    if (str == NULL) return (NULL);
    str[1] = NULL;
    while (a != -1) {
        str[0] = malloc(sizeof(char) * 100 + 1);
        if (str[0] == NULL) return (NULL);
        a = read(fd, str[0], 100);
        if (a <= 0) {
            *mem[0] = '\0';
            free(str[0]);
            free(str);
            return (*result);
        }
        str[0][a] = '\0';
        a = get_next_line3(&str, a, result, mem);
    }
    free(str);
    return (*result);
}

char *get_next_line(int fd)
{
    char *result = NULL;
    static char mem[100+1] = "\0";

    if (fd < 0) return (NULL);
    for (int i = 0; mem[i] != '\0'; i++)
        if (mem[i] == '\n') {
            result = malloc(sizeof(char) * strlength(mem) + 1);
            if (result == NULL) return (NULL);
            result[0] = '\0';
            result = strconcat(result, mem);
            mem[0] = '\0';
            strconcat(mem, &result[i+1]);
            result[i] = '\0';
            return (result);
        }
    return (get_next_line2(&mem, &result, fd));
}

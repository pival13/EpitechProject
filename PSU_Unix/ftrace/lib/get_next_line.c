/*
** EPITECH PROJECT, 2019
** get_next_line
** File description:
** get the next line
*/

#include <stdlib.h>
#include <unistd.h>

static int have_line(char *str)
{
    for (int i = 0; str && str[i]; i++)
        if (str[i] == '\n')
            return (1);
    return (0);
}

static char *concat(char *s1, char *s2)
{
    int size[2] = {0, 0};
    char *str;

    if (!s1 && (!s2 || !s2[0]))
        return (NULL);
    for (; s1 && s1[size[0]]; size[0]++);
    for (; s2 && s2[size[1]]; size[1]++);
    str = malloc(sizeof(char) * (size[0]+size[1]+1));
    for (int i = 0; str && i < size[0]; i++)
        str[i] = s1[i];
    for (int i = 0; str && i < size[1]; i++)
        str[size[0]+i] = s2[i];
    if (str)
        str[size[0]+size[1]] = '\0';
    if (s1)
        free(s1);
    return (str);
}

static char *read_more(int fd, char *mem)
{
    char *str = concat(NULL, mem);
    char buff[1001] = {0};

    while (!have_line(str)) {
        if (read(fd, buff, 1000) <= 0) {
            mem[0] = 0;
            return (str);
        }
        str = concat(str, buff);
    }
    for (int i = 0; str[i]; i++)
        if (str[i] == '\n') {
            for (int j = 0; str[i] == '\n' && str[i+j+1]; j++) {
                mem[j] = str[i+j+1];
                mem[j+1] = '\0';
            }
            str[i] = '\0';
            break;
        }
    return (str);
}

char *get_next_line(int fd)
{
    static char mem[1001] = {0};
    int i = 0;
    char *str;
    int j = 0;

    if (fd == -1)
        return (NULL);
    if (!have_line(mem))
        return (read_more(fd, mem));
    for (; mem[i] != '\n'; i++);
    str = malloc(sizeof(char) * (i+1));
    for (; str && j != i; j++) {
        str[j] = mem[j];
    }
    str[j] = '\0';
    for (j = 0; str && j != i+1; j++)
        for (int k = 0; mem[k]; k++)
            mem[k] = mem[k+1];
    return (str);
}

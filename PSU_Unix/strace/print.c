/*
** EPITECH PROJECT, 2020
** PSU_strace_2019 [WSL: Ubuntu]
** File description:
** print
*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/ptrace.h>

void my_printf(char *s, ...);

void display_nb(size_t a, char *format, bool display)
{
    char s[21] = {0};

    if (display)
        sprintf(s, format, a);
    else
        sprintf(s, "0x%lx", a);
    my_printf(s);
}

void display_string(size_t pid, size_t a, bool display)
{
    char s[50] = {0};

    if (!display && a == 0) {
        my_printf("0x0");
        return;
    } else if (!display) {
        sprintf(s, "%p", (void *)a);
        my_printf(s);
        return;
    }
    s[0] = '\"';
    for (int i = 0; i != 48; i++) {
        s[i+1] = (char)ptrace(PTRACE_PEEKTEXT, pid, a+i, NULL);
        if (s[i+1] == 0) {
            s[i+1] = '\"';
            break;
        } else if (i == 47)
            strcpy(s+45, "\"...");
    }
    my_printf(s);
}

void display_pointer(size_t a, bool display)
{
    char s[20] = {0};

    if (a == 0 && display)
        strcpy(s, "NULL");
    else if (!display && a == 0)
        strcpy(s, "0x0");
    else
        sprintf(s, "%p", (void *)a);
    my_printf(s);
}

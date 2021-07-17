/*
** EPITECH PROJECT, 2019
** minishell.h
** File description:
** header of minishell
*/

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>
#include <limits.h>

#ifndef MINISHELL_H_
#define MINISHELL_H_

#ifndef BLACK
#define BLACK "\e[1;30m"
#endif
#ifndef RED
#define RED "\e[1;31m"
#endif
#ifndef GREEN
#define GREEN "\e[1;32m"
#endif
#ifndef YELLOW
#define YELLOW "\e[1;33m"
#endif
#ifndef BLUE
#define BLUE "\e[1;34m"
#endif
#ifndef ROSE
#define ROSE "\e[1;35m"
#endif
#ifndef CYAN
#define CYAN "\e[1;36m"
#endif
#ifndef WHITE
#define WHITE "\e[1;37m"
#endif
#ifndef RESET
#define RESET "\e[0m"
#endif

typedef struct arg_s {
    char **arg;
    char link;
    struct arg_s *input;
    struct arg_s *output;
    struct arg_s *next;
} arg_t;

typedef struct shell_s {
    char **env;
    char **arr;
    arg_t *arg;
    int in_pid[2];
    int out_pid[2];
    int status;
    int nb_process;
} shell_t;

char **get_var_env(char **env, char *var);
void minishell(shell_t *);
void get_arg(shell_t *);
void execute(shell_t *);
void make_pipe(shell_t *);
void free_arg(shell_t *);

void my_close(int *fd);
void add_var(shell_t *, char *name, char *var);
void del_var(shell_t *, char *name);
char *get_home(char **env);
char *get_oldpwd(char **env);

void my_cd(shell_t *);
void my_exit(shell_t *);
void my_env(shell_t *);
void my_setenv(shell_t *);
void my_unsetenv(shell_t *);

#endif

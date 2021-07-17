/*
** EPITECH PROJECT, 2019
** asm.h
** File description:
** asm.h
*/

#ifndef ASM_H
#define ASM_H

typedef struct asm_s {
    struct asm_s *next;
    struct asm_s *prev;
    char **param;
    char *arg;
    char *label;
    int other;
    int size;
} asm_t;

asm_t *parsing(char **tab);
asm_t *initialize(void);
char **space_gestion(char **tab, int i, int j);
char **delete_bad_character(char **tab, int i, int j);
char *my_strcpy_not_unsigned(char const *src);
char *cpy_label(char *str);
char *cpy_com(char *str);
char *delete_chara(char *str, int j);
int verify_string(asm_t *save, char *string, int len);
int verify_cote(asm_t *list, int a, char *string, int len);
int verify_len_name(asm_t *save, int len);
int print_probleme(void);
int invalid_label_parameters(asm_t *com, int i, int j);
int my_strcmp_n(char *str, char *str2, int j);
int verify_word(char *str);
int count_word(char *str);
int find_size_asm(asm_t *command);
int return_fd(char *str);
int labcheck(char *str, asm_t *com);
int my_lablen(char *str, int i);
void rev_list(asm_t **list);
void label(asm_t *r, char *str);
void com(asm_t *r, char *str);

//check

int condition_check_file(asm_t *commands, int check, op_t *opstruct);
int condition_checks_params(int i, int check, asm_t *com, op_t op);
int check_mnemonique(int check, asm_t *commands, op_t *opstruct);
int check_struct(asm_t *commands, op_t *opstruct, int i);
int check_this_param(asm_t *com, int i, int j, op_t op);
int condition_check_label(asm_t *list, asm_t *mem);
int check_file(asm_t *commands);
int check_header(asm_t *);

//print

void print_label(int fd, asm_t *list, char *label, int size);
void print_nb(int fd, unsigned int nb, int nb_bytes);
void print_type(int fd, char **file);

//instruction

void asm_zjmp_fork(op_t op, asm_t *, int fd);
void asm_funct(op_t op, asm_t *, int fd);
void asm_live(op_t op, asm_t *, int fd);
void asm_ldi(op_t op, asm_t *, int fd);
void asm_sti(op_t op, asm_t *, int fd);
void asm_header(int fd, asm_t *);
void assembler(asm_t *, char *);

#endif

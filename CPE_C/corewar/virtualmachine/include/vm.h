/*
** EPITECH PROJECT, 2019
** vm.h
** File description:
** vm.h
*/

#ifndef VM_H
#define VM_H

typedef struct champ_s {
    unsigned char *name;
    unsigned char *reg;
    int nb;
    int pc;
    int n_option;
    int cycle;
    int a_option;
    char carry;
    char live;
} champ_t;

typedef struct vm_s {
    champ_t *champion;
    unsigned char *memory;
    int dump;
    int live;
    int last_live;
    int cycle;
    int timer;
    int r;
    int nb_champion;
} virtualmachine_t;

void create_vm(int ac, char **av, virtualmachine_t **vm);
int h_function(void);
int find_size_vm(unsigned char *mem, int pc);
void virtualmachine(virtualmachine_t *vm);
int create_champ(virtualmachine_t *vm, int ac, char **av);

//verification_file_binary_and_argument

int condition_get_opt(virtualmachine_t *vm, char **av, int a, int i);
int check_bin(op_t op, virtualmachine_t *vm, int champ);
int check_argument(char **av, int a);

//check end game

int nb_alive(virtualmachine_t *vm);
int kill_champ(virtualmachine_t *vm);

//dump_option

void dump_corewar(virtualmachine_t *vm);
int dump_condition(virtualmachine_t *vm, char **av, int a);
int dump_option(int ac, char **av, virtualmachine_t *vm);

//get_information

unsigned int get_bytes(unsigned char *mem, int start, int size);
unsigned int get_value(virtualmachine_t *vm, int player, int nb_param);
unsigned int get_lvalue(virtualmachine_t *vm, int player, int nb_param);
int get_opt(int ac, char **av, virtualmachine_t *vm);
void set_bytes(unsigned char *mem, unsigned int nb, int start, int size);
void set_value(virtualmachine_t *vm, int player, int nb_param, \
unsigned int nb);
void set_lvalue(virtualmachine_t *vm, int player, int nb_param, \
unsigned int nb);
int get_type(int size, int nb);

//instruction

void vm_live(op_t, virtualmachine_t *, int);
void vm_ld(op_t, virtualmachine_t *, int);
void vm_st(op_t, virtualmachine_t *, int);
void vm_add(op_t, virtualmachine_t *, int);
void vm_sub(op_t, virtualmachine_t *, int);
void vm_and(op_t, virtualmachine_t *, int);
void vm_or(op_t, virtualmachine_t *, int);
void vm_xor(op_t, virtualmachine_t *, int);
void vm_zjmp(op_t, virtualmachine_t *, int);
void vm_ldi(op_t, virtualmachine_t *, int);
void vm_sti(op_t, virtualmachine_t *, int);
void vm_fork(op_t, virtualmachine_t *, int);
void vm_lld(op_t, virtualmachine_t *, int);
void vm_lldi(op_t, virtualmachine_t *, int);
void vm_lfork(op_t, virtualmachine_t *, int);
void vm_aff(op_t, virtualmachine_t *, int);
void end_corewar(virtualmachine_t *vm);

//free

void free_champion_error(virtualmachine_t **vm);
void free_registre_error(virtualmachine_t **vm, int i);
void free_create_champ_error(virtualmachine_t **vm);
void free_vm(virtualmachine_t *vm);

#endif

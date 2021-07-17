/*
** EPITECH PROJECT, 2020
** PSU_nmobjdump_2019 [WSL: Ubuntu]
** File description:
** elf_reader
*/

#ifndef _ELF_READER_H
#define _ELF_READER_H

#include <elf.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <stdbool.h>
#include <errno.h>
#include "lib/generic_list.h"

#ifndef ARCH
    #define ARCH 64
#endif
#if ARCH == 32
    #define FUNCT_ARCH(funct) funct ## _32
    #define ELF_T Elf32_Ehdr
    #define ELFPH_T Elf32_Phdr
    #define ELFSH_T Elf32_Shdr
    #define ELFSYM_T Elf32_Sym
#else
    #define FUNCT_ARCH(funct) funct ## _64
    #define ELF_T Elf64_Ehdr
    #define ELFPH_T Elf64_Phdr
    #define ELFSH_T Elf64_Shdr
    #define ELFSYM_T Elf64_Sym
#endif

#ifndef FUNC
    #define FUNC 1
#endif
#if FUNC == 1
    #define ELF_FUNCT my_nm
    #define ELF_FUNCT_32 my_nm_32
    #define ELF_FUNCT_64 my_nm_64
#else
    #define ELF_FUNCT my_objdump
    #define ELF_FUNCT_32 my_objdump_32
    #define ELF_FUNCT_64 my_objdump_64
#endif

#define CONCAT(s1, s2) s1 ## s2

typedef struct readelf_s {
    char *name;
    struct stat stat;
    ELF_T *file;
    ELFPH_T *pheader;
    ELFSH_T *sheader;
    ELFSYM_T *symbol;
    map_t section_list; //string, ELFSH_T

    char *shstrtab;
    char *strtab;
    char *dynstrtab;
    int symsize;
} readelf_t;

void my_nm_32(readelf_t *);
void my_nm_64(readelf_t *);
void my_objdump_32(readelf_t *);
void my_objdump_64(readelf_t *);

void print_flags(size_t flag);
char type_nm32(Elf32_Sym *sym, Elf32_Shdr *shead);
char type_nm64(Elf64_Sym *sym, Elf64_Shdr *shead);

#endif
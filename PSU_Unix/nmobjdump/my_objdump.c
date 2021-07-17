/*
** EPITECH PROJECT, 2020
** PSU_nmobjdump_2019 [WSL: Ubuntu]
** File description:
** my_ojdump
*/

#include "elf_reader.h"

static size_t get_flag(readelf_t *mstruct)
{
    size_t flags = 0;
    char symFlag = 0;

    if (mstruct->file->e_type == ET_REL)
        flags |= 0x01;
    if (mstruct->file->e_type == ET_EXEC)
        flags |= 0x02;
    for (size_t i = 0; i < mstruct->file->e_shnum; i++)
        if (mstruct->sheader[i].sh_type == SHT_SYMTAB ||
            mstruct->sheader[i].sh_type == SHT_DYNSYM)
            symFlag = 1;
    if (symFlag == 1)
        flags |= 0x10;
    if (mstruct->file->e_type == ET_DYN)
        flags |= 0x40;
    if (mstruct->file->e_phnum != 0)
        flags |= 0x100;
    return flags;
}

static void describe_header(readelf_t *mstruct)
{
    size_t flag = get_flag(mstruct);
    printf("\n%s:     file format %s\n", mstruct->name, (mstruct->file->\
e_ident[EI_CLASS] == ELFCLASS32 ? "elf32-i386" : "elf64-x86-64"));
    printf("architecture: %s, flags 0x%08lx:\n", (mstruct->file->e_ident[EI\
_CLASS] == ELFCLASS32 ? "i386" : "i386:x86-64"), flag);
    print_flags(flag);
    printf("start address 0x%016lx\n\n", (size_t)mstruct->file->e_entry);
}

static void describe_obj_next(ELFSH_T *sheader, unsigned char *mem, size_t i)
{
    for (size_t j = 0; j != 4; j++) {
        for (size_t k = 0; k != 4; k++) {
            if (i*0x10 + j*4 + k < sheader->sh_size)
                printf("%02x", mem[i*0x10+j*4+k]);
            else
                printf("  ");
        }
        printf(" ");
    }
    printf(" ");
    for (size_t j = 0; j != 0x10; j++)
        if (i*0x10 + j >= sheader->sh_size)
            printf(" ");
        else if (mem[i*0x10+j] < ' ' || mem[i*0x10+j] > '~')
            printf(".");
        else
            printf("%c", mem[i*0x10+j]);
    printf("\n");
}

static void describe_obj(ELFSH_T *sheader, readelf_t *mstruct)
{
    unsigned char *mem = (void *)mstruct->file + sheader->sh_offset;
    char *str = &mstruct->shstrtab[sheader->sh_name];

    if (sheader->sh_size == 0 || sheader->sh_type == SHT_NOBITS ||
        strstr(str, "tab") == str + strlen(str) - 3)
        return;
    printf("Contents of section %s:\n", &mstruct->shstrtab[sheader->sh_name]);
    for (size_t i = 0; i * 0x10 < sheader->sh_size; i++) {
        if ((size_t)sheader->sh_addr + sheader->sh_size > 0xFFFFF)
            printf(" %06lx ", (size_t)sheader->sh_addr+i*0x10);
        else if ((size_t)sheader->sh_addr + sheader->sh_size > 0xFFFF)
            printf(" %05lx ", (size_t)sheader->sh_addr+i*0x10);
        else
            printf(" %04lx ", (size_t)sheader->sh_addr+i*0x10);
        describe_obj_next(sheader, mem, i);
    }
}

void FUNCT_ARCH(my_objdump)(readelf_t *file)
{
    file->sheader = (void *)file->file + file->file->e_shoff;
    file->pheader = (void *)file->file + file->file->e_phoff;
    file->shstrtab = (char *)file->file +
        file->sheader[file->file->e_shstrndx].sh_offset;
    describe_header(file);
    for (int i = 0; i != file->file->e_shnum; i++) {
        ELFSH_T *sheader = file->sheader+i;
        describe_obj(sheader, file);
    }
}
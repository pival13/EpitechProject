/*
** EPITECH PROJECT, 2020
** PSU_nmobjdump_2019 [WSL: Ubuntu]
** File description:
** my_nm
*/

#include "elf_reader.h"

static readelf_t *static_ptr(readelf_t *m)
{
    static readelf_t *mem = NULL;

    if (m != NULL)
        mem = m;
    return mem;
}

static void list_dumper(ELFSYM_T *sym)
{
    ELFSH_T *sh = static_ptr(NULL)->sheader;
    if (sym->st_name != 0 && ELF64_ST_TYPE(sym->st_info) != STT_FILE) {
#if ARCH == 32
        if (type_nm32(sym, sh) != 'u' && type_nm32(sym, sh) != 'U' &&
            type_nm32(sym, sh) != 'w')
            printf("%08x %c %s\n", sym->st_value, type_nm32(sym, sh),
                static_ptr(NULL)->strtab + sym->st_name);
        else
            printf("%8c %c %s\n", ' ', type_nm32(sym, sh),
                static_ptr(NULL)->strtab + sym->st_name);
#else
        if (type_nm64(sym, sh) != 'u' && type_nm64(sym, sh) != 'U' &&
            type_nm64(sym, sh) != 'w')
            printf("%016lx %c %s\n", sym->st_value, type_nm64(sym, sh),
                static_ptr(NULL)->strtab + sym->st_name);
        else
            printf("%16c %c %s\n", ' ', type_nm64(sym, sh),
                static_ptr(NULL)->strtab + sym->st_name);
#endif
    }
}

static int symb_sort(ELFSYM_T *p1, ELFSYM_T *p2)
{
    if (!strcmp(static_ptr(NULL)->strtab + p1->st_name, static_ptr(NULL)
        ->strtab + p2->st_name))
        return p1->st_value - p2->st_value;
    return strcmp(static_ptr(NULL)->strtab + p1->st_name, static_ptr(NULL)
        ->strtab + p2->st_name);
}

static void fill_struct(readelf_t *file)
{
    file->section_list = NULL;
    file->sheader = (void *)file->file + file->file->e_shoff;
    file->shstrtab = (char *)file->file + file->sheader[file->file->
        e_shstrndx].sh_offset;
    for (int i = 0; i != file->file->e_shnum; i++) {
        if ((size_t)file->stat.st_size < file->file->e_shoff ||
            (size_t)file->stat.st_size < file->sheader[i].sh_offset) {
            printf("./my_nm: %s: Bad value\n", file->name);
            munmap(file->file, file->stat.st_size);
            exit(1);
        }
        map_add(&file->section_list, &file->shstrtab[file->sheader[i].sh_name],
            &file->sheader[i], (key_comparator_t)strcmp);
    }
    file->strtab = ((ELFSH_T *)map_get(file->section_list, ".strtab",
        (key_comparator_t)strcmp))->sh_offset + (void *)file->file;
}

void FUNCT_ARCH(my_nm)(readelf_t *file)
{
    static_ptr(file);
    fill_struct(file);
    ELFSH_T *symtab_header = map_get(file->section_list, ".symtab",
        (key_comparator_t)strcmp);
    ELFSYM_T *sym = (void *)file->file + symtab_header->sh_offset;
    list_t symbols = NULL;
    for (size_t i = 0; i != symtab_header->sh_size / symtab_header->
        sh_entsize; i++)
        list_push_back(&symbols, sym + i);
    list_sort(symbols, (value_comparator_t)symb_sort);
    list_dump(symbols, (value_displayer_t)list_dumper);
}

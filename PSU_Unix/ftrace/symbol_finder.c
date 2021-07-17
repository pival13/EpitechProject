/*
** EPITECH PROJECT, 2020
** ftrace [WSL: Ubuntu]
** File description:
** symbol_finder
*/

#include "ftrace.h"

static void get_symbol_name(Elf_Scn *scn, const shared_lib_t *slib,
    symbol_located_t *r)
{
    GElf_Ehdr ehdr;
    GElf_Shdr shdr;
    Elf_Data *data = elf_getdata(scn, NULL);
    GElf_Sym mem_sym;

    gelf_getsym(data, 0, &mem_sym);
    gelf_getshdr(scn, &shdr);
    gelf_getehdr(slib->elf, &ehdr);
    for (size_t i = 0; i < shdr.sh_size / shdr.sh_entsize; ++i) {
        GElf_Sym sym;
        gelf_getsym(data, i, &sym);
        if (sym.st_value <= r->offset && sym.st_value >= mem_sym.st_value)
            mem_sym = sym;
    }
    if (mem_sym.st_value != 0) {
        r->symb_name = elf_strptr(slib->elf, shdr.sh_link, mem_sym.st_name);
        r->symb_begin = mem_sym.st_value;
    }
}

static void sect_symbol_finder(const shared_lib_t *slib, symbol_located_t *r,
    unsigned int section_type)
{
    GElf_Shdr shdr;
    GElf_Ehdr ehdr;
    Elf_Scn *scn = elf_nextscn(slib->elf, NULL);
    while (scn) {
        gelf_getshdr(scn, &shdr);
        if (shdr.sh_type == section_type)
            break;
        scn = elf_nextscn(slib->elf, scn);
    }
    if (shdr.sh_entsize == 0)
        return;

    gelf_getehdr(slib->elf, &ehdr);
    r->sect_name = elf_strptr(slib->elf, ehdr.e_shstrndx, shdr.sh_name);
    return get_symbol_name(scn, slib, r);
}

static void symbols_section(const shared_lib_t *slib, symbol_located_t *r)
{
    GElf_Ehdr ehdr;
    GElf_Shdr shdr;
    Elf_Scn *scn = elf_nextscn(slib->elf, NULL);

    while (scn) {
        gelf_getshdr(scn, &shdr);
        if (shdr.sh_addr <= r->offset && shdr.sh_size + shdr.sh_addr >
            r->offset)
            break;
        scn = elf_nextscn(slib->elf, scn);
    }
    if (!scn)
        return;
    gelf_getehdr(slib->elf, &ehdr);
    r->sect_name = elf_strptr(slib->elf, ehdr.e_shstrndx, shdr.sh_name);
}

static shared_lib_t *symbols_binary(const ftrace_t *obj, size_t offset,
    symbol_located_t *r)
{
    shared_lib_t *slib;
    GElf_Ehdr ehdr;

    for (size_t idx = 0; idx != list_size(obj->elfs); idx++) {
        slib = list_get(obj->elfs, idx);
        gelf_getehdr(slib->elf, &ehdr);
        for (int i = 5; i >= 0; i--) {
            if (!slib->pos[i][1])
                continue;
            if (slib->pos[i][0] <= offset && slib->pos[i][1] > offset) {
                if (ehdr.e_type == ET_EXEC)
                    r->offset = offset;
                else
                    r->offset = offset - slib->pos[i][0] + slib->pos[i][2];
                r->bin_name = slib->name;
                return slib;
            }
        }
    }
    return NULL;
}

symbol_located_t symbol_finder(const ftrace_t *obj, size_t offset)
{
    symbol_located_t result = {0};
    shared_lib_t *slib = symbols_binary(obj, offset, &result);

    if (!slib)
        return result;
    symbols_section(slib, &result);
    if (!result.sect_name)
        return result;
    if (!strcmp(result.sect_name, ".plt")) {
        search_plt(slib, &result);
    } else {
        sect_symbol_finder(slib, &result, SHT_SYMTAB);
        if (!result.symb_name)
            sect_symbol_finder(slib, &result, SHT_DYNSYM);
    }
    return result;
}
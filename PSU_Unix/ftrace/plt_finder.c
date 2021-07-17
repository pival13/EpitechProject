/*
** EPITECH PROJECT, 2020
** ftrace [WSL: Ubuntu]
** File description:
** symbol_finder
*/

#include "ftrace.h"

static size_t get_got_index(Elf_Scn *scn[4], size_t initoff)
{
    GElf_Shdr shdr;
    size_t offset = 0;

    gelf_getshdr(scn[1], &shdr);
    Elf_Data *data = elf_getdata(scn[1], NULL);
    for (size_t i = 0; i < shdr.sh_size / shdr.sh_entsize; ++i)
        if (initoff - shdr.sh_addr == i * shdr.sh_entsize) {
            uint32_t *off = data->d_buf + i*shdr.sh_entsize+2;
            offset = shdr.sh_addr + i*shdr.sh_entsize + 6 + *off;
        }
    if (offset == 0)
        return 0;
    gelf_getshdr(scn[2], &shdr);
    for (size_t i = 0; i < shdr.sh_size / shdr.sh_entsize; ++i)
        if (offset == shdr.sh_addr + i * shdr.sh_entsize)
            return i;
    return 0;
}

static void get_section(const shared_lib_t *slib, Elf_Scn *scn[4])
{
    GElf_Ehdr ehdr;
    GElf_Shdr shdr;

    gelf_getehdr(slib->elf, &ehdr);
    for (Elf_Scn *scn2 = elf_nextscn(slib->elf, NULL); scn2; scn2 =
        elf_nextscn(slib->elf, scn2)) {
        gelf_getshdr(scn2, &shdr);
        if (shdr.sh_type == SHT_DYNSYM)
            scn[0] = scn2;
        if (!strcmp(elf_strptr(slib->elf, ehdr.e_shstrndx, shdr.sh_name),
            ".plt"))
            scn[1] = scn2;
        if (!strcmp(elf_strptr(slib->elf, ehdr.e_shstrndx, shdr.sh_name),
            ".got") || !strcmp(elf_strptr(slib->elf, ehdr.e_shstrndx,
            shdr.sh_name), ".got.plt"))
            scn[2] = scn2;
        if (!strcmp(elf_strptr(slib->elf, ehdr.e_shstrndx, shdr.sh_name),
            ".rela.plt"))
            scn[3] = scn2;
    }
}

void search_plt(const shared_lib_t *slib, symbol_located_t *r)
{
    Elf_Scn *scn[4] = {NULL, NULL, NULL, NULL};
    GElf_Shdr shdr;
    GElf_Rela rel;
    GElf_Sym sym;

    get_section(slib, scn);
    if (!scn[0] || !scn[1] || !scn[2] || !scn[3])
        return;

    size_t index = get_got_index(scn, r->offset);
    if (index < 3)
        return;

    gelf_getshdr(scn[0], &shdr);
    gelf_getrela(elf_getdata(scn[3], NULL), index-3, &rel);
    gelf_getsym(elf_getdata(scn[0], NULL), ELF64_R_SYM(rel.r_info), &sym);
    r->symb_name = elf_strptr(slib->elf, shdr.sh_link, sym.st_name);
    r->symb_begin = r->offset;
}

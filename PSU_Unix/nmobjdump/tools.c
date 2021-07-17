/*
** EPITECH PROJECT, 2020
** PSU_nmobjdump_2019 [WSL: Ubuntu]
** File description:
** tools
*/

#include "elf_reader.h"

void print_flags(size_t flag)
{
    char *arr[9] = {"HAS_RELOC", "EXEC_P", "HAS_LINEO", "HAS_DEBUG",
        "HAS_SYMS", "HAS_LOCALS", "DYNAMIC", "WP_TEXT", "D_PAGED"};
    int ok = 0;

    if (flag == 0) {
        printf("BFD_NO_FLAGS\n");
    } else {
        for (size_t i = 0; i != 9; i++) {
            if (flag & 0x01) {
                if (ok)
                    printf(", ");
                printf("%s", arr[i]);
                ok = 1;
            }
            flag = flag >> 1;
        }
        printf("\n");
    }
}

char type_nm32_next(Elf32_Sym *sym, Elf32_Shdr *shead, int a)
{
    if ((ELF64_ST_TYPE(sym->st_info) == STT_FUNC && shead[a].sh_type ==
        SHT_PROGBITS && (shead[a].sh_flags & SHF_EXECINSTR) &&
        (shead[a].sh_flags & SHF_ALLOC)) ||
        ((ELF64_ST_TYPE(sym->st_info) == STT_OBJECT ||
        ELF64_ST_TYPE(sym->st_info) == STT_NOTYPE) && (shead[a].sh_flags
        & SHF_WRITE) && (shead[a].sh_flags & SHF_ALLOC)))
        return (ELF64_ST_BIND(sym->st_info) == STB_LOCAL ? 't' : 'T');
    if ((shead[a].sh_type == SHT_PROGBITS && (shead[a].sh_flags & SHF_ALLOC))
        || (shead[a].sh_type == SHT_DYNAMIC))
        return (shead[a].sh_flags & SHF_WRITE ? (ELF64_ST_BIND(sym->st_info)
        == STB_LOCAL ? 'd' : 'D') : (ELF64_ST_BIND(sym->st_info) == STB_LOCAL
        ? 'r' : 'R'));
    return '?';
}

char type_nm32(Elf32_Sym *sym, Elf32_Shdr *shead)
{
    int a = sym->st_shndx;
    if (ELF64_ST_BIND(sym->st_info) == STB_WEAK)
        return (ELF64_ST_TYPE(sym->st_info) == STT_OBJECT ? 'V' :
            (sym->st_shndx == SHN_UNDEF ? 'w' : 'W'));
    if (sym->st_shndx == SHN_COMMON || sym->st_shndx == SHN_ABS)
        return (sym->st_shndx == SHN_COMMON ? 'C' : 'A');
    if (sym->st_shndx == SHN_UNDEF)
        return (ELF64_ST_BIND(sym->st_info) == STB_LOCAL ? 'u' : 'U');
    if (shead[a].sh_type == SHT_NOBITS)
        return (ELF64_ST_BIND(sym->st_info) == STB_LOCAL ? 'b' : 'B');
    return type_nm32_next(sym, shead, a);
}

char type_nm64_next(Elf64_Sym *sym, Elf64_Shdr *shead, int a)
{
    if ((shead[a].sh_type == SHT_PROGBITS && (shead[a].sh_flags & SHF_ALLOC))
        || (shead[a].sh_type == SHT_DYNAMIC))
        return (shead[a].sh_flags & SHF_WRITE ? (ELF64_ST_BIND(sym->st_info) ==
            STB_LOCAL ? 'd' : 'D') : (ELF64_ST_BIND(sym->st_info) == STB_LOCAL
            ? 'r' : 'R'));
    if ((ELF64_ST_TYPE(sym->st_info) == STT_FUNC && shead[a].sh_type ==
        SHT_PROGBITS && (shead[a].sh_flags & SHF_EXECINSTR) &&
        (shead[a].sh_flags & SHF_ALLOC)) ||
        ((ELF64_ST_TYPE(sym->st_info) == STT_OBJECT ||
        ELF64_ST_TYPE(sym->st_info) == STT_NOTYPE) && (shead[a].sh_flags &
        SHF_WRITE) && (shead[a].sh_flags & SHF_ALLOC)))
        return (ELF64_ST_BIND(sym->st_info) == STB_LOCAL ? 't' : 'T');
    return '?';
}

char type_nm64(Elf64_Sym *sym, Elf64_Shdr *shead)
{
    int a = sym->st_shndx;
    if (ELF64_ST_BIND(sym->st_info) == STB_WEAK)
        return (ELF64_ST_TYPE(sym->st_info) == STT_OBJECT ? 'V' :
            (sym->st_shndx == SHN_UNDEF ? 'w' : 'W'));
    if (sym->st_shndx == SHN_COMMON)
        return 'C';
    if (sym->st_shndx == SHN_ABS)
        return 'A';
    if (sym->st_shndx == SHN_UNDEF)
        return (ELF64_ST_BIND(sym->st_info) == STB_LOCAL ? 'u' : 'U');
    if (shead[a].sh_type == SHT_NOBITS)
        return (ELF64_ST_BIND(sym->st_info) == STB_LOCAL ? 'b' : 'B');
    return type_nm64_next(sym, shead, a);
}
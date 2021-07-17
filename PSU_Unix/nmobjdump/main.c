/*
** EPITECH PROJECT, 2020
** PSU_nmobjdump_2019 [WSL: Ubuntu]
** File description:
** main
*/

#include "elf_reader.h"

void ELF_FUNCT(readelf_t *file)
{
    if (file->file->e_ident[EI_CLASS] == ELFCLASS32)
        ELF_FUNCT_32(file);
    else if (file->file->e_ident[EI_CLASS] == ELFCLASS64)
        ELF_FUNCT_64(file);
    else
        dprintf(2, "%s file format not recognized\n", file->name);
}

static bool check_file(int fd, readelf_t *file, char *funct, char *s)
{
    if (fstat(fd, &file->stat) == -1) {
        dprintf(2, "%s: %s: %s\n", funct, s, strerror(errno));
        return false;
    } else if (S_ISDIR(file->stat.st_mode)) {
        dprintf(2, "%s: Warning: '%s' is a directory\n", funct, s);
        return false;
    }
    file->file = mmap(NULL, file->stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (file->file == (void *)-1) {
        dprintf(2, "%s: %s: %s\n", funct, s, strerror(errno));
        return false;
    } else if (strncmp((char *)file->file->e_ident, ELFMAG, 4)) {
        dprintf(2, "%s file format not recognized\n", s);
        return false;
    }
    return true;
}

static void parse_file(readelf_t *file, char *s)
{
    file->name = s;
    file->pheader = NULL;
    file->sheader = NULL;
    file->shstrtab = NULL;
    file->strtab = NULL;
    ELF_FUNCT(file);
    munmap(file->file, file->stat.st_size);
}

static void check_each_file(int i, int n, char **arg, size_t *return_value)
{
    readelf_t elf;
    int fd = open(arg[i], O_RDONLY);

    if (fd == -1) {
        dprintf(2, "'%s' No such file\n", arg[i]);
        *return_value = 1;
        return;
    }
    if (check_file(fd, &elf, arg[0], arg[i])) {
        if (n != 2 && FUNC == 1)
            printf("\n%s:\n", arg[i]);
        parse_file(&elf, arg[i]);
    }
    close(fd);
}

int main(int n, char **arg)
{
    size_t return_value = 0;

    if (n == 1)
        check_each_file(1, 2, (char *[2]){arg[0], "a.out"}, &return_value);
    for (int i = 1; i < n; i++)
        check_each_file(i, n, arg, &return_value);
    return return_value;
}

//Add flags on objdump
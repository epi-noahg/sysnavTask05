/*
** EPITECH PROJECT, 2021
** sysnavTask05
** File description:
** open_file.c
*/

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

char *open_file(char **av)
{
    // open a file and return it's content
    char *buff;
    struct stat st;
    int fd = open(av[1], O_RDONLY);

    if (fd == -1 || fstat(fd, &st) == -1)
        exit(1);
    buff = malloc(sizeof(char) * st.st_size + 1);
    if (buff == NULL)
        exit(1);
    buff[st.st_size] = '\0';
    if (read(fd, buff, st.st_size) == -1)
        exit(1);
    if (close(fd) == -1)
        exit(1);
    return (buff);
}

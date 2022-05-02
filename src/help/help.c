/*
** EPITECH PROJECT, 2021
** sysnavTask05
** File description:
** help.c
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void help(int ac, char **av)
{
    if (ac == 2 && (strcmp(av[1], "-h") == 0 || strcmp(av[1], "--help") == 0)) {
        printf("Usage (-h):\n");
        printf("  ./task05 <file>\n");
        exit(0);
    }
}
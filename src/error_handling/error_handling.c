/*
** SYSNAV PROJECT, 2022
** sysnavTask05
** File description:
** error_handling
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void error_handling(int ac, char **av)
{
    if (ac != 2) {
        fprintf(stderr, "Error: Invalid number of arguments\n");
        fprintf(stderr, "  Try: ./task05 -h\n");
        exit(1);
    }
}
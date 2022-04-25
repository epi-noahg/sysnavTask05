/*
** EPITECH PROJECT, 2022
** ex5
** File description:
** error_handling
*/

#include <stdlib.h>
#include <unistd.h>

void error_handling(int ac, char **av)
{
    if (ac != 2) {
        write(2, "Error: Invalid number of arguments\n", 36);
        write(2, "  Try: ./task05 -h\n", 20);
        exit(1);
    }
}
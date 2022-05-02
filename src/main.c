/*
** SYSNAV PROJECT, 2022
** sysnavTask05
** File description:
** main
*/

#include "../include/main.h"

int main(int ac, char **av)
{
    error_handling(ac, av);
    help(ac, av);
    solver(av);
    return (0);
}

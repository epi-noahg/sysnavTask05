/*
** EPITECH PROJECT, 2021
** sysnavTask05
** File description:
** utils.c
*/

#include "../../include/vector.h"
#include <string.h>

int count_char(char *str, char c)
{
    int res = 0;

    for (int i = 0; str[i] != '\0'; i++)
        res += str[i] == c ? 1 : 0;
    return (res);
}

int find_length(char *str)
{
    int i = 0;

    for (; str[i] != '\n'; i++);
    return (i);
}

vector_t find_coord(char *map, int nbExits, char toFind)
{
    char *str = strdup(map);
    vector_t result = (vector_t) {0, 0};
    int i = 0;
    int x = 0;
    int y = 0;

    while (nbExits != 0) {
        for (i = 0; str[i] != toFind && str[i] != '\0'; i++);
        str[i] = str[i] == toFind ? '.' : str[i];
        nbExits--;
    }
    for (i = 0; str[i] != toFind; i++) {
        if (str[i] == '\n') {
            y = 0;
            x++;
        }
        else
            y++;
    }
    free(str);
    return ((vector_t) {x, y});
}
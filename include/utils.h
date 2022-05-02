/*
** SYSNAV PROJECT, 2022
** sysnavTask05
** File description:
** utils
*/

#ifndef UTILS_H_
    #define UTILS_H_

    #include "vector.h"

    #define MIN(a, b) (a < b) ? a : b
    #define INF 999999

    int count_char(char *str, char c);
    int find_length(char *str);
    vector_t find_coord(char *map, int nbExits, char toFind);

#endif /* !UTILS_H_ */

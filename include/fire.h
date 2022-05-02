/*
** SYSNAV PROJECT, 2022
** sysnavTask05
** File description:
** fire
*/

#ifndef FIRE_H_
    #define FIRE_H_

    #include "matrix.h"

    void propagation(matrix_t *matrix);
    void add_fire(int **matrix, char *map);

#endif /* !FIRE_H_ */

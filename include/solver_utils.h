/*
** SYSNAV PROJECT, 2022
** sysnavTask05
** File description:
** solver_utils
*/

#ifndef SOLVER_UTILS_H_
    #define SOLVER_UTILS_H_

    #include "utils.h"
    #include "matrix.h"

    int small_neighbour(matrix_t *matrix, int x, int y, int a);
    int neighbour_path(matrix_t *matrix, int i, int j);
    void print_trajectory(matrix_t *matrix, vector_t start, vector_t end);
    int check_results(matrix_t *matrix, vector_t start, vector_t end);


#endif /* !SOLVER_UTILS_H_ */

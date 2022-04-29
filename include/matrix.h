/*
** EPITECH PROJECT, 2022
** ex5
** File description:
** matrix
*/

#ifndef MATRIX_H_
    #define MATRIX_H_

    typedef struct matrix_s {
        int **matrix;
        int xMax;
        int yMax;
    } matrix_t;

    matrix_t *create_matrix(int size_x, int size_y);
    void fill_matrix(int **matrix, char *map);
    void print_matrix(matrix_t *matrix);
    void propagation(matrix_t *matrix);

#endif /* !MATRIX_H_ */
